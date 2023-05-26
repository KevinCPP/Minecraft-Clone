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

    bool AxisAlignedBoundingBox::intersectsFrustum(const glm::mat4& viewProjectionMatrix, float scaleFactor) const {
        glm::vec4 clipSpaceCorners[8] = {
            viewProjectionMatrix * glm::vec4(min.x, min.y, min.z, scaleFactor),
            viewProjectionMatrix * glm::vec4(min.x, min.y, max.z, scaleFactor),
            viewProjectionMatrix * glm::vec4(min.x, max.y, min.z, scaleFactor),
            viewProjectionMatrix * glm::vec4(min.x, max.y, max.z, scaleFactor),
            viewProjectionMatrix * glm::vec4(max.x, min.y, min.z, scaleFactor),
            viewProjectionMatrix * glm::vec4(max.x, min.y, max.z, scaleFactor),
            viewProjectionMatrix * glm::vec4(max.x, max.y, min.z, scaleFactor),
            viewProjectionMatrix * glm::vec4(max.x, max.y, max.z, scaleFactor),
        };

        for (int i = 0; i < 6; ++i) {
            int out = 0;
            for (int j = 0; j < 8; ++j) {
                glm::vec4 corner = clipSpaceCorners[j] / clipSpaceCorners[j].w;
                switch(i) {
                    case 0: if(corner.x > 1.0f) out++; break;
                    case 1: if(corner.x < -1.0f) out++; break;
                    case 2: if(corner.y > 1.0f) out++; break;
                    case 3: if(corner.y < -1.0f) out++; break;
                    case 4: if(corner.z > 1.0f) out++; break;
                    case 5: if(corner.z < -1.0f) out++; break;
                }
            }
            if(out == 8)
                return false;
        }

        return true;
    }

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
