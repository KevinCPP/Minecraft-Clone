#ifndef REGION_H
#define REGION_H

#include <mutex>
#include <queue>
#include <unordered_map>

#include <glm/glm.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include "../vendor/fastnoiselite.h"

#include "Cube.h"
#include "World.h"
#include "Chunk.h"
#include "Frustum.h"
#include "Settings.h"
#include "CubeFactory.h"
#include "ChunkGenerator.h"


namespace World {
    
    // custom point to be used for priority queue
    struct Point {
        int16_t distance;
        Geometry::Location value;

        Point(int16_t dist, Geometry::Location value) : distance(dist), value(std::move(value)) {}
    };
    
    struct PointComparator {
        bool operator()(const Point& lhs, const Point& rhs) const {
            return lhs.distance > rhs.distance;
        }
    };

    class Region {
    private:
        // hash map that will store all of the loaded chunks in the region
        std::unordered_map<Geometry::Location, std::shared_ptr<Chunk>, Geometry::Location_hash_avalanching> chunks;
        
        // stores the list of chunks to generate, where lower distance from center = higher priority
        std::priority_queue<Point, std::vector<Point>, PointComparator> toGenerate;
        
        // regenerates the priority queue
        void makeQueue(int16_t radius);
        
        // multi-threadded function that generates the next chunk in the queue
        void generateChunk();

        // calculates the distance from the center, of either a given
        // point, or the point stored within a Geometry::Location object.
        uint64_t getDistanceFromCenter(int64_t x, int64_t y, int64_t z);
        uint64_t getDistanceFromCenter(Geometry::Location key);
        
        // object that will generate the chunks for us.
        ChunkGenerator generator;

        // multi threading stuff
        std::mutex chunk_map_mutex;
        boost::thread_group workers;
        std::condition_variable cv;
        std::atomic<bool> generating;

        // stores the center point that we're rendering around
        int64_t centerX;
        int64_t centerY;
        int64_t centerZ;
    public:
        // initialize a region with x, y, and z coordinates. Defaults to (0, 0, 0).
        Region(int64_t x = 0, int64_t y = 0, int64_t z = 0);
        ~Region();

        // sets the center of the region and reloads it
        void setCenter(int64_t x, int64_t y, int64_t z);

        // reloads the region
        void reload();
        
        // renders all the chunks in the region
        void render(const Renderer& renderer, Shader& shader, const Geometry::Frustum& frustum, bool frustumCulling = true);
    };
}

#endif
