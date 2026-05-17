#include "cpu.hpp"

// The use of the addressing mode functions prevents repeating within the opcode table

void CPU::IMP()
{
    // consumes no operand bytes and computes no effective address
}

void CPU::ACC()
{
    // consumes no operand bytes and computes no effective address
}

void CPU::INTR()
{
    registers.pc += 1;
    // computes no effective adress
}

void CPU::IMM_8()
{
    effective_address = ((registers.pb << 16) | registers.pc);
    registers.pc += 1;
}

void CPU::IMM_M()
{
    if (registers.get_accum_size_flag())
    { // 8-bit size
        effective_address = ((registers.pb << 16) | registers.pc);
        registers.pc += 1;
    }
    else
    { // 16-bit size
        effective_address = ((registers.pb << 16) | registers.pc);
        registers.pc += 2;
    }
}

void CPU::IMM_X()
{
    if (registers.get_index_size_flag())
    { // 8-bit size
        effective_address = ((registers.pb << 16) | registers.pc);
        registers.pc += 1;
    }
    else
    { // 16-bit size
        effective_address = ((registers.pb << 16) | registers.pc);
        registers.pc += 2;
    }
}

void CPU::ABS()
{
    uint32_t read_addr = ((registers.pb << 16) | registers.pc);
    effective_address = read16(read_addr);
    registers.pc += 2;
}

void CPU::ABI()
{
    uint16_t read_addr = read16((registers.pb << 16) | registers.pc);
    effective_address = read16(read_addr);

    registers.pc += 2;
}

void CPU::ABX()
{
    uint32_t operand_addr = (registers.pb << 16) | registers.pc;

    uint16_t base_addr = read16(operand_addr);

    effective_address = base_addr + registers.x;

    page_crossed = ((base_addr & 0xFF00) != (effective_address & 0xFF00));

    registers.pc += 2;
}

void CPU::ABY()
{
    uint32_t operand_addr = (registers.pb << 16) | registers.pc;

    uint16_t base_addr = read16(operand_addr);

    effective_address = base_addr + registers.y;

    page_crossed = ((base_addr & 0xFF00) != (effective_address & 0xFF00));

    registers.pc += 2;
}

void CPU::ABIX()
{
    uint32_t operand_addr = (registers.pb << 16) | registers.pc;

    uint16_t pointer_addr = read16(operand_addr);

    pointer_addr += registers.x;

    effective_address = read16(pointer_addr);

    registers.pc += 2;
}

void CPU::ABL()
{
    uint32_t operand_addr = (registers.pb << 16) | registers.pc;

    uint16_t addr = read16(operand_addr);
    uint8_t bank = read8(operand_addr + 2);

    effective_address = (bank << 16) | addr;

    registers.pc += 3;
}

void CPU::ABIL()
{
    uint16_t pointer_addr = read16((registers.pb << 16) | registers.pc);

    uint16_t addr = read16(pointer_addr);
    uint8_t bank = read8(pointer_addr + 2);

    effective_address = (bank << 16) | addr;

    registers.pc += 2;
}

void CPU::ALX()
{
    uint32_t operand_addr = (registers.pb << 16) | registers.pc;

    uint16_t addr = read16(operand_addr);
    uint8_t bank = read8(operand_addr + 2);

    uint32_t formed_addr = (bank << 16) | addr;
    effective_address = formed_addr + registers.x;

    registers.pc += 3;
}

void CPU::DP()
{
    uint8_t operand_addr = read8(registers.pc);
    if (registers.get_emulation_mode_flag() && (registers.dp & 0xFF) == 0x00)
    {
        effective_address = (registers.dp & 0xFF00) | operand_addr;
    }
    else
    {
        effective_address = registers.dp + operand_addr;
    }

    registers.pc += 1;
}

void CPU::DPX()
{
    uint8_t operand_addr = read8(registers.pc);
    if (registers.get_emulation_mode_flag() && (registers.dp & 0xFF) == 0x00)
    {
        effective_address = (registers.dp & 0xFF00) | (uint8_t)(operand_addr + registers.x);
    }
    else
    {
        effective_address = registers.dp + operand_addr + registers.x;
    }

    registers.pc += 1;
}

