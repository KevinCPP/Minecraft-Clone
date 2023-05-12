#ifndef BLOCKATTRIBUTES_H
#define BLOCKATTRIBUTES_H

#include <variant>
#include <vector>
#include <tuple>

#include "Block.h"
#include "AxisAlignedBoundingBox.h"

namespace Blocks {
 
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
    struct BlockAttributes {
        Material ItemID;

        // stores some basic info about the block
        Type type;
        State state;
    
        bool isTransparent;
        bool hasCollision;
    
        // using declaration for less typing
        using AABB = Geometry::AxisAlignedBoundingBox;

        // a BlockAttributes object can either have no collision boxes,
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
        BlockAttributes();
        BlockAttributes(const Material& ID);
        BlockAttributes(const Material& ID, bool transparent, bool collision);
        BlockAttributes(const Material& ID, Type t, State s, bool transparent, bool collision);

        // methods for setting the collision boxes
        void setCollisionBoxes(AABB box);
        void setCollisionBoxes(std::pair<AABB, AABB> boxes);
        void setCollisionBoxes(std::tuple<AABB, AABB, AABB> boxes);
        void setCollisionBoxes(std::vector<AABB> boxes);
    };
}

#endif
