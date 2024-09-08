#pragma once
enum FONTS
{
    ORANGE = 0,
    SLAPT_STICK_COMIC,
    RETRO_GAMING,
    COUNT
};

inline const char* FONTS_TO_STRING(FONTS font)
{
    switch (font)
    {
    case ORANGE: return "data/Fonts/Orange.ttf";

    case SLAPT_STICK_COMIC: return "data/Fonts/SFSlapstickComic.ttf";

    case RETRO_GAMING: return "data/Fonts/RetroGaming.ttf";

    default: return "data/Fonts/RetroGaming.ttf";
    }
}
