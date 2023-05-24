#include "../include/Region.h"
#include "../include/CubeFactory.h"

#include <cmath>

namespace World {

    using i64vec3 = glm::tvec3<int64_t>;
    
    Region::Region(int64_t x, int64_t y, int64_t z) {
        centerX = x;
        centerY = y;
        centerZ = z;
    }

    int64_t Region::getDistanceFromCenter(int64_t x, int64_t y, int64_t z) {
        int64_t dx = std::abs(centerX - x);
        int64_t dy = std::abs(centerY - y);
        int64_t dz = std::abs(centerZ - z);
        
        // uses this instead of distance formula so we can generate in a "square"
        // pattern around the center point.
        return std::max(std::max(dx, dy), dz);
    }

    int64_t Region::getDistanceFromCenter(Geometry::Location key) {
        getDistanceFromCenter(key.x, key.y, key.z);
    }

    void Region::makeQueue(int16_t radius) {
        // clear the priority queue using the swap method
        std::priority_queue<Point, std::vector<Point>, PointComparator> emptyQueue;
        toGenerate.swap(emptyQueue);
        
        for(int64_t x = centerX - radius; x <= centerX + radius; x++)
        for(int64_t y = centerY - radius; y <= centerY + radius; y++)
        for(int64_t z = centerZ - radius; z <= centerZ + radius; z++) {
            int64_t dist = getDistanceFromCenter(x, y, z);
            
            toGenerate.push(Point(dist, Geometry::Location(x, y, z)));
        }
    }

    void Region::setCenter(int64_t x, int64_t y, int64_t z) {
        centerX = x;
        centerY = y;
        centerZ = z;
        
        reload();
    }
    
//    void Region::generateChunk() {
//        if(toGenerate.empty())
//            return;
//
//        Geometry::Location ck = toGenerate.top();
//        toGenerate.pop();
//        
//        std::shared_ptr<Chunk> chunk; 
//        generator.generateChunk(chunk, ck);
//
//        {
//            std::lock_guard<std::mutex> lock(chunk_map_mutex);
//            chunk_map.insert({ck, chunk});
//        }
//    }

    void Region::reload() {
        makeQueue(Settings::renderDistance);
        
        for(auto it = chunks.begin(); it != chunks.end();) {
            if(getDistanceFromCenter(it->first) > Settings::renderDistance) {
                it = chunks.erase(it);
            } else {
                ++it;
            }
        }
        
        
            
    }
}



