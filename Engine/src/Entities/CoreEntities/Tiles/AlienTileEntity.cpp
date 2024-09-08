#include "AlienTileEntity.h"
#include "Enums.h"
#include "../../../Engine_Managers/AudioManager.h"
#include "../../../Utils/Collision/Collider.h"
#include "../../../Utils/Sprite/Sprite.h"
#include "../../../Engine_Managers/LogicManager.h"
#include "../../../Utils/MathUtils.h"
#include "../../../Utils/Debug/DrawDebugUtils.h"

AlienTileEntity::AlienTileEntity(Vec2 position, int renderLayer, std::string tag, std::string path, int numCols,
                                 int numRows,
                                 int id): TileEntity(position, renderLayer, tag, path, numCols, numRows, id)
{
    //create  sprite
    m_tileSprite = new Sprite(path, numCols, numRows, Vec2(1), BLEND_ALPHA,
                              Vec2(1), Vec2(0.5f), 0,
                              NONE, WORLD, id);

    //updata sprite
    m_tileSprite->update(0.f, position);

    //register sprite
    AddSprite(m_tileSprite);
}

void AlienTileEntity::RenderUpdate()
{
    Entity::RenderUpdate();

    //draw sprite
    m_tileSprite->draw();
}

void AlienTileEntity::BeginPlay()
{
    //parent beguin play
    TileEntity::BeginPlay();

    //startStopwatch
    stop_watch.Start();
    m_killStopwatch.Start();
    m_killStopwatch.AddElapsedTime(10.f);
    //get player
    m_player = LogicManager::GetInstanceLogicManager()->GetCurrentScene()->GetPlayer();
}

void AlienTileEntity::EarlyUpdate(double tick)
{
    updated = false;
    m_desiredAlpha = 0;
}


void AlienTileEntity::LogicUpdate(double tick)
{
    if (hasAlien)
    {
        SetNeighborsAlpha(GetPosition(), 0);
    }
}

void AlienTileEntity::LogicLateUpdate(double tick)
{
    //update alpha
    m_alpha = MathUtils::fLerp(m_alpha, m_desiredAlpha, tick, m_speed);
    m_tileSprite->setColor(Vec2(1, 1, 1, m_alpha));

    //move
    if (hasAlien)
    {
        //feed the stop watch
        stop_watch.ReceiveTick(tick);
        m_killStopwatch.ReceiveTick(tick);
        //draw debug
        // DrawDebugUtils::DrawDebugCircle( GetPosition(),m_maxDistance,Vec2(1,0,0,1));
        // DrawDebugUtils::DrawDebugCircle(GetPosition(),m_minDistance,Vec2(0,1,0,1));


        float distance = m_player->GetPosition().distance(GetPosition());

        //update difficulty
        UpdateDifficulty();

        //tension cooldown
        cooldown = distance < m_maxDistance * 0.75 ? cooldown = maxCooldown / 2.f : cooldown = maxCooldown;

        //do kill stuff
        if (distance < m_minDistance && stop_watch.GetElapsedSeconds() >= cooldown)
        {
            //change alien location
            changeAlienLocation();

            //reset stop watch
            stop_watch.ReStart();

            //load game
            LogicManager::GetInstanceLogicManager()->SetCurrentScene(
                LogicManager::GetInstanceLogicManager()->GetSceneManager()->GetDialogueLevel(1, GetDifficulty()));
        }

        //move alien

        if (stop_watch.GetElapsedSeconds() >= cooldown)
        {
            float gain = 1 - MathUtils::Clamp(MathUtils::NormalizeBetweenValues(distance, m_minDistance, m_maxDistance),
                                              0, 1);
            //audio 
            AudioManager::GetInstanceAudioManager()->PlayInstantSound("data/Audio/stomp.wav", 1, gain, GetPosition());

            //MOVE
            Move();

            //reset stop watch
            stop_watch.ReStart();
        }
    }
}

