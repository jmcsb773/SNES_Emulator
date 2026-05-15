#pragma once
#include <string>
#include <cstdint>
#include <functional>
#include <array>
#include "cpu.hpp"

struct Instruction
{
    std::string mnemonic;
    Addressing_Mode address_mode;
    uint8_t base_cycles;
    std::function<void(CPU &, Bus &)> execute;
};

// Stack helper functions
void push8(CPU &cpu, Bus &bus, uint8_t data);
void push16(CPU &cpu, Bus &bus, uint16_t data);
uint8_t pop8(CPU &cpu, Bus &bus);
uint16_t pop16(CPU &cpu, Bus &bus);

// Instructions ordered according to their respective opcode, accessed with their opcode
std::array<Instruction, 0x100> opcode_table;

void initialise_instructions();