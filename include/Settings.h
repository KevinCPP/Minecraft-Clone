#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

namespace Settings {
    // paths for loading various assets
    extern std::string  TEXTURE_ATLAS_FILE_PATH;
    extern std::string  TEXTURE_DIRECTORY;
    extern std::string  SHADER_DIRECTORY;

    // number of textures in a texture atlas
    extern size_t       TEXTURE_ATLAS_SIZE_X;
    extern size_t       TEXTURE_ATLAS_SIZE_Y;

    // basic settings
    extern size_t       ResolutionX;
    extern size_t       ResolutionY;
    extern float        FOV;

    // other video settings
    extern bool         useMipmapping;
    extern bool         useAnisotropicFiltering;
    extern float        anisotropicLevels;

    extern size_t       renderDistance;

    // initializes default settings
    void defaultSettings();
}

#endif
