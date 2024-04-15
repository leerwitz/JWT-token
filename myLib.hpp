#include <iostream>

#include "update_long_arithmetic.hpp"

long long modular_multiplication(long long a, long long b, long long mod);
long long pow(long long variable, long long power, long long mod);
long long get_bit_degree(long long value);
long long pow(long long variable, long long power);
long long greatest_common_divisor(long long a, long long b, long long &coefficient_on_a, long long &coefficient_on_b);
long long extended_Euclidean_algorithm(long long a, long long modulus_value);
std::string get_number_string_from_string(std::string str);
std::string get_string_from_lnumber(lnumber number);
std::string get_number_string_from_string_99(std::string str);
std::string get_number_string_from_string_991(std::string str);
long long modular_multiplication(long long a, long long b, long long mod) { return a * b % mod; }
std::string get_string_from_lnumber_99(lnumber number);
std::string get_string_from_lnumber_991(lnumber number);
char get_character(int value);
lnumber greatest_common_divisor(lnumber a, lnumber b, lnumber &coefficient_on_a, lnumber &coefficient_on_b);
lnumber extended_Euclidean_algorithm(lnumber a, lnumber modulus_value);
size_t get_numerical_order(std::vector<int> number);

long long pow(long long variable, long long power, long long mod) {
    long long current_multiplier = variable, result = 1;

    while (power != 0) {
        current_multiplier = current_multiplier % mod;
        if (power % 2 == 1) {
            result = modular_multiplication(result, current_multiplier, mod);
            --power;
        }
        current_multiplier = modular_multiplication(current_multiplier, current_multiplier, mod);
        power /= 2;
    }

    return result % mod;
}

long long get_bit_degree(long long value) {
    long long t = 1 << 30, result = 30;
    while (value < t) {
        --result;
        t >>= 1;
    }

    return result;
}

long long pow(long long variable, long long power) {
    long long current_multiplier = variable, result = 1;

    while (power != 0) {
        current_multiplier = current_multiplier;
        if (power % 2 == 1) {
            result *= current_multiplier;
            --power;
        }
        current_multiplier *= current_multiplier;
        power /= 2;
    }

    return result;
}

long long greatest_common_divisor(long long a, long long b, long long &coefficient_on_a, long long &coefficient_on_b) {
    if (a == 0) {
        coefficient_on_a = 0;
        coefficient_on_b = 1;
        return b;
    } else {
        long long new_coefficient_on_a = 0, new_coefficient_on_b = 0;
        long long res = greatest_common_divisor(b % a, a, new_coefficient_on_a, new_coefficient_on_b);
        coefficient_on_b = new_coefficient_on_a;
        coefficient_on_a = new_coefficient_on_b - b / a * new_coefficient_on_a;

        return res;
    }
}

long long extended_Euclidean_algorithm(long long a, long long modulus_value) {
    long long coefficient_on_a, coefficient_on_b;
    if (greatest_common_divisor(a, modulus_value, coefficient_on_a, coefficient_on_b) != 1) {
        return 0;
    } else {
        coefficient_on_a = (coefficient_on_a % modulus_value + modulus_value) % modulus_value;
    }

    return coefficient_on_a;
}

lnumber greatest_common_divisor(lnumber a, lnumber b, lnumber &coefficient_on_a, lnumber &coefficient_on_b) {
    if ((a.digits[0] == 0 && a.digits.size() == 1)) {
        coefficient_on_a = lnumber(0);
        coefficient_on_b = lnumber(1);
        return b;
    } else {
        lnumber new_coefficient_on_a, new_coefficient_on_b;
        lnumber res = greatest_common_divisor(b % a, a, new_coefficient_on_a, new_coefficient_on_b);
        coefficient_on_b = new_coefficient_on_a;
        coefficient_on_a = new_coefficient_on_b - b / a * new_coefficient_on_a;

        return res;
    }
}

lnumber extended_Euclidean_algorithm(lnumber a, lnumber modulus_value) {
    lnumber coefficient_on_a, coefficient_on_b;
    if (greatest_common_divisor(a, modulus_value, coefficient_on_a, coefficient_on_b) != 1) {
        return 0;
    } else {
        coefficient_on_a = (coefficient_on_a % modulus_value + modulus_value) % modulus_value;
    }

    return coefficient_on_a;
}

size_t get_numerical_order(std::vector<int> number) { return std::to_string(number.back()).size() + (number.size() - 1) * 9; }

std::string get_number_string_from_string(std::string str) {
    std::string number_str = "";
    for (char ch : str) {
        if (static_cast<long long>(ch) < 10) number_str += "0";
        if (static_cast<long long>(ch) < 100) number_str += "0";
        number_str += std::to_string(static_cast<long long>(ch));
    }
    return number_str;
}

std::string get_number_string_from_string_99(std::string str) {
    std::string number_str = "";
    int current_number;
    for (size_t i = 0; i < str.size(); ++i) {
        int ascii_number = 0;
        if (str[i] == '~')
            str[i] = '.';
        else if (str[i] == '}')
            str[i] = '\\';
        else if (str[i] == '\\' && i < str.size() - 1) {
            ascii_number = atoi(str.substr(i + 1, 2).c_str());
            if (ascii_number > 24 && ascii_number < 33) {
                number_str += '0';
                number_str += std::to_string(ascii_number - 25);
                i += 2;
            }
        }
        if (ascii_number == 0 || ascii_number > 32 || ascii_number < 25) {
            current_number = static_cast<int>(str[i]) - 25;
            if (current_number < 10) number_str += '0';
            number_str += std::to_string(static_cast<int>(current_number));
        }
    }
    return number_str;
}

std::string get_string_from_lnumber(lnumber number) {
    std::string number_string = "";
    std::string res = "";
    std::string cur;
    size_t string_lenght = get_numerical_order(number.digits);

    for (int i = number.digits.size() - 1; i >= 0; --i) {
        cur = std::to_string(number.digits[i]);
        for (long long j = 0; j < 9 - static_cast<long long>(cur.size()) && i != static_cast<int>(number.digits.size()) - 1 && cur.size() < 10; ++j) number_string += '0';
        number_string += cur;
    }

    for (int i = 0; i < static_cast<int>(string_lenght); i += 3) {
        if (i == 0) {
            res += static_cast<char>(atoi(number_string.substr(i, 3 - (3 - (string_lenght % 3)) % 3).c_str()));
            i -= (3 - (string_lenght % 3)) % 3;
        } else {
            res += static_cast<char>(atoi(number_string.substr(i, 3).c_str()));
        }
    }

    return res;
}

char get_character(int value) {
    char result;
    if (value == 21)
        result = '~';
    else if (value == 67)
        result = '}';
    else
        result = static_cast<char>(value + 25);
    return result;
}

std::string get_string_from_lnumber_99(lnumber number) {
    std::string string_number = std::string(number), result = "";
    int carry;
    for (size_t i = 0; i < string_number.size(); i += 2) {
        if (i == 0 && string_number.size() % 2) {
            carry = atoi(string_number.substr(i, 1).c_str());
            ++i;
            if (carry < 8)
                result += '\\' + std::to_string(carry + 25);
            else
                result += get_character(carry);
        }
        carry = atoi(string_number.substr(i, 2).c_str());
        if (carry < 8)
            result += '\\' + std::to_string(carry + 25);
        else
            result += get_character(carry);
    }
    return result;
}