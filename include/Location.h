#ifndef LOCATION_H
#define LOCATION_H

#include "Geometry.h"

namespace Geometry {
    struct Location {
        int64_t x, y, z;

        Location(int64_t X, int64_t Y, int64_t Z) : x(X), y(Y), z(Z) {}

        bool operator==(const Location& other) const {
            return x == other.x && y == other.y && z == other.z;
        }
    };

    struct Location_hash_avalanching {
        using is_avalanching = void;

        uint64_t operator()(const Location& obj) const noexcept;
    }

    
}

#endif
