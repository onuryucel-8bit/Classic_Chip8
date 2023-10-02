#include "Commands.h"
namespace ch8 {

	uint16_t Commands::getLastInstruction() {
		return instruction;
	}

	uint8_t Commands::getInputVx() {
		return inputVx;
	}

	void Commands::runCommands(CPU* chip) {

		instruction = chip->ram[chip->programCounter];
		instruction <<= 8;
		chip->programCounter++;

		instruction |= chip->ram[chip->programCounter];
		chip->programCounter++;

		
		uint16_t instructionGroup;

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
			ADDC_7xnn(chip);
			break;
#pragma region 0X8000
		case 0x8000:

			instructionGroup = instruction & 0x000f;

			switch (instructionGroup) {

				// LD VX, VY — 8XY0
			case 0x0000:
				MOV_8xy0(chip);
				break;

				// OR VX, VY — 8XY1
			case 0x0001:
				OR_8xy1(chip);
				break;

				// AND VX, VY — 8XY2
			case 0x0002:
				AND_8xy2(chip);
				break;

				// XOR VX, VY — 8XY3
			case 0x0003:
				XOR_8xy3(chip);
				break;

				// ADD VX, VY — 8XY4
			case 0x0004:
				ADDR_8xy4(chip);
				break;

				// SUB VX, VY — 8XY5
			case 0x0005:
				SUBX_8xy5(chip);
				break;

				// SHR VX {, VY} — 8XY6
			case 0x0006:
				SHR_8xy6(chip);
				break;

				// SUBN VX, VY — 8XY7
			case 0x0007:
				SUBY_8xy7(chip);
				break;

				// SHL VX {, VY} — 8XYE
			case 0x000E:
				SHL_8xyE(chip);
				break;

			}

			break;
#pragma endregion	

			// SNE VX, VY — 9XY0
		case 0x9000:
			RNE_9xy0(chip);
			break;

			// LD I, NNN — ANNN
		case 0xA000:
			LDI_Annn(chip);
			break;

			// JMP V0, NNN — BNNN
		case 0xB000:
			JMPZ_Bnnn(chip);
			break;

			// RND VX, NN – CXNN
		case 0xC000:
			RND_Cxnn(chip);
			break;

			// DRW VX, VY, N — DXYN
		case 0xD000:
			// Implementation...
			DRW_Dxyn(chip);
			break;

			// SKP VX — EX9E
		case 0xE000:
			if ((instruction & 0x009E) == 0x009E)
				SKP_Ex9E(chip);
			if ((instruction & 0x00A1) == 0x00A1)
				SKNP_ExA1(chip);

			break;

		case 0xF000:

			instructionGroup = instruction & 0x00ff;

			switch (instructionGroup)
			{
			case 0x07:
				LDD_Fx07(chip);
				break;
			case 0x0A:
				WFK_Fx0A(chip);
				break;
			case 0x15:
				LDRD_Fx15(chip);
				break;
			case 0x18:
				LDRS_Fx18(chip);
				break;
			case 0x1E:
				ADDI_Fx1E(chip);
				break;
			case 0x29:
				IIR_FX29(chip);
				break;
			case 0x33:
				DTB_FX33(chip);
				break;
			case 0x55:
				STR_FX55(chip);
				break;
			case 0x65:
				CFR_FX65(chip);
				break;
			}

			break;
		}
	}

	



	void Commands::CLS_00E0(CPU* chip) {
		for (size_t i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
			chip->display[i] = 0;
		}

		chip->flag = 1;
	}

	void Commands::JMP_1nnn(CPU* chip){
		chip->programCounter = instruction & 0x0fff;
		
	}

	void Commands::CALL_2nnn(CPU* chip){
		chip->stack[chip->stackPointer] = chip->programCounter & 0xff0;
		chip->stackPointer += 1;
		chip->stack[chip->stackPointer] = chip->programCounter & 0x00f;
	}

	void Commands::CE_3xnn(CPU* chip) {
		
		uint16_t regX = instruction & 0x0f00;
		regX >>= 8;

		if (chip->registerFile[regX] == (instruction & 0x00ff)) {
			chip->programCounter += 2;
		}
	}

	void Commands::CNE_4xnn(CPU* chip) {
		uint16_t regX = instruction & 0x0f00;
		regX >>= 8;

		if (chip->registerFile[regX] != (instruction & 0x00ff)) {
			chip->programCounter += 2;
		}
	}

	void Commands::RE_5xy0(CPU* chip) {
		uint16_t regX = instruction & 0x0f00;
		regX >>= 8;
		uint16_t regY = instruction & 0x00f0;
		regX >>= 4;

		if (chip->registerFile[regX] == chip->registerFile[regY]) {
			chip->programCounter += 2;
		}
	}

	void Commands::LDC_6xnn(CPU* chip) {
		uint16_t regX = instruction & 0x0f00;
		regX = regX >> 8;

		uint8_t value = instruction & 0x00ff;

		chip->registerFile[regX] = value;
	}

	void Commands::ADDC_7xnn(CPU* chip){

		uint16_t regX = instruction & 0x0f00;
		regX >>= 8;

		uint8_t value = instruction & 0x00ff;

		chip->registerFile[regX] += value;
	}

	void Commands::MOV_8xy0(CPU* chip){
		uint16_t regX = instruction & 0x0f00;
		regX >>= 8;

		uint16_t regY = instruction & 0x00f0;
		regY >>= 4;

		chip->registerFile[regX] = chip->registerFile[regY];
	}
	void Commands::OR_8xy1(CPU* chip){
		uint16_t regX = instruction & 0x0f00;
		regX >>= 8;

		uint16_t regY = instruction & 0x00f0;
		regY >>= 4;

		chip->registerFile[regX] |= chip->registerFile[regY];
	}
	void Commands::AND_8xy2(CPU* chip){
		uint16_t regX = instruction & 0x0f00;
		regX >>= 8;

		uint16_t regY = instruction & 0x00f0;
		regY >>= 4;

		chip->registerFile[regX] &= chip->registerFile[regY];
	}

	void Commands::XOR_8xy3(CPU* chip){
		uint16_t regX = instruction & 0x0f00;
		regX >>= 8;

		uint16_t regY = instruction & 0x00f0;
		regY >>= 4;

		chip->registerFile[regX] ^= chip->registerFile[regY];
	}
	void Commands::ADDR_8xy4(CPU* chip){
		uint16_t regX = instruction & 0x0f00;
		regX >>= 8;

		uint16_t regY = instruction & 0x00f0;
		regY >>= 4;

		if (chip->registerFile[regX] + chip->registerFile[regY] > 0xff) {
			chip->registerFile[0xf] = 1;
		}
		else {
			chip->registerFile[0xf] = 0;
		}

		chip->registerFile[regX] += chip->registerFile[regY];
	}
	void Commands::SUBX_8xy5(CPU* chip){
		uint16_t regX = instruction & 0x0f00;
		regX >>= 8;

		uint16_t regY = instruction & 0x00f0;
		regY >>= 4;

		if (chip->registerFile[regX] > chip->registerFile[regY]) {
			chip->registerFile[0xf] = 1;
		}
		else {
			chip->registerFile[0xf] = 0;
		}

		chip->registerFile[regX] -= chip->registerFile[regY];
	}
	void Commands::SHR_8xy6(CPU* chip){
		uint16_t regX = instruction & 0x0f00;
		regX >>= 8;

		chip->registerFile[regX] >>= 1;
		chip->registerFile[0xf] = regX & 0x01;
	}

	void Commands::SUBY_8xy7(CPU* chip){
		uint16_t regX = instruction & 0x0f00;
		regX >>= 8;

		uint16_t regY = instruction & 0x00f0;
		regY >>= 4;

		if (chip->registerFile[regX] > chip->registerFile[regY]) {
			chip->registerFile[0xf] = 1;
		}
		else {
			chip->registerFile[0xf] = 0;
		}

		chip->registerFile[regY] -= chip->registerFile[regX];
	}
	void Commands::SHL_8xyE(CPU* chip){
		uint16_t regX = instruction & 0x0f00;
		regX >>= 8;

		chip->registerFile[regX] <<= 1;
		chip->registerFile[0xf] = regX & 0x80;
	}
	void Commands::RNE_9xy0(CPU* chip){
		uint16_t regX = instruction & 0x0f00;
		regX >>= 8;

		uint16_t regY = instruction & 0x00f0;
		regY >>= 4;

		if (chip->registerFile[regX] != chip->registerFile[regY]) {
			chip->programCounter += 2;
		}
	}
	void Commands::LDI_Annn(CPU* chip){
		chip->indexRegister = instruction & 0x0fff;
	}

	void Commands::JMPZ_Bnnn(CPU* chip){
		chip->programCounter = chip->registerFile[0] + (instruction & 0x0fff);
	}
	void Commands::RND_Cxnn(CPU* chip){
		uint16_t regX = instruction & 0x0f00;
		regX >>= 8;

		uint8_t value = instruction & 0x00ff;

		std::random_device rd;
		std::uniform_int_distribution <int>dist(0, 255);

		chip->registerFile[regX] = (uint8_t)(dist(rd)) & value;
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

		uint8_t screenPixel;
		size_t startingPos;

		chip->registerFile[0xf] = 0;

		for (uint8_t row = 0; row < height; row++) {

			spriteByte = chip->ram[chip->indexRegister + row];

			for (uint8_t col = 0; col < 8; col++) {

				startingPos = Vy * SCREEN_WIDTH + Vx;

				//let spriteByte = 1001_(4color)
				spritePixel = (spriteByte >> (7 - col)) & 0x01;
				//---//
				screenPixel = chip->display[startingPos] >> 7;

				//check collision
				if ((screenPixel == 1 && spritePixel == 1)) {
					chip->registerFile[0xf] = 1; // Collision occurred
				}

				//             1 = 0^1
				screenPixel = screenPixel ^ spritePixel;

				//copying for color values i cant find logical operation for this
				//11 = 1 / 10 = 0 / 01 = 1 / 00 = 0

				chip->display[startingPos] = screenPixel ;

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

	void Commands::SKP_Ex9E(CPU* chip) {
		//take register Vx index
		uint16_t regX = instruction & 0x0f00;
		regX >>= 8;

		//for code errors : if Vx = 0xff registerFile[Vx] gonna give index of bound error
		if (chip->registerFile[regX] > 0xf) {
			return;
		}

		//if key pressed
		if (chip->keys[chip->registerFile[regX]]) {
			chip->programCounter += 2;
		}
	
	}

	void Commands::SKNP_ExA1(CPU* chip) {
		uint16_t regX = instruction & 0x0f00;
		regX >>= 8;

		//for code errors : if Vx = 0xff registerFile[Vx] gonna give index of bound error
		if (chip->registerFile[regX] > 0xf) {
			return;
		}

		//if key pressed
		if (chip->keys[chip->registerFile[regX]] == false) {
			chip->programCounter += 2;
		}

	}

	void Commands::LDD_Fx07(CPU* chip) {
		uint16_t regX = instruction & 0x0f00;
		regX >>= 8;
		chip->registerFile[regX] = chip->delayTimer;
	}

	void Commands::WFK_Fx0A(CPU* chip) {
		chip->flag = 3;
	}

	void Commands::LDRD_Fx15(CPU* chip) {
		uint16_t regX = instruction & 0x0f00;
		regX >>= 8;
		chip->delayTimer = chip->registerFile[regX];
	}

	void Commands::LDRS_Fx18(CPU* chip) {
		uint16_t regX = instruction & 0x0f00;
		regX >>= 8;
		chip->soundTimer = chip->registerFile[regX];
	}
	void Commands::ADDI_Fx1E(CPU* chip) {
		uint16_t regX = instruction & 0x0f00;
		regX >>= 8;

		chip->indexRegister += chip->registerFile[regX];
	}
	void Commands::IIR_FX29(CPU* chip) {
		uint16_t regX = instruction & 0x0f00;
		regX >>= 8;

		chip->indexRegister = chip->registerFile[regX] + 0x05;
	}
	void Commands::DTB_FX33(CPU* chip) {
		uint16_t regX = instruction & 0x0f00;
		regX >>= 8;

		std::string numberStr = std::to_string(chip->registerFile[regX]);

		uint16_t i = 0;
		for (char digitChar : numberStr) {
			int digit = digitChar - '0'; // Convert char to integer
			chip->ram[chip->indexRegister + i] = (uint8_t)(digit);
			i++;
		}
	}
	void Commands::STR_FX55(CPU* chip){
		uint16_t regX = instruction & 0x0f00;
		regX >>= 8;

		for (uint16_t i = 0; i < regX; i++) {
			chip->ram[chip->indexRegister + i] = chip->registerFile[i];
		}
	}
	void Commands::CFR_FX65(CPU* chip) {
		uint16_t regX = instruction & 0x0f00;
		regX >>= 8;

		for (uint16_t i = 0; i < regX; i++) {
			chip->registerFile[i] = chip->ram[chip->indexRegister + i];
		}
	}

}