#pragma once
#include<iostream>
#include <string>
//#include "Cpu.h"
//#include "Memory.h"
//#include "Assembler.h"
class Console {
private:
	std::string line;
	//Cpu* systemCpu;
	//Memory* systemMemory;
public:
	Console() {};
	void Input() {
		std::cout << "     ============================================     " << std::endl;
		std::cout << "     |               CPU V1.0                   |     " << std::endl;
		std::cout << "     |   Copyright© 2016. All Right Reserved.   |     " << std::endl;
		std::cout << "     |          Author =                        |     " << std::endl;
		std::cout << "     ============================================     " << std::endl;
		std::cout << std::endl << "Initialization Done!" << std::endl;
		std::cout << "Ready for input...." << std::endl;
		while (this->line != "run") {
			std::cout << ">";
			std::getline(std::cin,this->line);
			std::cout << "\a" << std::endl;
			bool* data =new bool[4];
			data[0] = true;
			data[1] = false;
			data[2] = true;
			data[3] = false;
			this->printRegisterRow(data);
			//Assembler::translateToBinary(this->systemCpu, this->line);
		}

	};
	void errorMessage(std::string errormessage,bool systemExit) {
		system("cls");
		std::cout << "     ===================    " << std::endl;
		std::cout << "     | × Error Message |    " << std::endl;
		std::cout << "     ===================    ";
		for (int i = 0;i < errormessage.size();i++) {
			if (i % 24 == 0) {
				std::cout << std::endl;
				std::cout << "   ";
			}
			std::cout << errormessage[i];
		}
		std::cout << std::endl<<std::endl;
		system("pause");
		if (systemExit==true)
			system("exit");
	}
	/**
	void setSystem(Cpu* system, Memory* memory) {
		this->systemCpu = system;
		this->systemMemory = memory;
	}
	Cpu* callCpu() {
		if (this->systemCpu == NULL) {
			errorMessage("Cpu hasn't been loaded yet!");
			system("exit");
		}
		return this->systemCpu;
	}
	Memory* callMemory() {
		if (this->systemCpu == NULL) {
			errorMessage("Memory hasn't been loaded yet!");
			system("exit");
		}
		return this->systemMemory;
	}
	*/
	void printRegisterRow(bool* data) {
		for (int i = 0;i < boolLength(data);i++)
			std::cout << "=======" <<" ";
		std::cout<<std::endl;
		for (int i = 0;i < boolLength(data);i++)
			std::cout << "|  " << data[i] << "  | ";
		std::cout << std::endl;
		for (int i = 0;i < boolLength(data);i++)
			std::cout << "=======" << " ";
		std::cout << std::endl;
	}
	int boolLength(bool*data) {
		int h = 1; // this is the array size
		for (int i = 0; data[i]; i++)
		{
			h++; // add one to the h(array size)
		}
		return (h + 2);
	}
};