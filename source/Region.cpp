#include "../include/Region.h"
#include "../include/CubeFactory.h"

namespace World {

    Region::Region() : rd(Settings::renderDistance * 2) {
        loadedChunks = new Chunk**[rd];
        
        std::cout << "going to allocate: " << sizeof(Chunk) * rd * rd * rd << " bytes." << std::endl;

        for(size_t i = 0; i < rd; ++i) {
            loadedChunks[i] = new Chunk*[rd];
            for(size_t j = 0; j < rd; ++j) {
                loadedChunks[i][j] = new Chunk[rd];
            }
        }

    }

    Region::~Region() { 
        for(size_t i = 0; i < rd; ++i) {
            for(size_t j = 0; j < rd; ++j) {
                delete[] loadedChunks[i][j];
            }
            delete[] loadedChunks[i];
        }
        delete[] loadedChunks;
    }
}



