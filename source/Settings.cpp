#include "Settings.h"

namespace Settings {

    std::string  TEXTURE_ATLAS_FILE_PATH;
    size_t       TEXTURE_ATLAS_SIZE_X;
    size_t       TEXTURE_ATLAS_SIZE_Y;
    size_t       ResolutionX;
    size_t       ResolutionY;
    float        FOV;

    bool        useMipmapping;
    bool        useAnisotropicFiltering;
    float       anisotropicLevels;

    void defaultSettings() {
        TEXTURE_ATLAS_FILE_PATH = "resources/textures/atlas.bmp";
        TEXTURE_ATLAS_SIZE_X = 4;
        TEXTURE_ATLAS_SIZE_Y = 4;

        ResolutionX = 1600;
        ResolutionY = 900;
        FOV = 90.0f;
    
        useMipmapping = true;
        useAnisotropicFiltering = true;
        anisotropicLevels = 2.0f;
    }
}
