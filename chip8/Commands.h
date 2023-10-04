#pragma once

//TESTING
#include <iostream>
#include "../utils/Radix.h"

#include <string>
#include <random>

#include "TypesChip8.h"

namespace ch8 {

	class Commands
	{
	public:
		
		void runCommands(CPU* chip);

		uint16_t getLastInstruction();
		uint8_t getInputVx();

	private:

		uint16_t instruction;
		uint8_t inputVx;

		void CLS_00E0(CPU* chip);
		void RET_00EE(CPU* chip);
		void JMP_1nnn(CPU* chip);
		void CALL_2nnn(CPU* chip);
		void CE_3xnn(CPU* chip);//SE //CONST EQUAL to reg

		void CNE_4xnn(CPU* chip);//SNE //const not equal to reg
		void RE_5xy0(CPU* chip);//reg equals
		void LDC_6xnn(CPU* chip);//LOAD CONST

		void ADDC_7xnn(CPU* chip);//ADD const
		void MOV_8xy0(CPU* chip);//LD 8XY0
		void OR_8xy1(CPU* chip);
		void AND_8xy2(CPU* chip);

		void XOR_8xy3(CPU* chip);
		void ADDR_8xy4(CPU* chip);//add reg
		void SUBX_8xy5(CPU* chip);
		void SHR_8xy6(CPU* chip);

		void SUBY_8xy7(CPU* chip);
		void SHL_8xyE(CPU* chip);
		void RNE_9xy0(CPU* chip);//reg not equal
		void LDI_Annn(CPU* chip);//load index reg

		void JMPZ_Bnnn(CPU* chip);//jump with zero reg	
		void RND_Cxnn(CPU* chip);
		void DRW_Dxyn(CPU* chip);
		void SKP_Ex9E(CPU* chip);//skip if key pressed

		void SKNP_ExA1(CPU* chip);//skip if key not pressed
		void LDD_Fx07(CPU* chip);//load delay timer
		void WFK_Fx0A(CPU* chip);//wait for key
		void LDRD_Fx15(CPU* chip);//load reg to delay timer

		void LDRS_Fx18(CPU* chip);//load reg to sound timer
		void ADDI_Fx1E(CPU* chip);//index reg + Vx
		void IIR_FX29(CPU* chip);//increase index reg 

		void DTB_FX33(CPU* chip);//dec to bcd DTB
		void STR_FX55(CPU* chip);//STORE
		void CFR_FX65(CPU* chip);//copy from ram CFR
		
	};

	
}