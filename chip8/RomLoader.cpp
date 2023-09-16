#include "RomLoader.h"

RomLoader::RomLoader()
{
}

bool RomLoader::load(CPU* chip, std::string filename) {

	std::cout << "Openning file: " << filename << "\n";

	//load ROM to std::vector<BYTE> fileData;
	if (!load_FromFile(chip, filename)) {
		return false;
	}

	//load fileData to (CPU) chip->ram
	for (size_t i = 0; i < fileData.size(); i++)
	{		
		chip->ram[i + 512] = fileData[i];
	}

	return true;
}

bool RomLoader::load_FromFile(CPU* chip,std::string filename) {
	
	std::streampos fileSize;
	std::ifstream file(filename, std::ios::binary);

	if (!file.is_open()) {

		std::cout << "ERROR : at RomLoader::load(CPU*, std::string) :: cannot open file \n";

		file.close();
		return false;
	}
	
	file.seekg(0, std::ios::end);
	fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	fileData.resize((size_t)(fileSize));
	file.read((char*)&fileData[0], fileSize);

	file.close();

	return true;
}

RomLoader::~RomLoader()
{
}