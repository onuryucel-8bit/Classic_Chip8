#pragma once

#include "TypesChip8.h"

namespace ch8 {

	class Commands
	{
	public:
		Commands();
		~Commands();

		void runCommands(CPU* chip);

	private:
		char ch8flag;

		uint16_t instruction;

		void CLS_00E0(CPU* chip);
		void JMP_1nnn(CPU* chip);
		void CALL_2nnn(CPU* chip);
		void CE_3xnn(CPU* chip);//SE //CONST EQUAL to reg

		void CNE_4xnn(CPU* chip);//SNE //const not equal to reg
		void RE_5xy0(CPU* chip);//reg equals
		void LDC_6xnn(CPU* chip);//LOAD CONST

		void DRW_Dxyn(CPU* chip);
		
	};

	
}