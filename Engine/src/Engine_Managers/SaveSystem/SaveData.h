#pragma once
#include <fstream>
#include <iostream>
#include <string>

#include "../../Utils/Debug/DrawDebugUtils.h"
using namespace std;
/// Each project must overwrite this save file
class SaveData
{
private:
    time_t m_saveDate = time_t();

public:
    SaveData();

    // Constructor to initialize the data members
    SaveData(time_t saveDate);

    // Getter methods for the class
    time_t GetSaveDate() const;
    void SetSaveDate(time_t time);


    //  Function for Serialization
    void SaveToFile_Serialize(const string& filename);

    //  Function for Deserialization
    static SaveData LoadSave_Deserialize(const string& filename);
};
