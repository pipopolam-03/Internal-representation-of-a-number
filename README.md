# Internal-representation-of-a-number
This project shows how to display the internal representation of double and short int numbers in C++.

# Some theory
The storage format for real numbers is described by the IEEE 754 standard in the form of a mantissa (M) with a sign (S) and an exponent (P) value. The number of bits used to store the mantissa and exponent depends on the floating-point data type.

float: M - 23 bits, P - 8 bits, S - 1 bit.

double: M - 52 bits, P - 11 bits, S - 1 bit.

A real number is stored in memory with a normalized mantissa, the decimal value of which falls within the range from 1 to 2, with 2 not being included in the range. If, during the execution of any floating-point operation, the mantissa value goes out of the specified range, normalization is performed at the end of the operation by bringing the mantissa value within the specified range with the corresponding adjustment of the exponent value. In this case, the most significant bit of the mantissa must be set to one. If the exponent value exceeds the allowable value, an overflow flag is raised.

If the mantissa value is zero, or if the exponent value becomes smaller than the allowable value during the operation, a "machine zero" is formed as a result of the operation, which means that the code has all bits set to zero. However, if the mantissa is always normalized, the most significant bit, which is one, can be omitted in memory storage. The standard proposes not to store this bit in memory, thereby doubling the precision of representing real numbers. This one is present implicitly, hidden from the observer's eye, and is called the implicit one.

The order of the number in accordance with the specified format is stored "shifted," meaning that a certain number is added to its actual value, depending on the format, to ensure that the exponent P is always non-negative. For the float format, 127 is added, for double numbers, 1023 is added, and for long double format, 16383 is added. The always non-negative exponent simplifies the comparison of exponents and arithmetic operations on them, as well as eliminates the need to allocate one bit for storing the sign of the exponent.

For example, the number 15.375 (1111.011 in binary) in the IEEE float format is represented as follows:
1.921875 (1.111011 in binary) is the value of the normalized mantissa;
3 (11 in binary) is the exponent in unbiased binary form (15.375 = 1.921875 * 8);
0 is the sign of the number.

Taking into account the omission of the implicit one and the exponent shift, we get the internal representation of the number:
S = 0;
P = 3 + 127 = 130 (10000010 in binary);
M = 11101100000000000000000.

Thus, the internal representation of the number 15.375 in the double format will be:

0  |	10000000010	| 11101100000000000...00000000000000000000000

# Implementation

The algorithm described above is implemented in the "inside_dob" function. 
Also I wrote it for short int format, but it's easyer - you shoud output only sign and binary number, and add nulls so that there will be 16 bits (function "inside_int").

# Bonus

The final part of this project is algorithm of shifting double and short int numbers in the specified direction for the specified number of bits (functions "dob_shift" and "int_shift"). These functions uses the reinterpret_cast operator to convert a pointer to a given number into a pointer to an unsigned 64-bit integer (uint64_t). This is done to enable working directly with the bitwise representation of the number.
Next, the value of the bitwise representation of the original number is stored in a new variable. The function examines the parameters passed to it to determine the direction and the number of bits to shift, and it performs the shift using standard bitwise operations in C++.


