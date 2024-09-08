#include "GameData.h"
#include "../Items/ItemDistributorEntity.h"

GameData::GameData()
{
    int count = 0;
    while (count < 6)
    {
        int ranItem = rand() % Items::ITEM_COUNT;
        Items aux = static_cast<Items>(ranItem);
        if (itemList.count(aux) <= 0)
        {
            itemList[aux] = false;
            count++;
        }
    }
}

int GameData::GetNumCoins() const
{
    return numCoins;
}

void GameData::AddCoins(int num)
{
    numCoins += num;
}

bool GameData::AddItem(int item)
{
    if (itemList.count(item) <= 0)
    {
        return false;
    }
    if (itemList[item])
    {
        return false;
    }
    itemList[item] = true;
    return true;
}


std::string GameData::GetItemsString()
{
    std::string buffer;
    for (auto& kv : itemList)
    {
        buffer.append("- ").append(ItemDistributorEntity::GetStringByItem(static_cast<Items>(kv.first))).append(" :").
               append(
                   kv.second ? " RECOGIDO" : "--------").append("|");
    }
    return buffer;
}

int GameData::GetMissingItems()
{
    int count = 0;
    for (auto& kv : itemList)
    {
        count = !kv.second ? count + 1 : count;
    }
    return count;
}

bool GameData::AllItemsCollected()
{
    return GetMissingItems() == 0;
}
