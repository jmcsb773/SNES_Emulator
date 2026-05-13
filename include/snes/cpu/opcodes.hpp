#pragma once
#include <string>
#include <cstdint>
#include <functional>

class CPU;
class Bus;

struct Instruction
{
    uint8_t opcode;
    std::string mnemonic;
    uint8_t cycles;
    std::function<void(CPU &, Bus &)> execute;
};