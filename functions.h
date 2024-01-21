/**
*
* Solution to course project # 4
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Daniel Nikolov
* @idnumber 0MI0600410
* @compiler GCC
*
* <functions prototype>
*
*/

#ifndef KURSOVA_FUNCTIONS_H
#define KURSOVA_FUNCTIONS_H
#include <vector>
#include <string>

using namespace std;

vector<bool> convertToBinary(const string& input);

unsigned int convertToHex(const bool word_array[32]);

void mod512(vector<bool> &binary);

void add64(vector<bool> &binary, unsigned int size);

// Function to right-rotate a hexadecimal integer
unsigned int rightRotate(unsigned int hexValue, int n);

// Function to right-shift a hexadecimal integer
unsigned int rightShift(unsigned int hexValue, int n);

string sha256(vector<bool> binary);


#endif //KURSOVA_FUNCTIONS_H
