#include "opcodes.hpp"

void CPU::LDA()
{
    uint16_t data;
    if (registers.get_accum_size_flag())
    {
        data = read8(effective_address);
        registers.a = (registers.a & 0xFF00) | (data & 0x00FF);

        registers.set_zero_flag((registers.a & 0xFF) == 0);
        registers.set_negative_flag(registers.a & 0x80);
    }
    else
    {
        data = read16(effective_address);
        registers.a = data;

        registers.set_zero_flag(registers.a == 0);
        registers.set_negative_flag(registers.a & 0x8000);

        add_extra_cycles(1);
    }
}

void CPU::STA()
{
    if (registers.get_accum_size_flag())
    {
        write8(effective_address, registers.a & 0xFF);
    }
    else
    {
        write16(effective_address, registers.a);
        add_extra_cycles(1);
    }
}

void CPU::LDX()
{
    uint16_t data;
    if (registers.get_index_size_flag())
    {
        data = read8(effective_address);
        registers.x = (registers.x & 0xFF00) | (data & 0x00FF);

        registers.set_zero_flag((registers.x & 0xFF) == 0);
        registers.set_negative_flag(registers.x & 0x80);
    }
    else
    {
        data = read16(effective_address);
        registers.x = data;

        registers.set_zero_flag(registers.x == 0);
        registers.set_negative_flag(registers.x & 0x8000);

        add_extra_cycles(1);
    }
}

void CPU::LDY()
{
    uint16_t data;
    if (registers.get_index_size_flag())
    {
        data = read8(effective_address);
        registers.y = (registers.y & 0xFF00) | (data & 0x00FF);

        registers.set_zero_flag((registers.y & 0xFF) == 0);
        registers.set_negative_flag(registers.y & 0x80);
    }
    else
    {
        data = read16(effective_address);
        registers.y = data;

        registers.set_zero_flag(registers.y == 0);
        registers.set_negative_flag(registers.y & 0x8000);

        add_extra_cycles(1);
    }
}

