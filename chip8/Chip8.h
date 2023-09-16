#pragma once

#include "TypesChip8.h"
#include "Commands.h"

class Chip8
{
public:
	Chip8();
	~Chip8();
	
	void init();

	void update(bool* keys);

	ch8::CPU* getCPU();

private:
	ch8::CPU chip;
	ch8::Commands command;
};

