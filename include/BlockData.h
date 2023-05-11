#ifndef BLOCKDATA_H
#define BLOCKDATA_H

#include <variant>
#include <vector>
#include <tuple>

#include "AxisAlignedBoundingBox.h"

namespace Blocks {

    // Direction the block is facing
    enum class Direction : uint8_t {
        NORTH = 0,
        SOUTH,
        EAST,
        WEST,
        DOWN,
        UP
    };

    // State of matter the block is in
    enum class State : uint8_t {
        SOLID = 0,
        LIQUID,
        GAS
    };

    // what type of block is it (full block, X-block, or empty)
    enum class Type : uint8_t {
        FULL = 0,
        BILLBOARD,
        EMPTY
    };
    
    // struct that stores the actual data for a block
    struct BlockData {
        uint8_t ItemID; // stores the ItemID of the block
       
        // stores some basic info about the block
        Type type;
        State state;
        Direction direction;
    
        bool isTransparent;
        bool hasCollision;
    
        // using declaration for less typing
        using AABB = Geometry::AxisAlignedBoundingBox;

        // a BlockData object can either have no collision boxes,
        // one collision box, a pair of collision boxes, a tuple of 3 collision boxes,
        // or a vector of many collision boxes. This adds greater flexibility to the struct,
        // so it can still be used for blocks that need more than one collision box,
        // but blocks that don't do not gain the additional overhead
        std::variant<
            AABB,
            std::pair<AABB, AABB>,
            std::tuple<AABB, AABB, AABB>,
            std::vector<AABB> > collisionBoxes;

        // constructors
        BlockData(uint8_t ID);
        BlockData(uint8_t ID, bool transparent, bool collision);
        BlockData(uint8_t ID, Type t, State s, Direction d, bool transparent, bool collision);

        // methods for setting the collision boxes
        void setCollisionBoxes(AABB box);
        void setCollisionBoxes(std::pair<AABB, AABB> boxes);
        void setCollisionBoxes(std::tuple<AABB, AABB, AABB> boxes);
        void setCollisionBoxes(std::vector<AABB> boxes);
    };
}

#endif
