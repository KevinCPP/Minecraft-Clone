#include "AxisAlignedBoundingBox.h"

namespace Geometry {
    AxisAlignedBoundingBox::AxisAlignedBoundingBox() {
        min = glm::vec3(0.0f);
        max = min;
    }

    AxisAlignedBoundingBox::AxisAlignedBoundingBox(const glm::vec3& minimum, const glm::vec3& maximum) {
        min = minimum;
        max = maximum;
    }

    AxisAlignedBoundingBox::AxisAlignedBoundingBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
        : AxisAlignedBoundingBox(glm::vec3(minX, minY, minZ), glm::vec3(maxX, maxY, maxZ)) { }


    bool AxisAlignedBoundingBox::intersects(const AxisAlignedBoundingBox& other) const {
        if(max.x < other.min.x || other.max.x < min.x)
            return false;
        if(max.y < other.min.y || other.max.y < min.y)
            return false;
        if(max.z < other.min.z || other.max.z < min.z)
            return false;

        return true;
    }
}
