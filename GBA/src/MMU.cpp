#include <cstdlib>

#include "inc\MMU.h"

// _VADDR: system-defined address
// _SIZE : system-defined section size
// _ADDR : index in emulator memory

static const uint32_t BIOS_VADDR = 0x0;
static const uint32_t BIOS_ADDR = 0x0;
static const uint32_t BIOS_SIZE = 0x4000;

static const uint32_t WRAM_BOARD_VADDR = 0x2000000;
static const uint32_t WRAM_BOARD_ADDR = BIOS_ADDR + BIOS_SIZE;
static const uint32_t WRAM_BOARD_SIZE = 0x40000;

static const uint32_t WRAM_CHIP_VADDR = 0x3000000;
static const uint32_t WRAM_CHIP_ADDR = WRAM_BOARD_ADDR + WRAM_BOARD_SIZE;
static const uint32_t WRAM_CHIP_SIZE = 0x8000;

static const uint32_t IOREG_VADDR = 0x4000000;
static const uint32_t IOREG_ADDR = WRAM_CHIP_ADDR + WRAM_CHIP_SIZE;
static const uint32_t IOREG_SIZE = 0x400;

static const uint32_t PALETTE_RAM_VADDR = 0x5000000;
static const uint32_t PALETTE_RAM_ADDR = IOREG_ADDR + IOREG_SIZE;
static const uint32_t PALETTE_RAM_SIZE = 0x400;

static const uint32_t VRAM_VADDR = 0x6000000;
static const uint32_t VRAM_ADDR = PALETTE_RAM_ADDR + PALETTE_RAM_SIZE;
static const uint32_t VRAM_SIZE = 0x18000;

static const uint32_t OAM_VADDR = 0x7000000;
static const uint32_t OAM_ADDR = VRAM_ADDR + VRAM_SIZE;
static const uint32_t OAM_SIZE = 0x400;

static const uint32_t TOTAL_MEM_SIZE = BIOS_SIZE + WRAM_BOARD_SIZE + WRAM_CHIP_SIZE + IOREG_SIZE + PALETTE_RAM_SIZE + VRAM_SIZE + OAM_SIZE;

// External memory
static const uint32_t GAME_ROM_0 =  0x8000000;
static const uint32_t GAME_ROM_1 =  0xA000000;
static const uint32_t GAME_ROM_2 =  0xC000000;
static const uint32_t GAME_SRAM =   0xE000000;

#define CASE_EXTERNAL_MEMORY\
    case 0x8000000:\
    case 0x9000000:\
    case 0xA000000:\
    case 0xB000000:\
    case 0xC000000:\
    case 0xD000000:\
    case 0xE000000

namespace GBA
{

    namespace Memory
    {

        MMU::MMU()
            : memory_(TOTAL_MEM_SIZE, 0)
        {
        }

        // GBA is little endian: LSB first
        // TODO: improve read and write with single memory access

        template<>
        uint32_t MMU::read<MMU::Width::_8>(uint32_t addr)
        {
            uint8_t* result = memTranslate_(addr);
            return static_cast<uint32_t>(*result);
        }
        
        template<>
        uint32_t MMU::read<MMU::Width::_16>(uint32_t addr)
        {
            uint8_t* result = memTranslate_(addr);
            return static_cast<uint32_t>(result[0] | result[1] << 8);
        }

        template<>
        uint32_t MMU::read<MMU::Width::_32>(uint32_t addr)
        {
            uint8_t* result = memTranslate_(addr);
            return static_cast<uint32_t>(
                (result[3] << 24) |
                (result[2] << 16) |
                (result[1] << 8) |
                result[0]
                );
        }

        template<>
        void MMU::write<MMU::Width::_8>(uint32_t addr, uint32_t value)
        {
            *memTranslate_(addr) = value & 0xFF;
        }
        
        template<>
        void MMU::write<MMU::Width::_16>(uint32_t addr, uint32_t value)
        {
            uint8_t* dest = memTranslate_(addr);
            dest[0] = value & 0x00FF;
            dest[1] = (value & 0xFF00) >> 8;
        }
        
        template<>
        void MMU::write<MMU::Width::_32>(uint32_t addr, uint32_t value)
        {
            uint8_t* dest = memTranslate_(addr);
            dest[0] = (value & 0x000000FF);
            dest[1] = (value & 0x0000FF00) >> 8;
            dest[2] = (value & 0x00FF0000) >> 16;
            dest[3] = (value & 0xFF000000) >> 24;
        }

        uint8_t* MMU::memTranslate_(uint32_t virtualAddress)
        {
            uint32_t sectionIndex = virtualAddress & 0x0FFFFFF;
            uint8_t* result = nullptr;

            switch (virtualAddress & 0xF000000)
            {
            case BIOS_VADDR:
                result = &memory_[BIOS_ADDR + sectionIndex];
                break;

            case WRAM_BOARD_VADDR:
                result = &memory_[WRAM_BOARD_ADDR + sectionIndex];
                break;

            case WRAM_CHIP_VADDR:
                result = &memory_[WRAM_CHIP_ADDR + sectionIndex];
                break;

            case IOREG_VADDR:
                result = &memory_[IOREG_ADDR + sectionIndex];
                break;

            case PALETTE_RAM_VADDR:
                result = &memory_[PALETTE_RAM_ADDR + sectionIndex];
                break;

            case VRAM_VADDR:
                result = &memory_[VRAM_ADDR + sectionIndex];
                break;

            case OAM_VADDR:
                result = &memory_[OAM_ADDR + sectionIndex];
                break;

            CASE_EXTERNAL_MEMORY:
                break;
            }

            return result;
        }

    }

}