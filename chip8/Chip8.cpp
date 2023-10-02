#include "Chip8.h"

Chip8::Chip8()
{
	
}

void Chip8::reset() {
	chip.programCounter = 512;
	chip.delayTimer = 0;
	chip.soundTimer = 0;
	chip.stackPointer = 0;

	for (size_t i = 512; i < 0xfff; i++) {
		chip.ram[i] = 0;
	}
}

//Set timers,pc,sp and load default Charset to ROM
void Chip8::init() {

	chip.programCounter = 512;
	chip.delayTimer = 0;
	chip.soundTimer = 0;
	chip.stackPointer = 0;	

	uint8_t CHARSET[] = {
		0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
		0x20, 0x60, 0x20, 0x20, 0x70, // 1
		0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
		0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
		0x90, 0x90, 0xF0, 0x10, 0x10, // 4
		0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
		0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
		0xF0, 0x10, 0x20, 0x40, 0x40, // 7
		0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
		0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
		0xF0, 0x90, 0xF0, 0x90, 0x90, // A
		0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
		0xF0, 0x80, 0x80, 0x80, 0xF0, // C
		0xE0, 0x90, 0x90, 0x90, 0xE0, // D
		0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
		0xF0, 0x80, 0xF0, 0x80, 0x80, // F
		
	};
	
	for (size_t i = 0; i < 80; i++)
	{
		chip.ram[i] = CHARSET[i];
	}

}

void Chip8::update(bool* keys) {

	//timers

	if (chip.soundTimer != 0) {
		chip.soundTimer--;
	}

	if (chip.delayTimer != 0) {
		chip.delayTimer--;
	}

	//get key input
	for (size_t i = 0; i < 16; i++) {
		chip.keys[i] = keys[i];
	}

	//execute wait for keys command
	if (chip.flag == 4) {
		//get wfk opcode
		uint16_t regX = command.getLastInstruction() & 0x0f00;
		regX >>= 8;

		for (size_t i = 0; i < 16; i++) {

			//for example if key D pressed Vx = key
			if (chip.keys[i]) {
				chip.registerFile[regX] = (uint8_t)(i);
			}
		}

		chip.flag = 0;

	}
	else {

		command.runCommands(&chip);
	}

	for (size_t i = 0; i < 16; i++) {
		chip.keys[i] = false;	
	}
}

ch8::CPU* Chip8::getCPU(){
	return &chip;
}

Chip8::~Chip8()
{
}