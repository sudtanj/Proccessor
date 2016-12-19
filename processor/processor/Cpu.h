//#pragma once
#include "Register.h"
#include <iostream>
using namespace std;
//#include "Memory.h"

#define MAX_REGISTER 8

class Cpu {
	private:
		Register memory_Register[MAX_REGISTER];
//		Memory memory;
	public:
		Cpu();
//		void checkRegister();
		Register getRegister(int index);
//		Memory getMemory();
		void instruction_add(Register r_destination, Register r_source);
		int convertToBaseTen(bool* r);
		bool* convertToBaseTwo(int number);
		void inputIntegerToRegister(int number, Register * r);
		int inputRegistertoInteger(Register * r);
		int getIntegerFromBuiltInRegister(int index);
		void storeBinarytoBuiltInRegister(int index, int number);
		void instruction_substract(Register r_destination, Register r_source);
		void instruction_shift_left(Register& r);
		void instruction_shift_right(Register& r);
		void instruction_complement(Register& r);
		bool* instruction_and(bool* r_destination, bool* r_source);
		bool basic_operator_and(bool one, bool two);
		bool basic_operator_or(bool one, bool two);
		bool basic_operator_xor(bool one, bool two);
		bool basic_operator_not(bool one);
		bool basic_operator_nor(bool one, bool two);
		bool basic_operator_nand(bool one, bool two);
};
