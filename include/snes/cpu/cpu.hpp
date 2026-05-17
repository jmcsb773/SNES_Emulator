#pragma once

#include "bus.hpp"
#include "cpu_registers.hpp"
#include "opcodes.hpp"

class Bus;

enum class Addressing_Mode
{
    IMP,  // Implied
    ACC,  // Accumulator
    INTR, // Interrupt

    IMM_8, // Immediate (8-bit)
    IMM_M, // Immediate (Accumulator Width)
    IMM_X, // Immediate (Index Width)

    ABS,  // Absolute
    ABI,  // Absolute Indirect
    ABX,  // Absolute Indexed X
    ABY,  // Absolute Indexed Y
    ABIX, // Absolute Indirect Indexed X

    ABL,  // Absolute Long
    ABIL, // Absolute Indirect Long
    ALX,  // Absolute Long Indexed X

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
    RELL // Program Counter Relative Long
};

// Maps each addressing mode to its respective handler function to update necessary state according to mode specification
std::unordered_map<Addressing_Mode, void (CPU::*)()> addressing_mode_handlers;

class CPU
{
public:
    CPU_Registers registers;
    uint16_t effective_address = 0;
    bool page_crossed = false;

    void initialise();
    void reset();
    void step();

    // Used within instruction execution to add extra cycles conditional on execution state
    void add_extra_cycles(int cycles);

    // Base instruction functions
    // Performs the minimum operation of each instruction, defined in opcodes.cpp
    void LDA();
    void STA();
    void LDX();
    void LDY();

    void connect_bus(Bus *bus);

private:
    Bus *bus;

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

    // Bus helpers (TODO: MUST MAKE IT SO IT DOES WRAPPING WHEN NECESSARY CORRECTLY)
    void write8(uint32_t address, uint8_t data);
    void write16(uint32_t address, uint16_t data);
    uint8_t read8(uint32_t address);
    uint16_t read16(uint32_t address);

    // Addressing Mode Handler Functions
    // Each correctly increment pc as necessary, in addition to setting the effective address for the instruction execution
    void IMP();
    void ACC();
    void INTR();

    void IMM_8();
    void IMM_M();
    void IMM_X();

    void ABS();
    void ABI();
    void ABX();
    void ABY();
    void ABIX();

    void ABL();
    void ABIL();
    void ALX();

    void DP();
    void DPX();
    void DPY();

    void DPI();
    void DPIX();
    void DPIY();

    void DPIL();
    void DPILY();

    void SR();
    void SRIY();

    void REL();
    void RELL();
};