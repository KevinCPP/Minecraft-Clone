#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "AxisAlignedBoundingBox.h"
#include "Geometry.h"

namespace Geometry {

    struct Frustum {
        std::array<glm::vec4, 6> planes;

        Frustum();
        Frustum(const glm::mat4& mvp);
        void update(const glm::mat4& mvp);
        bool isInsideFrustum(const AxisAlignedBoundingBox& aabb) const;
    };

}

#endif
