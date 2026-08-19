#include "SaveData.h"

SaveData::SaveData()
{
}

SaveData::SaveData(time_t saveDate) : m_saveDate(saveDate)
{
}

time_t SaveData::GetSaveDate() const
{
    return m_saveDate;
}

void SaveData::SetSaveDate(time_t time)
{
    m_saveDate = time;
}

void SaveData::SaveToFile_Serialize(const string& filename)
{
    ofstream file(filename, ios::binary);
    if (!file.is_open())
    {
        DrawDebugUtils::AddToLog("Error: Failed to open file for writing.");
        return;
    }
    file.write(reinterpret_cast<const char*>(this), sizeof(*this));
    file.close();
    DrawDebugUtils::AddToLog("Object serialized successfully.");
}

SaveData SaveData::LoadSave_Deserialize(const string& filename)
{
    SaveData obj = SaveData(time_t());
    ifstream file(filename, ios::binary);
    if (!file.is_open())
    {
        DrawDebugUtils::AddToLog("Error: Failed to open file for reading.");
        return SaveData();
    }
    file.read(reinterpret_cast<char*>(&obj),
              sizeof(obj));
    file.close();

    DrawDebugUtils::AddToLog("Object deserialized successfully.");
    return obj;
}
