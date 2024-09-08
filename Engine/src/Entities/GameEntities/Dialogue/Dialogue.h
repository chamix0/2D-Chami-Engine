#pragma once
#include <string>
#include <vector>

class Dialogue
{
public:
    std::string m_name;
    std::vector<std::string> m_texts;
    std::vector<std::string> m_options;
    Dialogue();
    Dialogue(std::string name, std::vector<std::string> texts, std::vector<std::string> options);
};
