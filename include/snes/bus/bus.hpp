#pragma once
#include <cstdint>

class Bus
{
    public:

    // All addresses are 24-bit, the function take 32-bit to accommodate this. 
    //Upper-most 8-bits are set to 0 to ensure correct behaviour
    uint8_t read8(uint32_t address);
    uint16_t read16(uint32_t address);

    void write8(uint32_t address, uint8_t data);
    void write16(uint32_t address, uint16_t data);
    private:

};