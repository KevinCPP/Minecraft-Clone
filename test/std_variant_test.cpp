#include <bits/stdc++.h>

struct myStruct {
    uint64_t x;
    std::variant<std::monostate, uint64_t> optionalParam;
};

struct myStruct2 {
    uint64_t x;
};

struct myStruct3 {
    uint8_t x;
    uint8_t y;
};

int main() {
    myStruct test1;
    test1.x = 5;
    test1.optionalParam = (uint64_t)10;

    myStruct test2;
    test2.x = 5;

    std::cout << sizeof(myStruct3) << " " << sizeof(test1) << " " << sizeof(test2) << " " << sizeof(myStruct2) << std::endl; 
}