void AlienTileEntity::SetAlpha(Vec2 position)
{
    updated = true;
    float distance = position.distance(GetPosition());
    m_desiredAlpha = 1 - MathUtils::NormalizeBetweenValues(distance, m_minDistance, m_maxDistance);
}

void AlienTileEntity::SetNeighborsAlpha(Vec2 position, int depth)
{
    //set self alpha
    SetAlpha(position);

    //propagate to neighbours
    if (depth > maxDepth)
    {
        return;
    }

    for (TileEntity* tile : GetNeighBors())
    {
        AlienTileEntity* ocTile = dynamic_cast<AlienTileEntity*>(tile);
        if (ocTile != nullptr && !ocTile->updated)
        {
            ocTile->SetNeighborsAlpha(position, depth + 1);
        }
    }
}

void AlienTileEntity::Move()
{
    float distance = m_player->GetPosition().distance(GetPosition());
    SetHasAlien(false);
    if (distance < m_detectionRange)
    {
        //the next tile inilialized to this in case the path is too short
        AlienTileEntity* nextTile = this;

        std::vector<TileEntity*> path = AStar(m_player->GetPosition());
        if (path.size() > 2)
        {
            nextTile = dynamic_cast<AlienTileEntity*>(path[path.size() - 2]);
        }

        nextTile->SetHasAlien(true);
    }
    else
    {
        //move random
        int randInd = rand() % GetNeighBors().size();
        AlienTileEntity* nextTile = dynamic_cast<AlienTileEntity*>(GetNeighBors()[randInd]);;
        nextTile->SetHasAlien(true);
    }
}

bool AlienTileEntity::GetUpdated() const
{
    return updated;
}


void AlienTileEntity::SetHasAlien(bool value)
{
    hasAlien = value;
}

void AlienTileEntity::changeAlienLocation(int depth)
{
    //deactivate alien here
    SetHasAlien(false);

    //look for other alien
    std::vector<Entity*> aliens = LogicManager::GetInstanceLogicManager()->FindEntitiesWithTag("alienTile");

    //update other aliens
    if (depth == 0)
    {
        for (int i = 0; i < aliens.size(); ++i)
        {
            AlienTileEntity* aux = dynamic_cast<AlienTileEntity*>(aliens[i]);

            if (aux == this)
            {
                continue;
            }

            if (aux->hasAlien)
            {
                aux->changeAlienLocation(depth + 1);
            }
        }
    }

    //move the other aliens
    bool validPos = false;
    while (validPos == false)
    {
        int rIndex = rand() % aliens.size();
        Entity* currentTile = aliens[rIndex];
        if (currentTile->GetPosition().distance(m_player->GetPosition()) > m_maxDistance * 3.f)
        {
            validPos = true;
            AlienTileEntity* aux = dynamic_cast<AlienTileEntity*>(currentTile);
            aux->SetHasAlien(true);
            aux->m_killStopwatch.ReStart();
        }
    }
}

int AlienTileEntity::GetDifficulty()
{
    int missingItems = m_player->m_gameData.GetMissingItems();
    if (missingItems <= 2)
    {
        return 2;
    }
    if (missingItems <= 4)
    {
        return 1;
    }
    return 0;
}

void AlienTileEntity::UpdateDifficulty()
{
    int difficulty = GetDifficulty();

    //override difficulty when killed
    if (m_killStopwatch.GetElapsedSeconds() < killCooldown)
    {
        m_detectionRange = 550.f;
        maxCooldown = 10.f;
        return;
    }

    if (difficulty == 0)
    {
        m_detectionRange = 550.f;
        maxCooldown = 1.f;
    }
    else if (difficulty == 1)
    {
        m_detectionRange = 650.f;
        maxCooldown = 0.75f;
    }
    else
    {
        m_detectionRange = 800.f;
        maxCooldown = 0.5f;
    }
}
