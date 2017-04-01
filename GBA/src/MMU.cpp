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
static const uint32_t GAME_ROM_0 = 0x8000000;
static const uint32_t GAME_ROM_1 = 0xA000000;
static const uint32_t GAME_ROM_2 = 0xC000000;
static const uint32_t GAME_SRAM = 0xE000000;

uint8_t* GBA::Memory::MMU::memAccess_(uint32_t virtualAddress)
{

}