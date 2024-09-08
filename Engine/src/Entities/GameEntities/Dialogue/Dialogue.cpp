#include "Dialogue.h"

Dialogue::Dialogue()
{
}

Dialogue::Dialogue(std::string name, std::vector<std::string> texts, std::vector<std::string> options): m_name(name), m_texts(texts), m_options(options)
{
}
