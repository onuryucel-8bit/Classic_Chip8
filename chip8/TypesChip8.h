#pragma once

#include <cstdint>

#define RESIZE_SCREEN_WIDTH 20
#define RESIZE_SCREEN_HEIGHT 20

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

namespace ch8 {
	struct CPU {

		char display[64 * 32] = {};

		uint8_t ram[0xfff] = {};
		uint8_t registerFile[16] = {};

		uint8_t stack[32] = {};

		uint16_t indexRegister;
		uint16_t stackPointer;
		uint16_t programCounter;

		uint8_t delayTimer;
		uint8_t soundTimer;

		bool keys[16];

		unsigned char flag;
	};
}
