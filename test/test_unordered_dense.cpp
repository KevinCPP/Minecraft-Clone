#include <bits/stdc++.h>
#include <ankerl/unordered_dense.h>

enum Direction : uint8_t {
    TOP = 0,
    LEFT,
    BACK,
    RIGHT,
    FRONT,
    BOTTOM
};

int main() {
    std::tuple<uint16_t, uint16_t, uint16_t, uint8_t> quadData;
    uint16_t x = 1, y = 2, z = 3;
    uint8_t dir = (uint8_t)TOP;

    quadData = std::make_tuple(x, y, z, dir); 

    //ankerl::unordered_dense::set<std::tuple<uint16_t, uint16_t, uint16_t, uint8_t>> unorderedTest; 
    std::unordered_set<std::tuple<uint16_t, uint16_t, uint16_t, uint8_t>> stdUnorderedTest;
    return 0;
}
