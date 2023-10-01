#include <iostream>
#include <string>
using namespace std;

string bin_int(int num, int bits) {
    // Convert an integer to its binary representation with a specified number of bits.
    string bin_num = "";
    while (num > 0) {
        bin_num = to_string(num % 2) + bin_num;
        num /= 2;
    }

    while (bin_num.length() < bits) {
        bin_num = "0" + bin_num;
    }

    return bin_num;
}

string bin_dob(double num, int bits) {
    // Convert a double-precision floating-point number to its binary representation with a specified number of bits.
    string bin_num = "";

    while (num > 0 && bin_num.length() < bits + 2) {
        num *= 2;
        if (num >= 1) {
            bin_num += "1";
            num -= 1;
        }
        else {
            bin_num += "0";
        }
    }

    while (bin_num.length() < bits + 2) {
        bin_num += "0";
    }

    return bin_num;
}

void inside_dob(double dob_num) {
    // Display the internal representation of a double-precision floating-point number.
    double mant, flag_neg = 0, flag_other = 0;
    int degree = 0;

    if (dob_num < 1 && dob_num > -1) {
        flag_other = 1;
    }

    if (dob_num < 0) {
        cout << "Sign: 1" << "\n";
        dob_num = -dob_num;
        flag_neg = 1;
    }
    else {
        cout << "Sign: 0" << "\n";
    }

    if (!flag_other) {
        while ((1 > dob_num / pow(2, degree)) || (dob_num / pow(2, degree) > 2)) {
            degree++;
        }
    }
    else {
        while ((1 > dob_num * pow(2, degree)) || (dob_num * pow(2, degree) > 2)) {
            degree++;
        }
    }

    if (!flag_other) {
        mant = dob_num / pow(2, degree) - 1;
        degree = 1023 + degree;
    }
    else {
        mant = dob_num * pow(2, degree) - 1;
        degree = 1023 - degree;
    }

    cout << "Exponent: " << bin_int(degree, 11) << "\n" << "Mantissa: " << bin_dob(mant, 51);
}

void inside_int(int int_num) {
    // Display the internal representation of a short integer.
    if (int_num < 0) {
        cout << "Sign: 1" << "\n";
        int_num = -int_num;
    }
    else {
        cout << "Sign: 0" << "\n";
    }

    cout << "Integer part: " << bin_int(int_num, 16);
}

short int shift_int(short int num, int move, int steps) {
    // Perform a bitwise shift operation on a short integer.
    if (steps <= 0) {
        return num;
    }
    uint16_t* new_num = reinterpret_cast<uint16_t*>(&num);
    uint16_t bun_bits = *new_num;

    switch (move) {
    case 1: // Left shift
        bun_bits <<= steps;
        break;
    case 2: // Right shift
        bun_bits >>= steps;
        break;
    default:
        cout << "Invalid shift direction." << endl;
        return num;
    }

    *new_num = bun_bits;

    return num;
}

double dob_shift(double num, int move, int steps) {
    // Perform a bitwise shift operation on a double-precision floating-point number.
    if (steps <= 0) {
        return num;
    }

    uint64_t* new_num = reinterpret_cast<uint64_t*>(&num);
    uint64_t num_bits = *new_num;

    switch (move) {
    case 1: // Left shift
        num_bits <<= steps;
        break;
    case 2: // Right shift
        num_bits >>= steps;
        break;
    default:
        cout << "Invalid shift direction." << endl;
        return num;
    }

    *new_num = num_bits;

    return num;
}

double output_dob_shift(int shift, int steps, double dob_num) {
    cout << "\nEnter direction of shift: \n1 - Left \n2 - Right\n";
    cin >> shift;
    while (shift != 1 && shift != 2) {
        cout << "Invalid input, please try again \n1 - Left \n2 - Right\n";
        cin >> shift;
    }
    cout << "Number of positions to shift?\n";
    cin >> steps;

    return dob_shift(dob_num, shift, steps);
}

double output_int_shift(int shift, int steps, int int_num) {
    cout << "\nEnter direction of shift: \n1 - Left \n2 - Right\n";
    cin >> shift;
    while (shift != 1 && shift != 2) {
        cout << "Invalid input, please try again \n1 - Left \n2 - Right\n";
        cin >> shift;
    }
    cout << "Number of positions to shift?\n";
    cin >> steps;

    return shift_int(int_num, shift, steps);
}

int main() {
    double dob_num, shifted_dob_num;
    int int_num, shift = 0, steps = 0, shifted_int_num;

    cout << "Enter a number which internal representation you want to see (type: double): ";
    cin >> dob_num;
    inside_dob(dob_num);

    shifted_dob_num = output_dob_shift(shift, steps, dob_num);

    cout << "New number: " << shifted_dob_num << endl;
    cout << "Its internal representation: " << endl;
    inside_dob(shifted_dob_num);

    cout << "\n\nEnter a number which internal representation you want to see (type: short int): \n";
    cin >> int_num;
    inside_int(int_num);
    shifted_int_num = output_int_shift(shift, steps, int_num);

    cout << "New number: " << shifted_int_num << endl;
    cout << "Its internal representation: " << endl;
    inside_int(shifted_int_num);
}
