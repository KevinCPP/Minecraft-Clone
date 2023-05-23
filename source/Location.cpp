
#include <ankerl/unordered_dense.h>

#include "Location.h"

namespace Geometry {
    
    // hashing function for location
    uint64_t Location_hash_avalanching::operator()(const Location& obj) const noexcept {
        uint64_t result = 0;
        result ^= ankerl::unordered_dense::detail::wyhash::hash(obj.x);
        result ^= ankerl::unordered_dense::detail::wyhash::hash(obj.y);
        result ^= ankerl::unordered_dense::detail::wyhash::hash(obj.z);
        return result;
    }
    

}
