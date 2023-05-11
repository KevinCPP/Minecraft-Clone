#include "../include/BlockData.h"

namespace Blocks {
    BlockData::BlockData(uint8_t ID) {
        ItemID = ID;
        type = Type::FULL;
        state = State::SOLID;
        direction = Direction::NORTH;
        isTransparent = false;
        hasCollision = true;
    }

    BlockData::BlockData(uint8_t ID, bool transparent, bool collision) : BlockData(ID) {
        isTransparent = transparent;
        hasCollision = collision;
    }
    
    BlockData::BlockData(uint8_t ID, Type t, State s, Direction d, bool transparent, bool collision) {
        ItemID = ID;
        type = t;
        state = s;
        direction = d;
        isTransparent = transparent;
        hasCollision = collision;
    }

    using AABB = Geometry::AxisAlignedBoundingBox;

    void BlockData::setCollisionBoxes(AABB box) {
        collisionBoxes = box; 
    }
 
    void BlockData::setCollisionBoxes(std::pair<AABB, AABB> boxes) {
        collisionBoxes = boxes;
    }

    void BlockData::setCollisionBoxes(std::tuple<AABB, AABB, AABB> boxes) {
        collisionBoxes = boxes;
    }

    void BlockData::setCollisionBoxes(std::vector<AABB> boxes) {
        collisionBoxes = boxes;
    }

}
