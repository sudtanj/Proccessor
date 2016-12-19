#include <cstddef>

#include "ALU.h"
#include <iostream>
ALU::ALU()
{

}

bool ALU::basic_and(bool val_1, bool val_2)
{
    return val_1 && val_2;
}

bool ALU::basic_or(bool val_1, bool val_2)
{
    return val_1 || val_2;
}

bool ALU::basic_not(bool val)
{
    return !val;
}

bool ALU::basic_xor(bool val_1, bool val_2)
{
    return basic_and(basic_not(basic_and(val_1, val_2)), basic_or(val_1, val_2));
}

bool* ALU::inverse(bool* number, int bits)
{
    bool* res = new bool[bits];
    for(int i=0; i<bits; i++) res[i] = basic_not(number[i]);
    return res;
}

bool* ALU::toBinary(int number, int bits)
{
    bool* res = new bool[bits];
    for(int i=bits-1; i>=0; i--, number/=2) res[i] = number%2;
    return res;
}

bool* ALU::add(bool* num_1, bool* num_2, int bits, Register* flags)
{
    bool* flag = flags->getBits();
    flag[2] = false;
    bool* res = new bool[bits];
    for(int i=bits-1; i>=0; i--)
    {
        res[i] = basic_xor(basic_xor(num_1[i], num_2[i]), flag[2]);
        flag[2] = basic_or(basic_and(basic_xor(num_1[i], num_2[i]), flag[2]), basic_and(num_1[i], num_2[i]));
    }
    return res;
}

bool* ALU::substract(bool* num_1, bool* num_2, int bits, Register* flags)
{
    bool* temp = new bool[bits];
    for(int i=0; i<bits; i++) temp[i] = num_2[i];
    temp = inverse(temp, bits);
    temp = add(temp, toBinary(1, bits), bits, flags);
    return add(num_1, temp, bits, flags);
}

bool* ALU::multiply(bool* num_1, bool* num_2, int bits, Register* flags)
{
    bool* temp_1 = new bool[bits];
    bool* temp_2 = new bool[bits];
    bool* res = new bool[bits];
    for(int i=0; i<bits; i++)
    {
        res[i] = 0;
        temp_1[i] = num_1[i];
        temp_2[i] = num_2[i];
    }
    for(int i=0; i<bits; i++)
    {
        if(temp_1[bits-1])
        {
            res = add(res, temp_2, bits, flags);
        }
        temp_1 = shiftRight(temp_1, bits);
        temp_2 = shiftLeft(temp_2, bits);
    }
    return res;
}

bool* ALU::divide(bool* num_1, bool* num_2, int bits, Register* flags)
{
    int numOfShiftLeft=0;
    bool* temp_1 = new bool[bits];
    bool* temp_2 = new bool[bits];
    bool* res = new bool[bits];
    for(int i=0; i<bits; i++)
    {
        res[i] = 0;
        temp_1[i] = num_1[i];
        temp_2[i] = num_2[i];
    }
    for(int i=0; i<bits; i++)
    {
        if(temp_1[i])
        {
            for(int j=0; j<bits; j++)
            {
                if(!temp_2[i])
                {
                    temp_2 = shiftLeft(temp_2, bits);
                    numOfShiftLeft++;
                }
            }
            break;
        }
    }
    if(numOfShiftLeft==bits) return NULL;

    for(int i=0; i<=numOfShiftLeft; i++)
    {
        temp_1 = substract(temp_1, temp_2, bits, flags);
        if(temp_1[0])
        {
            temp_1 = add(temp_1, temp_2, bits, flags);
        }
        else
        {
            res = add(res, toBinary(1, bits), bits, flags);
        }
        temp_2 = shiftRight(temp_2, bits);
        res = shiftLeft(res, bits);
    }
    res = shiftRight(res, bits);
    return res;
}

bool* ALU::modulo(bool* num_1, bool* num_2, int bits, Register* flags)
{
    bool* div = divide(num_1, num_2, bits, flags);
    if(div!=NULL) return substract(num_1, multiply(num_2, div, bits, flags), bits, flags);
    else return NULL;
}

bool* ALU::shiftRight(bool* number, int bits)
{
    bool* res = new bool[bits];
    for(int i=bits-1; i>0; i--)
    {
        res[i] = number[i-1];
    }
    res[0] = 0;
    return res;
}

bool* ALU::shiftLeft(bool* number, int bits)
{
    bool* res = new bool[bits];
    bits--;
    for(int i=0; i<bits; i++)
    {
        res[i] = number[i+1];
    }
    res[bits] = 0;
    return res;
}

bool* ALU::rotateRight(bool* number, int bits)
{
    bool* res = new bool[bits];
    for(int i=bits-1; i>0; i--)
    {
        res[i] = number[i-1];
    }
    res[0] = number[bits-1];
    return res;
}

bool* ALU::rotateLeft(bool* number, int bits)
{
    bool* res = new bool[bits];
    bits--;
    for(int i=0; i<bits; i++)
    {
        res[i] = number[i+1];
    }
    res[bits] = number[0];
    return res;
}

