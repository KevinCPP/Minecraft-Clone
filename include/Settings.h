#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

namespace Settings {
    extern std::string  TEXTURE_ATLAS_FILE_PATH;
    extern size_t       TEXTURE_ATLAS_SIZE_X;
    extern size_t       TEXTURE_ATLAS_SIZE_Y;
    extern size_t       ResolutionX;
    extern size_t       ResolutionY;
    extern float        FOV;

    void defaultSettings();
}

#endif