void initialise_instructions()
{

    opcode_table[0x00] =
        {
            "BRK", Addressing_Mode::INTR, 7,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x01] =
        {
            "ORA (dp,X)", Addressing_Mode::DPIX, 6, // conditional cycles
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x02] =
        {
            "COP #const", Addressing_Mode::INTR, 7, // cond
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x03] =
        {
            "ORA sr,S", Addressing_Mode::SR, 4, // cond
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x04] =
        {
            "TSB dp", Addressing_Mode::DP, 5, // cond
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x05] =
        {
            "ORA dp", Addressing_Mode::DP, 3, // cond
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x06] =
        {
            "ASL dp", Addressing_Mode::DP, 5, // cond
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x07] =
        {
            "ORA [dp]", Addressing_Mode::DPIL, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x08] =
        {
            "PHP", Addressing_Mode::IMP, 3,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x09] =
        {
            "ORA #const", Addressing_Mode::IMM_M, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x0A] =
        {
            "ASL A", Addressing_Mode::ACC, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x0B] =
        {
            "PHD", Addressing_Mode::IMP, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x0C] =
        {
            "TSB addr", Addressing_Mode::ABS, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x0D] =
        {
            "ORA addr", Addressing_Mode::ABS, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x0E] =
        {
            "ASL addr", Addressing_Mode::ABS, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x0F] =
        {
            "ORA long", Addressing_Mode::ABL, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x10] =
        {
            "BPL near", Addressing_Mode::REL, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x11] =
        {
            "ORA (dp), Y", Addressing_Mode::DPIY, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x12] =
        {
            "ORA (dp)", Addressing_Mode::DPI, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x13] =
        {
            "ORA (sr, S), Y", Addressing_Mode::SRIY, 7,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x14] =
        {
            "TRB dp", Addressing_Mode::DP, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x15] =
        {
            "ORA dp, X", Addressing_Mode::DPX, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x16] =
        {
            "ASL dp, X", Addressing_Mode::DPX, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x17] =
        {
            "ORA [dp], Y", Addressing_Mode::DPILY, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x18] =
        {
            "CLC", Addressing_Mode::IMP, 2,
            [](CPU &cpu, Bus &bus)
            {
                cpu.registers.set_carry_flag(0);
            }};

    opcode_table[0x19] =
        {
            "ORA addr, Y", Addressing_Mode::ABY, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x20] =
        {
            "JSR addr", Addressing_Mode::ABS, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x21] =
        {
            "AND (dp, X)", Addressing_Mode::DPIX, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x22] =
        {
            "JSL long", Addressing_Mode::ABL, 8,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x23] =
        {
            "AND sr, S", Addressing_Mode::SR, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x24] =
        {
            "BIT dp", Addressing_Mode::DP, 3,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x25] =
        {
            "AND dp", Addressing_Mode::DP, 3,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x26] =
        {
            "ROL dp", Addressing_Mode::DP, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x27] =
        {
            "AND [dp]", Addressing_Mode::DPIL, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x28] =
        {
            "PLP", Addressing_Mode::IMP, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x29] =
        {
            "AND #const", Addressing_Mode::IMM_M, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x2A] =
        {
            "ROL", Addressing_Mode::ACC, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x2B] =
        {
            "PLD", Addressing_Mode::IMP, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x2C] =
        {
            "BIT addr", Addressing_Mode::ABS, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x2D] =
        {
            "AND addr", Addressing_Mode::ABS, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x2E] =
        {
            "ROL addr", Addressing_Mode::ABS, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x2F] =
        {
            "AND long", Addressing_Mode::ABL, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x30] =
        {
            "BMI near", Addressing_Mode::REL, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x31] =
        {
            "AND (dp, X)", Addressing_Mode::DPIY, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x32] =
        {
            "AND (dp)", Addressing_Mode::DPI, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x33] =
        {
            "AND (sr, S), Y", Addressing_Mode::SRIY, 7,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x34] =
        {
            "BIT dp, X", Addressing_Mode::DPX, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x35] =
        {
            "AND dp, X", Addressing_Mode::DPX, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x36] =
        {
            "ROL dp, X", Addressing_Mode::DPX, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x37] =
        {
            "AND [dp], Y", Addressing_Mode::DPILY, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x38] =
        {
            "SEC", Addressing_Mode::IMP, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x39] =
        {
            "AND addr, Y", Addressing_Mode::ABY, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x3A] =
        {
            "DEC", Addressing_Mode::ACC, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x3B] =
        {
            "TSC", Addressing_Mode::IMP, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x3C] =
        {
            "BIT addr, X", Addressing_Mode::ABX, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x3D] =
        {
            "AND addr, X", Addressing_Mode::ABX, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x3E] =
        {
            "ROL addr, X", Addressing_Mode::ABX, 7,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x3F] =
        {
            "AND long, X", Addressing_Mode::ALX, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x40] =
        {
            "RTI", Addressing_Mode::IMP, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x41] =
        {
            "EOR (dp, X)", Addressing_Mode::DPIX, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x42] =
        {
            "WDM", Addressing_Mode::IMP, 2,
            [](CPU &cpu, Bus &bus)
            {
                // Reserved Instruction
            }};

    opcode_table[0x43] =
        {
            "EOR sr, S", Addressing_Mode::SR, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x44] =
        {
            "MVP srcBank, destBank", Addressing_Mode::IMP, 7, // 7 cycles per byte moved
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x45] =
        {
            "EOR dp", Addressing_Mode::DP, 3,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x46] =
        {
            "LSR dp", Addressing_Mode::DP, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x47] =
        {
            "EOR [dp]", Addressing_Mode::DPIL, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x48] =
        {
            "PHA", Addressing_Mode::IMP, 3,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x49] =
        {
            "EOR #const", Addressing_Mode::IMM_M, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x4A] =
        {
            "LSR", Addressing_Mode::ACC, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x4B] =
        {
            "PHK", Addressing_Mode::IMP, 3,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x4C] =
        {
            "JMP addr", Addressing_Mode::ABS, 3,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x4D] =
        {
            "EOR addr", Addressing_Mode::ABS, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x4E] =
        {
            "LSR addr", Addressing_Mode::ABS, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x4F] =
        {
            "EOR long", Addressing_Mode::ABL, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x50] =
        {
            "BVC near", Addressing_Mode::REL, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x51] =
        {
            "EOR (dp), Y", Addressing_Mode::DPIY, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x52] =
        {
            "EOR (dp)", Addressing_Mode::DPI, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x53] =
        {
            "EOR (sr, S), Y", Addressing_Mode::SRIY, 7,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x54] =
        {
            "MVN srcBank, destBank", Addressing_Mode::IMP, 7, // 7 cycles per byte moved
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x55] =
        {
            "EOR dp, X", Addressing_Mode::DPX, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x56] =
        {
            "LSR dp, X", Addressing_Mode::DPX, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x57] =
        {
            "EOR [dp], Y", Addressing_Mode::DPILY, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x58] =
        {
            "CLI", Addressing_Mode::IMP, 2,
            [](CPU &cpu, Bus &bus)
            {
                cpu.registers.set_irq_disable_flag(0);
            }};

    opcode_table[0x59] =
        {
            "EOR addr, Y", Addressing_Mode::ABY, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x5A] =
        {
            "PHY", Addressing_Mode::IMP, 3,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x5B] =
        {
            "TCT", Addressing_Mode::IMP, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x5C] =
        {
            "JML long", Addressing_Mode::ABL, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x5D] =
        {
            "EOR addr, X", Addressing_Mode::ABX, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x5E] =
        {
            "LSR addr, X", Addressing_Mode::ABX, 7,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x5F] =
        {
            "EOR long, X", Addressing_Mode::ALX, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x60] =
        {
            "RTS", Addressing_Mode::IMP, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x61] =
        {
            "ADC (dp, X)", Addressing_Mode::DPX, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x62] =
        {
            "PER label", Addressing_Mode::RELL, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x63] =
        {
            "ADC sr, S", Addressing_Mode::SR, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x64] =
        {
            "STZ dp", Addressing_Mode::DP, 3,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x65] =
        {
            "ADC dp", Addressing_Mode::DP, 3,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x66] =
        {
            "ROR dp", Addressing_Mode::DP, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x67] =
        {
            "ADC [dp]", Addressing_Mode::DPIL, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x68] =
        {
            "PLA", Addressing_Mode::IMP, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x69] =
        {
            "ADC #const", Addressing_Mode::IMM_M, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x6A] =
        {
            "ROR", Addressing_Mode::ACC, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x6B] =
        {
            "RTL", Addressing_Mode::IMP, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x6C] =
        {
            "JMP (addr)", Addressing_Mode::ABI, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x6D] =
        {
            "ADC addr", Addressing_Mode::ABS, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x6E] =
        {
            "ROR addr", Addressing_Mode::ABS, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x6F] =
        {
            "ADC long", Addressing_Mode::ABL, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x70] =
        {
            "BVS near", Addressing_Mode::REL, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x71] =
        {
            "ADC (dp), Y", Addressing_Mode::DPIY, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x72] =
        {
            "ADC (dp)", Addressing_Mode::DPI, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x73] =
        {
            "ADC (sr, S), Y", Addressing_Mode::SRIY, 7,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x74] =
        {
            "STZ dp, X", Addressing_Mode::DPX, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x75] =
        {
            "ADC dp, X", Addressing_Mode::DPX, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x76] =
        {
            "ROR dp, X", Addressing_Mode::DPX, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x77] =
        {
            "ADC [dp], Y", Addressing_Mode::DPILY, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x78] =
        {
            "SEI", Addressing_Mode::IMP, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x79] =
        {
            "ADC addr, Y", Addressing_Mode::ABY, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x7A] =
        {
            "PLY", Addressing_Mode::IMP, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x7B] =
        {
            "TDC", Addressing_Mode::IMP, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x7C] =
        {
            "JMP (addr, X)", Addressing_Mode::ABIX, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x7D] =
        {
            "ADC addr, X", Addressing_Mode::ABX, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x7E] =
        {
            "ROR addr, X", Addressing_Mode::ABX, 7,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x7F] =
        {
            "ADC long, X", Addressing_Mode::ALX, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x80] =
        {
            "BRA near", Addressing_Mode::REL, 3,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x81] =
        {
            "STA (dp, X)", Addressing_Mode::DPIX, 6,
            [](CPU &cpu, Bus &bus) {
                cpu.STA();

                if ((cpu.registers.dp & 0x00FF) != 0)
                    cpu.add_extra_cycles(1);
            }};

    opcode_table[0x82] =
        {
            "BRL label", Addressing_Mode::RELL, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x83] =
        {
            "STA sr, S", Addressing_Mode::SR, 4,
            [](CPU &cpu, Bus &bus) {
                cpu.STA();
            }};

    opcode_table[0x84] =
        {
            "STY dp", Addressing_Mode::DP, 3,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x85] =
        {
            "STA dp", Addressing_Mode::DP, 3,
            [](CPU &cpu, Bus &bus) {
                cpu.STA();

                if ((cpu.registers.dp & 0x00FF) != 0)
                    cpu.add_extra_cycles(1);
            }};

    opcode_table[0x86] =
        {
            "STX dp", Addressing_Mode::DP, 3,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x87] =
        {
            "STA [dp]", Addressing_Mode::DPIL, 6,
            [](CPU &cpu, Bus &bus) {
                cpu.STA();

                if ((cpu.registers.dp & 0x00FF) != 0)
                    cpu.add_extra_cycles(1);
            }};

    opcode_table[0x88] =
        {
            "DEY", Addressing_Mode::IMP, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x89] =
        {
            "BIT #const", Addressing_Mode::IMM_M, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x8A] =
        {
            "TXA", Addressing_Mode::IMP, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x8B] =
        {
            "PHB", Addressing_Mode::IMP, 3,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x8C] =
        {
            "STY addr", Addressing_Mode::ABS, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x8D] =
        {
            "STA addr", Addressing_Mode::ABS, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x8E] =
        {
            "STX addr", Addressing_Mode::ABS, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x8F] =
        {
            "STA long", Addressing_Mode::ABL, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x90] =
        {
            "BCC near", Addressing_Mode::REL, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x91] =
        {
            "STA (dp), Y", Addressing_Mode::DPIY, 6,
            [](CPU &cpu, Bus &bus) {
                cpu.STA();

                if ((cpu.registers.dp & 0x00FF) != 0)
                    cpu.add_extra_cycles(1);
            }};

    opcode_table[0x92] =
        {
            "STA (dp)", Addressing_Mode::DPI, 5,
            [](CPU &cpu, Bus &bus) {
                cpu.STA();

                if ((cpu.registers.dp & 0x00FF) != 0)
                    cpu.add_extra_cycles(1);
            }};

    opcode_table[0x93] =
        {
            "STA (sr, S), Y", Addressing_Mode::SRIY, 7,
            [](CPU &cpu, Bus &bus) {
                cpu.STA();
            }};

    opcode_table[0x94] =
        {
            "STY dp, X", Addressing_Mode::DPX, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x95] =
        {
            "STA dp, X", Addressing_Mode::DPX, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x96] =
        {
            "STX dp, Y", Addressing_Mode::DPY, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x97] =
        {
            "STA [dp], Y", Addressing_Mode::DPILY, 6,
            [](CPU &cpu, Bus &bus) {
                cpu.STA();

                if ((cpu.registers.dp & 0x00FF) != 0)
                    cpu.add_extra_cycles(1);
            }};

    opcode_table[0x98] =
        {
            "TYA", Addressing_Mode::IMP, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x99] =
        {
            "STA addr, Y", Addressing_Mode::ABY, 5,
            [](CPU &cpu, Bus &bus) {
                cpu.STA();
            }};

    opcode_table[0x9A] =
        {
            "TXS", Addressing_Mode::IMP, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x9B] =
        {
            "TXY", Addressing_Mode::IMP, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x9C] =
        {
            "STZ addr", Addressing_Mode::ABS, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x9D] =
        {
            "STA addr, X", Addressing_Mode::ABX, 5,
            [](CPU &cpu, Bus &bus) {
                cpu.STA();
            }};

    opcode_table[0x9E] =
        {
            "STZ addr, X", Addressing_Mode::ABX, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0x9F] =
        {
            "STA long, X", Addressing_Mode::ALX, 5,
            [](CPU &cpu, Bus &bus) {
                cpu.STA();
            }};

    opcode_table[0xA0] =
        {
            "LDY #const", Addressing_Mode::IMM_X, 2,
            [](CPU &cpu, Bus &bus) {
                cpu.LDY();
            }};

    opcode_table[0xA1] =
        {
            "LDA (dp, X)", Addressing_Mode::DPIX, 6,
            [](CPU &cpu, Bus &bus)
            {
                cpu.LDA();

                if ((cpu.registers.dp & 0x00FF) != 0)
                    cpu.add_extra_cycles(1);
            }};

    opcode_table[0xA2] =
        {
            "LDX #const", Addressing_Mode::IMM_X, 2,
            [](CPU &cpu, Bus &bus) {
                cpu.LDX();
            }};

    opcode_table[0xA3] =
        {
            "LDA sr, S", Addressing_Mode::SR, 4,
            [](CPU &cpu, Bus &bus)
            {
                cpu.LDA();
            }};

    opcode_table[0xA4] =
        {
            "LDY dp", Addressing_Mode::DP, 3,
            [](CPU &cpu, Bus &bus) {
                cpu.LDY();

                if ((cpu.registers.dp & 0x00FF) != 0)
                    cpu.add_extra_cycles(1);
            }};

    opcode_table[0xA5] =
        {
            "LDA dp", Addressing_Mode::DP, 3,
            [](CPU &cpu, Bus &bus)
            {
                cpu.LDA();
            }};

    opcode_table[0xA6] =
        {
            "LDX dp", Addressing_Mode::DP, 3,
            [](CPU &cpu, Bus &bus) {
                cpu.LDX();

                if ((cpu.registers.dp & 0x00FF) != 0)
                    cpu.add_extra_cycles(1);
            }};

    opcode_table[0xA7] =
        {
            "LDA [dp]", Addressing_Mode::DPIL, 6,
            [](CPU &cpu, Bus &bus)
            {
                cpu.LDA();
            }};

    opcode_table[0xA8] =
        {
            "TAY", Addressing_Mode::IMP, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xA9] =
        {
            "LDA #const", Addressing_Mode::IMM_M, 2,
            [](CPU &cpu, Bus &bus)
            {
                cpu.LDA();
            }};

    opcode_table[0xAA] =
        {
            "TAX", Addressing_Mode::IMP, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xAB] =
        {
            "PLB", Addressing_Mode::IMP, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xAC] =
        {
            "LDY addr", Addressing_Mode::ABS, 4,
            [](CPU &cpu, Bus &bus) {
                cpu.LDY();
            }};

    opcode_table[0xAD] =
        {
            "LDA addr", Addressing_Mode::ABS, 4,
            [](CPU &cpu, Bus &bus)
            {
                cpu.LDA();
            }};

    opcode_table[0xAE] =
        {
            "LDX addr", Addressing_Mode::ABS, 4,
            [](CPU &cpu, Bus &bus) {
                cpu.LDX();
            }};

    opcode_table[0xAF] =
        {
            "LDA long", Addressing_Mode::ABL, 5,
            [](CPU &cpu, Bus &bus)
            {
                cpu.LDA();
            }};

    opcode_table[0xB0] =
        {
            "BCS near", Addressing_Mode::REL, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xB1] =
        {
            "LDA (dp), Y", Addressing_Mode::DPIY, 5,
            [](CPU &cpu, Bus &bus)
            {
                cpu.LDA();

                if ((cpu.registers.dp & 0x00FF) != 0)
                    cpu.add_extra_cycles(1);

                if (cpu.page_crossed)
                    cpu.add_extra_cycles(1);
            }};

    opcode_table[0xB2] =
        {
            "LDA (dp)", Addressing_Mode::DPI, 5,
            [](CPU &cpu, Bus &bus)
            {
                cpu.LDA();

                if ((cpu.registers.dp & 0x00FF) != 0)
                    cpu.add_extra_cycles(1);
            }};

    opcode_table[0xB3] =
        {
            "LDA (sr, S), Y", Addressing_Mode::SRIY, 7,
            [](CPU &cpu, Bus &bus)
            {
                cpu.LDA();
            }};

    opcode_table[0xB4] =
        {
            "LDY dp, X", Addressing_Mode::DPX, 4,
            [](CPU &cpu, Bus &bus) {
                cpu.LDY();

                if ((cpu.registers.dp & 0x00FF) != 0)
                    cpu.add_extra_cycles(1);
            }};

    opcode_table[0xB5] =
        {
            "LDA dp, X", Addressing_Mode::DPX, 4,
            [](CPU &cpu, Bus &bus)
            {
                cpu.LDA();

                if ((cpu.registers.dp & 0x00FF) != 0)
                    cpu.add_extra_cycles(1);
            }};

    opcode_table[0xB6] =
        {
            "LDX dp, Y", Addressing_Mode::DPY, 4,
            [](CPU &cpu, Bus &bus) {
                cpu.LDX();

                if ((cpu.registers.dp & 0x00FF) != 0)
                    cpu.add_extra_cycles(1);
            }};

    opcode_table[0xB7] =
        {
            "LDA [dp], Y", Addressing_Mode::DPILY, 6,
            [](CPU &cpu, Bus &bus)
            {
                cpu.LDA();

                if ((cpu.registers.dp & 0x00FF) != 0)
                    cpu.add_extra_cycles(1);
            }};

    opcode_table[0xB8] =
        {
            "CLV", Addressing_Mode::IMP, 2,
            [](CPU &cpu, Bus &bus)
            {
                cpu.registers.set_overflow_flag(0);
            }};

    opcode_table[0xB9] =
        {
            "LDA addr, Y", Addressing_Mode::ABY, 4,
            [](CPU &cpu, Bus &bus)
            {
                cpu.LDA();

                if (cpu.page_crossed)
                    cpu.add_extra_cycles(1);
            }};

    opcode_table[0xBA] =
        {
            "TSX", Addressing_Mode::IMP, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xBB] =
        {
            "TYX", Addressing_Mode::IMP, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xBC] =
        {
            "LDY addr, X", Addressing_Mode::ABX, 4,
            [](CPU &cpu, Bus &bus) {
                cpu.LDY();

                if (cpu.page_crossed)
                    cpu.add_extra_cycles(1);
            }};

    opcode_table[0xBD] =
        {
            "LDA addr, X", Addressing_Mode::ABX, 4,
            [](CPU &cpu, Bus &bus)
            {
                cpu.LDA();

                if (cpu.page_crossed)
                    cpu.add_extra_cycles(1);
            }};

    opcode_table[0xBE] =
        {
            "LDX addr, Y", Addressing_Mode::ABY, 4,
            [](CPU &cpu, Bus &bus) {
                cpu.LDX();

                if (cpu.page_crossed)
                    cpu.add_extra_cycles(1);
            }};

    opcode_table[0xBF] =
        {
            "LDA long, X", Addressing_Mode::ALX, 5,
            [](CPU &cpu, Bus &bus) {
                cpu.LDA();
            }};

    opcode_table[0xC0] =
        {
            "CPY #const", Addressing_Mode::IMM_X, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xC1] =
        {
            "CMP (dp, X)", Addressing_Mode::DPIX, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xC2] =
        {
            "REP #const", Addressing_Mode::IMM_8, 3,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xC3] =
        {
            "CMP sr, S", Addressing_Mode::SR, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xC4] =
        {
            "CPY dp", Addressing_Mode::DP, 3,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xC5] =
        {
            "CMP dp", Addressing_Mode::DP, 3,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xC6] =
        {
            "DEC dp", Addressing_Mode::DP, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xC7] =
        {
            "CMP [dp]", Addressing_Mode::DPIL, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xC8] =
        {
            "INY", Addressing_Mode::IMP, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xC9] =
        {
            "CMP #const", Addressing_Mode::IMM_M, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xCA] =
        {
            "DEX", Addressing_Mode::IMP, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xCB] =
        {
            "WAI", Addressing_Mode::IMP, 3,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xCC] =
        {
            "CPY addr", Addressing_Mode::ABS, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xCD] =
        {
            "CMP addr", Addressing_Mode::ABS, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xCE] =
        {
            "DEC addr", Addressing_Mode::ABS, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xCF] =
        {
            "CMP long", Addressing_Mode::ABL, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xD0] =
        {
            "BNE near", Addressing_Mode::REL, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xD1] =
        {
            "CMP (dp), Y", Addressing_Mode::DPIY, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xD2] =
        {
            "CMP (dp)", Addressing_Mode::DPI, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xD3] =
        {
            "CMP (sr, S), Y", Addressing_Mode::SRIY, 7,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xD4] =
        {
            "PEI (dp)", Addressing_Mode::DPI, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xD5] =
        {
            "CMP dp, X", Addressing_Mode::DPX, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xD6] =
        {
            "DEC dp, X", Addressing_Mode::DPX, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xD7] =
        {
            "CMP [dp], Y", Addressing_Mode::DPILY, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xD8] =
        {
            "CLD", Addressing_Mode::IMP, 2,
            [](CPU &cpu, Bus &bus)
            {
                cpu.registers.set_decimal_mode_flag(0);
            }};

    opcode_table[0xD9] =
        {
            "CMP addr, Y", Addressing_Mode::ABY, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xDA] =
        {
            "PHX", Addressing_Mode::IMP, 3,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xDB] =
        {
            "STP", Addressing_Mode::IMP, 3,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xDC] =
        {
            "JML [addr]", Addressing_Mode::ABIL, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xDD] =
        {
            "CMP addr, X", Addressing_Mode::ABX, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xDE] =
        {
            "DEC addr, X", Addressing_Mode::ABX, 7,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xDF] =
        {
            "CMP long, X", Addressing_Mode::ALX, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xE0] =
        {
            "CPX #const", Addressing_Mode::IMM_X, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xE1] =
        {
            "SBC (dp, X)", Addressing_Mode::DPIX, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xE2] =
        {
            "SEP #const", Addressing_Mode::IMM_8, 3,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xE3] =
        {
            "SBC sr, S", Addressing_Mode::SR, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xE4] =
        {
            "CPX dp", Addressing_Mode::DP, 3,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xE5] =
        {
            "SBC dp", Addressing_Mode::DP, 3,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xE6] =
        {
            "INC dp", Addressing_Mode::DP, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xE7] =
        {
            "SBC [dp]", Addressing_Mode::DPIL, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xE8] =
        {
            "INX", Addressing_Mode::IMP, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xE9] =
        {
            "SBC #const", Addressing_Mode::IMM_M, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xEA] =
        {
            "NOP", Addressing_Mode::IMP, 2,
            [](CPU &cpu, Bus &bus)
            {
                // Does nothing
            }};

    opcode_table[0xEB] =
        {
            "XBA", Addressing_Mode::IMP, 3,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xEC] =
        {
            "CPX addr", Addressing_Mode::ABS, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xED] =
        {
            "SBC addr", Addressing_Mode::ABS, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xEE] =
        {
            "INC addr", Addressing_Mode::ABS, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xEF] =
        {
            "SBC long", Addressing_Mode::ABL, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xF0] =
        {
            "BEQ near", Addressing_Mode::REL, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xF1] =
        {
            "SBC (dp), Y", Addressing_Mode::DPIY, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xF2] =
        {
            "SBC (dp)", Addressing_Mode::DPI, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xF3] =
        {
            "SBC (sr, S), Y", Addressing_Mode::SRIY, 7,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xF4] =
        {
            "PEA addr", Addressing_Mode::ABS, 5,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xF5] =
        {
            "SBC dp, X", Addressing_Mode::DPX, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xF6] =
        {
            "INC dp, X", Addressing_Mode::DPX, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xF7] =
        {
            "SBC [dp], Y", Addressing_Mode::DPILY, 6,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xF8] =
        {
            "SED", Addressing_Mode::IMP, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xF9] =
        {
            "SBC addr, Y", Addressing_Mode::ABY, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xFA] =
        {
            "PLX", Addressing_Mode::IMP, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xFB] =
        {
            "XCE", Addressing_Mode::IMP, 2,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xFC] =
        {
            "JSR (addr, X)", Addressing_Mode::ABIX, 8,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xFD] =
        {
            "SBC addr, X", Addressing_Mode::ABX, 4,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xFE] =
        {
            "INC addr, X", Addressing_Mode::ABX, 7,
            [](CPU &cpu, Bus &bus) {

            }};

    opcode_table[0xFF] =
        {
            "SBC long, X", Addressing_Mode::ALX, 5,
            [](CPU &cpu, Bus &bus) {

            }};
};
