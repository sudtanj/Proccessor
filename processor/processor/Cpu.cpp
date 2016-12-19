#include "Cpu.h"
#include <stdlib.h>
using namespace std;

Cpu::Cpu()
{
}

Register Cpu::getRegister(int idx)
{
    return memory_Register[idx];
}

void Cpu::instruction_add(Register r_destination, Register r_source)
{
	bool* a = memory_Register[6].getRegister();
	bool* dest = r_destination.getRegister();
	bool* src = r_source.getRegister();
	bool temp, temp2;
	a[2] = 0;
	for(int i=31; i>=0; i--)
	{
	    temp = basic_operator_and(src[i], dest[i]);
        dest[i] = basic_operator_xor(src[i], dest[i]);
	    temp2 = basic_operator_and(a[2], dest[i]);
        dest[i] = basic_operator_xor(a[2], dest[i]);
        a[2] = basic_operator_xor(temp, temp2);
	}
	r_destination.setRegister(dest);
}

int Cpu::convertToBaseTen(bool* r) {
	int temp=0;
	for (unsigned int i = sizeof(r);i > 0;i--)
			temp += (r[i])? pow(2, (i - 31)*-1) : 0 ;
	return temp;
}

bool* Cpu::convertToBaseTwo(int number) {
	bool* tempBinary = new bool[32];
	memset(tempBinary, false, 32 * sizeof(bool));
	int temp=31;
	while (number != 0) {
		tempBinary[temp] = number % 2;
		number /= 2;
		temp--;
	}
	return tempBinary;
}

void Cpu::inputIntegerToRegister(int number,Register* r) {
	r->setRegister(this->convertToBaseTwo(number));
}

int Cpu::inputRegistertoInteger(Register* r) {
	return this->convertToBaseTen(r->getRegister());
}

int Cpu::getIntegerFromBuiltInRegister(int index) {
	return this->convertToBaseTen(this->getRegister(index).getRegister());
}

void Cpu::storeBinarytoBuiltInRegister(int index, int number) {
	this->getRegister(index).setRegister(this->convertToBaseTwo(number));
}

void Cpu::instruction_shift_left(Register& r)
{
	bool *reg = r.getRegister();
	for(int i=0; i<30; i++) reg[i] = reg[i+1];
	reg[31] = 0;
	r.setRegister(reg);
}

void Cpu::instruction_shift_right(Register& r)
{
	bool *reg = r.getRegister();
	for(int i=32-2; i>0; i--) reg[i+1] = reg[i];
	reg[0] = 0;
	r.setRegister(reg);
}

void Cpu::instruction_complement(Register& r)
{
	bool *reg = r.getRegister();
	for(int i=0; i<32; i++) reg[i] = basic_operator_not(reg[i]);
	r.setRegister(reg);
}

bool* Cpu::instruction_and(bool* r_destination, bool* r_source)
{
//	bool *dest = r_destination.getRegister();
//	bool *src = r_source.getRegister();
	for(int i=0; i<32; i++)
	{
		r_destination[i] = basic_operator_and(r_destination[i], r_source[i]);
	}
	return r_destination;
//	r_destination.setRegister(dest);
}

bool Cpu::basic_operator_and(bool one, bool two)
{
	return one && two;
}

bool Cpu::basic_operator_or(bool one, bool two)
{
	return one || two;
}

bool Cpu::basic_operator_xor(bool one, bool two)
{
	return basic_operator_and(basic_operator_not(basic_operator_and(one, two)), basic_operator_or(one, two));
}

bool Cpu::basic_operator_not(bool one)
{
	return !one;
}

bool Cpu::basic_operator_nor(bool one, bool two)
{
	return basic_operator_not(basic_operator_or(one, two));
}

bool Cpu::basic_operator_nand(bool one, bool two)
{
	return basic_operator_not(basic_operator_and(one, two));
}
