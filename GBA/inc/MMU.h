#ifndef _MMU_H_
#define _MMU_H_

#include <vector>

namespace GBA
{

    namespace Memory
    {

        class MMU
        {
        public:
            MMU();

            enum class Width
            {
                _8,
                _16,
                _32,
            };

            template<Width width>
            uint32_t read(uint32_t addr);
            
            template<Width width>
            void write(uint32_t addr, uint32_t value);

        private:
            // Returns a pointer to physical memory corresponding to the input virtual address
            uint8_t* memTranslate_(uint32_t virtualAddr);

            std::vector<uint8_t> memory_;
        };

    }

}

const GBA::Memory::MMU::Width _8 = GBA::Memory::MMU::Width::_8;
const GBA::Memory::MMU::Width _16 = GBA::Memory::MMU::Width::_16;
const GBA::Memory::MMU::Width _32 = GBA::Memory::MMU::Width::_32;

#endif
