#include "../include/Frustum.h"

namespace Geometry {

    Frustum::Frustum() { }

    Frustum::Frustum(const glm::mat4& mvp) {
        update(mvp);
    }

    void Frustum::update(const glm::mat4& mvp) {
         // Left clipping plane
        planes[0] = glm::vec4(mvp[0][3] + mvp[0][0], mvp[1][3] + mvp[1][0], mvp[2][3] + mvp[2][0], mvp[3][3] + mvp[3][0]);
        // Right clipping plane
        planes[1] = glm::vec4(mvp[0][3] - mvp[0][0], mvp[1][3] - mvp[1][0], mvp[2][3] - mvp[2][0], mvp[3][3] - mvp[3][0]);
        // Top clipping plane
        planes[2] = glm::vec4(mvp[0][3] - mvp[0][1], mvp[1][3] - mvp[1][1], mvp[2][3] - mvp[2][1], mvp[3][3] - mvp[3][1]);
        // Bottom clipping plane
        planes[3] = glm::vec4(mvp[0][3] + mvp[0][1], mvp[1][3] + mvp[1][1], mvp[2][3] + mvp[2][1], mvp[3][3] + mvp[3][1]);
        // Near clipping plane
        planes[4] = glm::vec4(mvp[0][3] + mvp[0][2], mvp[1][3] + mvp[1][2], mvp[2][3] + mvp[2][2], mvp[3][3] + mvp[3][2]);
        // Far clipping plane
        planes[5] = glm::vec4(mvp[0][3] - mvp[0][2], mvp[1][3] - mvp[1][2], mvp[2][3] - mvp[2][2], mvp[3][3] - mvp[3][2]);

        // Normalize the plane equations if needed
        for(auto& plane : planes)
        {
            float length = glm::length(glm::vec3(plane));
            plane = plane / length;
        }  
    }

    bool Frustum::isInsideFrustum(const AxisAlignedBoundingBox& aabb) const {
        glm::vec3 minPosition = aabb.min;
        glm::vec3 maxPosition = aabb.max;
        
        glm::vec3 vertices[8] = {
            { minPosition.x, minPosition.y, minPosition.z },
            { maxPosition.x, minPosition.y, minPosition.z },
            { maxPosition.x, maxPosition.y, minPosition.z },
            { minPosition.x, maxPosition.y, minPosition.z },
            { minPosition.x, minPosition.y, maxPosition.z },
            { maxPosition.x, minPosition.y, maxPosition.z },
            { maxPosition.x, maxPosition.y, maxPosition.z },
            { minPosition.x, maxPosition.y, maxPosition.z },
        };

        for(const auto& plane : planes) {
            bool inside = false;

            for(const auto& vertex : vertices) {
                if(glm::dot(glm::vec3(plane), vertex) + plane.w >= 0) {
                    inside = true;
                    break;
                }
            }

            if(!inside)
                return false;
        }

        return true;
    }
}

