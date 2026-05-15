#pragma once

#include "cpu_registers.hpp"
#include "opcodes.hpp"

class Bus;

enum class Addressing_Mode
{
    IMP, // Implied

    IMM,    // Immediate (8-bit)
    IMM_M, // Immediate (Accumulator Width)
    IMM_X, // Immediate (Index Width)

    ABS, // Absolute
    ABI, // Absolute Indirect
    ABX, // Absolute Indexed X
    ABY, // Absolute Indexed Y
    ABIX, // Absolute Indirect Indexed X

    ABL, // Absolute Long
    ABIL, // Absolute Indirect Long
    ALX, // Absolute Long Indexed X

    DP,  // Direct Page
    DPX, // Direct Page Indexed X
    DPY, // Direct Page Indexed Y

    DPI,  // Direct Page Indirect
    DPIX, // Direct Page Indexed Indirect X
    DPIY, // Direct Page Indirect Indexed Y

    DPIL,  // Direct Page Indirect Long
    DPILY, // Direct Page Indirect Long Indexed Y

    SR,   // Stack Relative
    SRIY, // Stack Relative Indirect Indexed Y

    REL, // Program Counter Relative
    RELL, // Program Counter Relative Long

    ACC,         // Accumulator
    INTR         // Interrupt
};

class CPU
{
private:
    Bus *bus;
    CPU_Registers registers;

    Instruction fetch_instruction();

    void get_addressing_mode();

    // Interrupts
    void check_interrupt_pending();
    void handle_interrupt();

    // Stack Helpers
    void push8(uint8_t data);
    void push16(uint16_t data);
    uint8_t pop8();
    uint16_t pop16();

public:
    void initialise();
    void reset();
    void step();

    void connect_bus(Bus *bus);
};