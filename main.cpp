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
 * <main file>
 *
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "functions.h"

using namespace std;

int main() {

    int choice;

    // User manual
    cout << "Enter your text in the input file. Then choose an option: " << endl;
    cout << "1: Hashing the input text file" << endl;
    cout << "2: Comparing hash value to the input text file" << endl;
    cout << "Make your choice by entering 1 or 2" << endl;
    cin >> choice;

    if (choice == 1) {

        ifstream file("input.txt");

        if (file.is_open()) {

            string input;
            string line;

            // Read the content of the file line by line
            while (getline(file, line)) {
                input += line + " ";
            }

            file.close();
            input.pop_back(); // Removing the last space

            unsigned int size_of_original = input.size();

            // Convert string to binary vector
            vector<bool> binary = convertToBinary(input);

            // Append '1' to the binary vector
            binary.push_back(true);

            // Padding with 0s til 512 then -64
            mod512(binary);

            // Add 64 bits to the end as big endian integer
            add64(binary, size_of_original);

            string output = sha256(binary);

            // Save the modified content to a new file in the same directory
            ofstream outputFile("output.txt");

            if (outputFile.is_open()) {
                outputFile << output;
                outputFile.close();
                cout << "Hashed file saved to 'output.txt'" << endl;
            } else {
                cout << "Unable to create the output file." << endl;
            }

        } else {
            cout << "Unable to open the file." << endl;
        }

    }

    else if (choice == 2) {

        string user_input;
        cout << "Enter your hashed value:" << endl;
        cin >> user_input;

        ifstream file("input.txt");

        if (file.is_open()) {
            string input;
            string line;

            // Read the content of the file line by line
            while (getline(file, line)) {
                input += line + " ";
            }

            file.close();
            input.pop_back(); // Removing the last space

            unsigned int size_of_original = input.size();

            // Convert string to binary vector
            vector<bool> binary = convertToBinary(input);

            // Append '1' to the binary vector
            binary.push_back(true);

            // Padding with 0s til 512 then -64
            mod512(binary);

            // Add 64 bits to the end as big endian integer
            add64(binary, size_of_original);

            string output = sha256(binary);

            if (user_input == output) {
                cout << "They match!";
            } else {
                cout << "They are different";
            }

        } else {
            cout << "Unable to open the file." << endl;
        }

    }

    return 0;
}

