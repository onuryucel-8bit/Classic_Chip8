#pragma once

#include<iostream>

#include<fstream>

#include<vector>

#include "TypesChip8.h"

#define BYTE unsigned char

using namespace ch8;

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

