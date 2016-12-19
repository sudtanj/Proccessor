#ifndef ALU_H
#define ALU_H

#include "Register.h"

class ALU
{
    private:
        bool basic_and(bool val_1, bool val_2);
        bool basic_or(bool val_1, bool val_2);
        bool basic_not(bool val);
        bool basic_xor(bool val_1, bool val_2);
    public:
        ALU();
        bool* toBinary(int number, int bits);
        bool* inverse(bool* number, int bits);
        bool* add(bool* num_1, bool* num_2, int bits, Register* flags);
        bool* substract(bool* num_1, bool* num_2, int bits, Register* flags);
        bool* multiply(bool* num_1, bool* num_2, int bits, Register* flags);
        bool* divide(bool* num_1, bool* num_2, int bits, Register* flags);
        bool* modulo(bool* num_1, bool* num_2, int bits, Register* flags);
        bool* shiftRight(bool* number, int bits);
        bool* shiftLeft(bool* number, int bits);
        bool* rotateRight(bool* number, int bits);
        bool* rotateLeft(bool* number, int bits);

};

#endif // ALU_H