void CPU::DPY()
{
    uint8_t operand_addr = read8(registers.pc);
    if (registers.get_emulation_mode_flag() && (registers.dp & 0xFF) == 0x00)
    {
        effective_address = (registers.dp & 0xFF00) | (uint8_t)(operand_addr + registers.y);
    }
    else
    {
        effective_address = registers.dp + operand_addr + registers.y;
    }

    registers.pc += 1;
}

void CPU::DPI()
{
    uint8_t pointer_addr = read8(registers.pc);

    uint16_t operand_addr = 0;

    if (registers.get_emulation_mode_flag() && (registers.dp & 0x00FF) == 0x00)
    {
        operand_addr = (registers.dp & 0xFF00) | pointer_addr;
    }
    else
    {
        operand_addr = registers.dp + pointer_addr;
    }

    effective_address = read16(operand_addr);

    registers.pc += 1;
}

void CPU::DPIX()
{
    uint8_t pointer_addr = read8(registers.pc);

    uint16_t operand_addr = 0;

    if (registers.get_emulation_mode_flag() && (registers.dp & 0x00FF) == 0x00)
    {
        operand_addr = (registers.dp & 0xFF00) | (uint8_t)(pointer_addr + registers.x);
    }
    else
    {
        operand_addr = registers.dp + pointer_addr + registers.x;
    }

    effective_address = read16(operand_addr);

    registers.pc += 1;
}

void CPU::DPIY()
{
    uint8_t pointer_addr = read8(registers.pc);

    uint16_t operand_addr = 0;

    if (registers.get_emulation_mode_flag() && (registers.dp & 0x00FF) == 0x00)
    {
        operand_addr = (registers.dp & 0xFF00) | (uint8_t)(pointer_addr + registers.y);
    }
    else
    {
        operand_addr = registers.dp + pointer_addr + registers.y;
    }

    effective_address = read16(operand_addr);

    registers.pc += 1;
}

void CPU::DPIL()
{
    uint8_t pointer_addr = read8(registers.pc);
    uint16_t operand_addr = 0;
    if (registers.get_emulation_mode_flag() && (registers.dp & 0xFF) == 0x00)
    {
        operand_addr = (registers.dp & 0xFF00) | pointer_addr;
    }
    else
    {
        operand_addr = registers.dp + pointer_addr;
    }
    effective_address = (read8(operand_addr + 2) << 16) | read16(operand_addr);

    registers.pc += 1;
}

void CPU::DPILY()
{
    uint8_t pointer_addr = read8(registers.pc);

    uint16_t operand_addr = 0;

    if (registers.get_emulation_mode_flag() && (registers.dp & 0x00FF) == 0x00)
    {
        operand_addr = (registers.dp & 0xFF00) | pointer_addr;
    }
    else
    {
        operand_addr = registers.dp + pointer_addr;
    }

    effective_address = (((uint32_t)read8(operand_addr + 2) << 16) | read16(operand_addr)) + registers.y;

    registers.pc += 1;
}

void CPU::SR()
{
    uint8_t offset = read8((registers.pb << 16) | registers.pc);

    effective_address = registers.sp + offset;

    registers.pc += 1;
}

void CPU::SRIY()
{
    uint8_t offset = read8((registers.pb << 16) | registers.pc);

    uint16_t pointer_addr = registers.sp + offset;

    effective_address = read16(pointer_addr) + registers.y;

    registers.pc += 1;
}

void CPU::REL()
{
    int8_t offset = (int8_t)(read8((registers.pb << 16) | registers.pc));

    effective_address = registers.pc + 1 + offset;

    registers.pc += 1;
}

void CPU::RELL()
{
    int16_t offset = (int16_t)(read16((registers.pb << 16) | registers.pc));

    effective_address = registers.pc + 2 + offset;

    registers.pc += 2;
}
