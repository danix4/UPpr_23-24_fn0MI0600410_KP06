/**
 *
 * Solution to course project #4
 * Introduction to programming course
 * Faculty of Mathematics and Informatics of Sofia University
 * Winter semester 2023/2024
 *
 * @author Daniel Nikolov
 * @idnumber 0MI0600410
 * @compiler GCC
 *
 * <functions file>
 *
 */

#include <string>
#include <vector>
#include "functions.h"

using namespace std;

const int amount_of_words = 64; // 16*32 = 512
const int chunk_size = 512;
const int word_length = 32;

// Function that converts string to binary representation
vector<bool> convertToBinary(const string& input) {
    vector<bool> binaryArray;

    for (char c : input) {
        for (int j = 7; j >= 0; j--) {
            binaryArray.push_back((c >> j) & 1);
        }
    }

    return binaryArray;
}

// Converts a bool array into hexadecimal value
unsigned int convertToHex(const bool wordArray[word_length]) {
    unsigned int hexValue = 0;

    for (int i = 0; i < 32; ++i) {
        hexValue = (hexValue << 1) | wordArray[i];
    }

    return hexValue;
}

// Making an array divisible by 512, then removing the last 64 elements
void mod512(vector<bool>& binary) {
    while (binary.size() % 512 != 0) {
        binary.push_back(false);
    }

    for (int i = 0; i < 64; i++) {
        binary.pop_back();
    }
}

// Adding the last 64 elements
void add64(vector<bool>& binary, unsigned int size) {
    size = size * 8;
    vector<bool> lastDigits;

    while (size != 0) {
        unsigned int n = size % 2;
        lastDigits.insert(lastDigits.begin(), n);
        size = size / 2;
    }

    while (lastDigits.size() != 64) {
        lastDigits.insert(lastDigits.begin(), false);
    }

    binary.insert(binary.end(), lastDigits.begin(), lastDigits.end());
}

// Padding with zeros
void paddingZeros(bool wordArray[][word_length]) {
    for (int i = 16; i < amount_of_words; i++) {
        for (int j = 0; j < word_length; j++) {
            wordArray[i][j] = false;
        }
    }
}

// Right rotating the bits of an int
unsigned int rightRotate(unsigned int hexValue, int n) {
    const unsigned int bitSize = sizeof(unsigned int) * 8;
    return (hexValue >> n) | (hexValue << (bitSize - n));
}

// Right shifting the bits of an int
unsigned int rightShift(unsigned int hexValue, int n) {
    return hexValue >> n;
}

// Main algorithm function
string sha256(vector<bool> binary) {
    unsigned int h0 = 0x6a09e667;
    unsigned int h1 = 0xbb67ae85;
    unsigned int h2 = 0x3c6ef372;
    unsigned int h3 = 0xa54ff53a;
    unsigned int h4 = 0x510e527f;
    unsigned int h5 = 0x9b05688c;
    unsigned int h6 = 0x1f83d9ab;
    unsigned int h7 = 0x5be0cd19;

    // Array of constants
    vector<unsigned int> array_of_constants = {
            0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b,
            0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
            0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7,
            0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
            0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152,
            0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
            0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc,
            0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
            0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819,
            0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08,
            0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f,
            0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
            0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };

    bool wordArray[amount_of_words][word_length];

    // Dividing the whole array into chunks of 512 elements
    for (int i = 0; i < binary.size(); i += chunk_size) {
        int counter = -1;

        for (int j = i; j < i + chunk_size && j < binary.size(); j++) {
            int k = j % word_length;

            if (k == 0) counter++;
            wordArray[counter][k] = binary[j];
        }

        paddingZeros(wordArray);

        unsigned int hexArray[amount_of_words];

        for (int l = 0; l < amount_of_words; l++) {
            unsigned int x = convertToHex(wordArray[l]);
            hexArray[l] = x;
        }

        for (int y = 16; y < amount_of_words; y++) {
            unsigned int r7 = rightRotate(hexArray[y - 15], 7);
            unsigned int r18 = rightRotate(hexArray[y - 15], 18);
            unsigned int r3 = rightShift(hexArray[y - 15], 3);

            unsigned int s0 = r7 ^ r18 ^ r3;

            unsigned int r17 = rightRotate(hexArray[y - 2], 17);
            unsigned int r19 = rightRotate(hexArray[y - 2], 19);
            unsigned int r10 = rightShift(hexArray[y - 2], 10);

            unsigned int s1 = r17 ^ r19 ^ r10;

            hexArray[y] = hexArray[y - 16] + s0 + hexArray[y - 7] + s1;
        }

        unsigned int a = h0;
        unsigned int b = h1;
        unsigned int c = h2;
        unsigned int d = h3;
        unsigned int e = h4;
        unsigned int f = h5;
        unsigned int g = h6;
        unsigned int h = h7;

        // Compression loop
        for (int n = 0; n < 64; n++) {
            unsigned int e6 = rightRotate(e, 6);
            unsigned int e11 = rightRotate(e, 11);
            unsigned int e25 = rightRotate(e, 25);

            unsigned int S1 = e6 ^ e11 ^ e25;

            unsigned int ch = (e & f) ^ ((~e) & g);
            unsigned int temp1 = h + S1 + ch + array_of_constants[n] + hexArray[n];

            unsigned int a2 = rightRotate(a, 2);
            unsigned int a13 = rightRotate(a, 13);
            unsigned int a22 = rightRotate(a, 22);

            unsigned int S0 = a2 ^ a13 ^ a22;

            unsigned int maj = (a & b) ^ (a & c) ^ (b & c);

            unsigned int temp2 = S0 + maj;

            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        h0 = h0 + a;
        h1 = h1 + b;
        h2 = h2 + c;
        h3 = h3 + d;
        h4 = h4 + e;
        h5 = h5 + f;
        h6 = h6 + g;
        h7 = h7 + h;
    }

    // Making the final value
    char outputArray[33];
    sprintf(outputArray, "%08X%08X%08X%08X%08X%08X%08X%08X", h0, h1, h2, h3, h4, h5, h6, h7);
    string output(outputArray);

    return output;
}
