#include "../include/BlockAttributes.h"

namespace Blocks {
    BlockAttributes::BlockAttributes() {
        ItemID = AIR;
        type = Type::FULL;
        state = State::SOLID;
        isTransparent = false;
        hasCollision = true;
    }

    BlockAttributes::BlockAttributes(const Material& ID) {
        ItemID = ID;
        type = Type::FULL;
        state = State::SOLID;
        isTransparent = false;
        hasCollision = true;
    }

    BlockAttributes::BlockAttributes(const Material& ID, bool transparent, bool collision) : BlockAttributes(ID) {
        isTransparent = transparent;
        hasCollision = collision;
    }
    
    BlockAttributes::BlockAttributes(const Material& ID, Type t, State s, bool transparent, bool collision) {
        ItemID = ID;
        type = t;
        state = s;
        isTransparent = transparent;
        hasCollision = collision;
    }

    using AABB = Geometry::AxisAlignedBoundingBox;

    void BlockAttributes::setCollisionBoxes(AABB box) {
        collisionBoxes = box; 
    }
 
    void BlockAttributes::setCollisionBoxes(std::pair<AABB, AABB> boxes) {
        collisionBoxes = boxes;
    }

    void BlockAttributes::setCollisionBoxes(std::tuple<AABB, AABB, AABB> boxes) {
        collisionBoxes = boxes;
    }

    void BlockAttributes::setCollisionBoxes(std::vector<AABB> boxes) {
        collisionBoxes = boxes;
    }

}
