#pragma once

#include "cpu_registers.hpp"
#include "opcodes.hpp"

class Bus;

enum class Addressing_Modes
{

};

class CPU
{
    private:
        Bus* bus;
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

        void connect_bus(Bus* bus);
};