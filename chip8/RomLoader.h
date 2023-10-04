#pragma once

#include<iostream>

#include<fstream>

#include<vector>

#include "TypesChip8.h"

#define BYTE unsigned char

using namespace ch8;

/*
Memory Map :
+---------------+= 0xFFF (4095) End of Chip - 8 RAM
|               |
|               |
|               |
|               |
|               |
| 0x200 to 0xFFF|
|     Chip - 8  |
| Program / Data|
|     Space     |
|               |
|               |
|               |
+---------------+= 0x600 (1536) Start of ETI 660 Chip - 8 programs
|               |
|               |
|               |
+---------------+= 0x200 (512) Start of most Chip - 8 programs
| 0x000 to 0x1FF|
| Reserved for  |
|  interpreter  |
+---------------+= 0x000 (0) Start of Chip - 8 RAM
*/
class RomLoader
{
public:
	RomLoader();
	~RomLoader();

	////////////////////////////////////////////////////////////
	/// 
	/// if ROM load fails it return false 
	/// can print error message
	///
	////////////////////////////////////////////////////////////
	bool load(CPU* chip, std::string filename);
	

private:
	std::vector<BYTE> fileData;

	bool load_FromFile(CPU* chip, std::string filename);
};

