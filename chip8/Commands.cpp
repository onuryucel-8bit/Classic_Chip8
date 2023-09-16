#include "Commands.h"
namespace ch8 {


	Commands::Commands()
	{
	}

	Commands::~Commands()
	{
	}

	void Commands::runCommands(CPU* chip) {

		instruction = chip->ram[chip->programCounter];
		instruction <<= 8;
		chip->programCounter++;

		instruction |= chip->ram[chip->programCounter];
		chip->programCounter++;

		switch (instruction & 0xf000)
		{
		case 0x0000:
			if (instruction == 0x00E0)CLS_00E0(chip);
			break;
		case 0x1000:
			JMP_1nnn(chip);
			break;
		case 0x2000:
			CALL_2nnn(chip);
			break;
		case 0x3000:
			CE_3xnn(chip);
			break;
		case 0x4000:
			CNE_4xnn(chip);
			break;
		case 0x5000:
			RE_5xy0(chip);
			break;
		case 0x6000:
			LDC_6xnn(chip);
			break;
		case 0x7000:
			break;
		case 0x8000:
			break;
		case 0xD000:
			DRW_Dxyn(chip);
			break;
		}

	}

	void Commands::CLS_00E0(CPU* chip) {
		for (size_t i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
			chip->display[i] = 0;
		}

		chip->flag = 1;
	}

	void Commands::JMP_1nnn(CPU* chip)
	{
		chip->programCounter = instruction & 0x0fff;
	}

	void Commands::CALL_2nnn(CPU* chip)
	{
		chip->stack[chip->stackPointer] = chip->programCounter & 0xff0;
		chip->stackPointer += 1;
		chip->stack[chip->stackPointer] = chip->programCounter & 0x00f;
	}

	void Commands::CE_3xnn(CPU* chip) {

	}

	void Commands::CNE_4xnn(CPU* chip) {

	}

	void Commands::RE_5xy0(CPU* chip) {

	}

	void Commands::LDC_6xnn(CPU* chip) {

	}

	void Commands::DRW_Dxyn(CPU* chip) {

		uint8_t regX = (instruction >> 8) & 0x0f;
		uint8_t regY = (instruction >> 4) & 0x0f;

		uint8_t height = instruction & 0x000f;

		uint8_t Vx = chip->registerFile[regX];
		uint8_t Vy = chip->registerFile[regY];


		Vx = Vx % SCREEN_WIDTH;

		Vy = Vy % SCREEN_HEIGHT;

		uint8_t spriteByte;
		uint8_t spritePixel;
		uint8_t color;

		uint8_t screenPixel;
		size_t startingPos;

		chip->registerFile[0xf] = 0;

		for (uint8_t row = 0; row < height; row++) {

			spriteByte = chip->ram[chip->indexRegister + row];

			for (uint8_t col = 0; col < 4; col++) {

				startingPos = Vy * SCREEN_WIDTH + Vx;

				//let spriteByte = 1001_(4color)
				spritePixel = (spriteByte >> (7 - col)) & 0x01;
				//---//
				screenPixel = chip->display[startingPos] >> 7;

				//check collision
				if ((screenPixel ^ spritePixel) == screenPixel) {
					chip->registerFile[0xf] = 1;
				}

				//             1 = 0^1
				screenPixel = screenPixel ^ spritePixel;

				//copying for color values i cant find logical operation for this
				//11 = 1 / 10 = 0 / 01 = 1 / 00 = 0


				screenPixel <<= 7;
				color = spriteByte & 0x0f;

				chip->display[startingPos] = screenPixel | color;

				Vx++;
				if (Vx > 63)
					Vx = Vx % SCREEN_WIDTH;
			}

			Vx = chip->registerFile[regX];
			Vy++;


			Vx %= SCREEN_WIDTH;
			Vy %= SCREEN_HEIGHT;

		}


		chip->flag = 2;
	}
}