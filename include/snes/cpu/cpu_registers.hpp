#pragma once
#include <cstdint>

struct CPU_Registers
{
    uint16_t pc = 0; // Program Counter
    uint16_t sp = 0; // Stack Pointer
    uint16_t a = 0;  // Accumulator
    uint16_t dp = 0; // Direct Page
    uint16_t x = 0;  // X Index Register
    uint16_t y = 0;  // Y Index Register
    uint8_t db = 0;  // Data Bank
    uint8_t pb = 0;  // Program Bank
    uint8_t p = 0;   // Processor Status
    bool emulation_mode = 1; // 0 = Native 65c816 16-bit mode, 1 = Emulated 6502 8-bit Mode

    // For use with operations that change flag state
    bool get_negative_flag();
    bool get_overflow_flag();
    bool get_accum_size_flag();     // 0 = 16-bit, 1 = 8-bit
    bool get_index_size_flag();     // 0 = 16-bit, 1 = 8-bit
    bool get_decimal_mode_flag();   // 0 = Binary Arithematic, 1 = Binary Coded Decimal Arithematic
    bool get_irq_disable_flag();
    bool get_zero_flag();
    bool get_carry_flag();
    bool get_break_flag(); // Emulation mode only
    // Emulation mode is a hidden flag, not in P register
    bool get_emulation_mode_flag();

    void set_negative_flag(bool set);
    void set_overflow_flag(bool set);
    void set_accum_size_flag(bool set);
    void set_index_size_flag(bool set);
    void set_decimal_mode_flag(bool set);
    void set_irq_disable_flag(bool set);
    void set_zero_flag(bool set);
    void set_carry_flag(bool set);
    void set_break_flag(bool set); // Emulation mode only
    // Emulation mode is a hidden flag, not in P register
    void set_emulation_mode_flag(bool set);

    // Flag Bitmasks
    static constexpr uint8_t NEGATIVE_FLAG_MASK     = 1 << 7;
    static constexpr uint8_t OVERFLOW_FLAG_MASK     = 1 << 6;
    static constexpr uint8_t ACCUM_SIZE_FLAG_MASK   = 1 << 5;
    static constexpr uint8_t INDEX_SIZE_FLAG_MASK   = 1 << 4;
    static constexpr uint8_t DECIMAL_FLAG_MASK      = 1 << 3;
    static constexpr uint8_t IRQ_DISABLE_FLAG_MASK  = 1 << 2;
    static constexpr uint8_t ZERO_FLAG_MASK         = 1 << 1;
    static constexpr uint8_t CARRY_FLAG_MASK        = 1 << 0;
};