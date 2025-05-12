#include <iostream>
#include <string>
#include <algorithm>
#include <windows.h>

using namespace std;

// Set color
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Convert Decimal to Binary
string decimalToBinary(int decimal) {
    string binary = "";
    while (decimal > 0) {
        binary += (decimal % 2 == 0) ? "0" : "1";
        decimal /= 2;
    }
    reverse(binary.begin(), binary.end());
    return binary;
}

// Convert Binary to Decimal
int binaryToDecimal(const string &binary) {
    int decimal = 0, power = 1;
    for (int i = binary.length() - 1; i >= 0; i--) {
        if (binary[i] == '1') decimal += power;
        power *= 2;
    }
    return decimal;
}

// Calculate Parity Bit
char calculateParityBit(const string &binary, bool evenParity) {
    int oneCount = count(binary.begin(), binary.end(), '1');
    return evenParity ? (oneCount % 2 == 0 ? '0' : '1') : (oneCount % 2 == 0 ? '1' : '0');
}

// Apply Bit Stuffing
string bitStuffing(const string &binary) {
    string stuffed = "";
    int onesCount = 0;
    for (char bit : binary) {
        stuffed += bit;
        if (bit == '1') {
            onesCount++;
            if (onesCount == 5) {
                stuffed += '0';
                onesCount = 0;
            }
        } else {
            onesCount = 0;
        }
    }
    return stuffed;
}

// Apply Bit De-stuffing
string bitDestuffing(const string &stuffed) {
    string destuffed = "";
    int onesCount = 0;
    for (size_t i = 0; i < stuffed.length(); i++) {
        char bit = stuffed[i];
        destuffed += bit;
        if (bit == '1') {
            onesCount++;
            if (onesCount == 5 && i + 1 < stuffed.length() && stuffed[i + 1] == '0') {
                i++; // Skip the stuffed '0'
                onesCount = 0;
            }
        } else {
            onesCount = 0;
        }
    }
    return destuffed;
}

// Parity Check
bool parityCheck(const string &binaryWithParity, bool evenParity) {
    string data = binaryWithParity.substr(0, binaryWithParity.length() - 1);
    char expectedParity = calculateParityBit(data, evenParity);
    return expectedParity == binaryWithParity.back();
}

// Main Function
int main() {
    setColor(11);
    cout << "=======================================\n";
    cout << "     GREEN UNIVERSITY OF BANGLADESH\n";
    cout << "   Data Communication Project - 2025\n";
    cout << "  Course Code: CSE 302 Section: 223 D3\n";
    cout << "=======================================\n";

    setColor(14);
    cout << "Project: Binary Conversion with Parity & Bit Stuffing\n";
    cout << "Developed by: [Mim Akter] (ID: 222002104)\n\n";
    setColor(7);

    int decimal;
    string binary;
    int inputType;

    cout << "Do you want to input a Binary number? [1] Yes  [2] No: ";
    cin >> inputType;

    if (inputType == 1) {
        cout << "Enter Binary Number: ";
        cin >> binary;
        decimal = binaryToDecimal(binary);
    } else {
        cout << "Enter Decimal Number: ";
        cin >> decimal;
        binary = decimalToBinary(decimal);
    }

    cout << "Binary Representation: " << binary << endl;

    cout << "Choose Parity Type: [1] Even Parity  [2] Odd Parity: ";
    int choice;
    cin >> choice;
    bool evenParity = (choice == 1);

    char parityBit = calculateParityBit(binary, evenParity);
    string binaryWithParity = binary + parityBit;
    cout << "Binary with Parity Bit: " << binaryWithParity << endl;

    string stuffed = bitStuffing(binaryWithParity);
    cout << "After Bit Stuffing: " << stuffed << endl;

    cout << "\nTransmitting Data...\n\n";

    // Receiver Side
    cout << "At Receiver Side:\n";
    cout << "Received Stuffed Data: " << stuffed << endl;

    string destuffed = bitDestuffing(stuffed);
    cout << "After De-stuffing: " << destuffed << endl;

    if (parityCheck(destuffed, evenParity)) {
        setColor(10);
        cout << "Parity Check: PASSED (No Error Detected)" << endl;
    } else {
        setColor(12);
        cout << "Parity Check: FAILED (Error Detected)" << endl;
        return 1;
    }

    string originalBinary = destuffed.substr(0, destuffed.length() - 1);
    int finalDecimal = binaryToDecimal(originalBinary);
    cout << "Final Decimal Number: " << finalDecimal << endl;

    setColor(11);
    cout << "\n=======================================\n";
    cout << "   DATA TRANSMISSION COMPLETED\n";
    cout << "=======================================\n";

    setColor(7);
    return 0;
}
