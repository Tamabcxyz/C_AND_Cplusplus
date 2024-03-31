
#include <bitset>
#include <iostream>

int main() {
    unsigned int a = 5;   // Binary: 0101
    unsigned int b = 3;   // Binary: 0011
    std::cout << "a binary: " << std::bitset<4>(a) << std::endl;
    std::cout << "b binary: " << std::bitset<4>(b) << std::endl;

    std::cout << "a & b = " << std::bitset<4>(a & b) <<std::endl;   // Bitwise AND
    std::cout << "a | b = %" << std::bitset<4>(a | b)<<std::endl;   // Bitwise OR
    std::cout << "a ^ b = " << std::bitset<4>(a ^ b)<<std::endl;    // Bitwise XOR
    std::cout << "~a = " << std::bitset<4>(~a)<<std::endl;          // Bitwise NOT
    std::cout << "a << 1 = " << std::bitset<4>((a << 1))<<std::endl;// Left Shift
    std::cout << "a >> 1 = " << std::bitset<4>((a >> 1))<<std::endl;// Right Shift

    return 0;
}

// set bit test bit and clear bit
/**
 * & for test bit
 * | for set bit
 * & use to test and clear of bit (set the bit to zero) not use for set bit ==> bit nào muốn clear cho mark = 0, bit nào không clear mark = 1
 * ^ XOR
 * I have state bool
 * state=0
 * state ^ 1 = 1; (state ^= 1;)
 * state = 1;
 * state ^ 1 = 0; (state ^= 1;)
 * ==>using XOR to change state
*/