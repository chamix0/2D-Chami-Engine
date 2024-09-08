#pragma once
#include <map>
#include <string>


class GameData
{
private:
    int numCoins;
    std::map<int, bool> itemList;

public:
    GameData();
    int GetNumCoins() const;
    void AddCoins(int num);
    bool AddItem(int item);
    std::string GetItemsString();
    int GetMissingItems();
    bool AllItemsCollected();

};
