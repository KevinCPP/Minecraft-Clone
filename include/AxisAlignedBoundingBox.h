#ifndef AXISALIGNEDBOUNDINGBOX_H
#define AXISALIGNEDBOUNDINGBOX_H

#include "Geometry.h"

namespace Geometry {

    struct AxisAlignedBoundingBox {
        glm::vec3 min;
        glm::vec3 max;

        AxisAlignedBoundingBox();
        AxisAlignedBoundingBox(const glm::vec3& min, const glm::vec3& max);
        AxisAlignedBoundingBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);

        bool intersects(const AxisAlignedBoundingBox& other) const;
    };

}

#endif
