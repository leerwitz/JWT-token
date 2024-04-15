#include <ctime>
#include <iostream>

#include "myLib.hpp"

class __RSA {
   private:
    std::string number_p_512bit = "6703903964971298549787012499102923063739682910296196688861780721860882015036773488400937149083451713845015929093243025426876941405973284973216824503042159";
    std::string number_q_512bit = "6703903964971298549787012499102923063739682910296196688861780721860882015036773488400937149083451713845015929093243025426876941405973284973216824503042857";
    std::string number_p_256bit = "57896044618658097711785492504343953926634992332820282019728792003956564820063";
    std::string number_q_256bit = "57896044618658097711785492504343953926634992332820282019728792003956564820109";
    std::pair<lnumber, lnumber> private_key;
    std::pair<lnumber, lnumber> public_key;
    lnumber euler_func;

    long long get_random_prime_number(long long max, long long min) {
        size_t res = min + 2;
        while (!is_prime_number(res, min)) {
            res = min + static_cast<long long>(rand()) % (max - min);
        }
        return res;
    }

    bool is_prime_number(size_t number, size_t min) {
        if (number < min) {
            return false;
        } else {
            for (size_t i = 2; i * i <= number; ++i) {
                if (number % i == 0) return false;
            }
        }
        return true;
    }

    long long get_prime_number_ferma(long long max) {
        long long max_degree = get_bit_degree(get_bit_degree(max - 1));
        long long result = static_cast<long long>(pow(2, pow(2, max_degree))) + 1;
        long long coef_a, coef_b;

        for (size_t i = max_degree; i > 0; --i) {
            if (greatest_common_divisor(result, max, coef_a, coef_b) == 1) {
                return result;
            }
            if (i > 0) result >>= pow(2, i - 1);
            ++result;
        }

        result = get_random_prime_number(max, 1);

        return result;
    }

    void create_keys() {
        lnumber prime_number_p, prime_number_q, public_exp, private_exp;

        prime_number_p = lnumber(number_p_256bit);
        prime_number_q = lnumber(number_q_256bit);
        this->private_key.second = prime_number_p * prime_number_q;
        this->public_key.second = this->private_key.second;
        this->euler_func = (prime_number_p - 1) * (prime_number_q - 1);
        public_exp = lnumber(65537);
        private_exp = extended_Euclidean_algorithm(public_exp, this->euler_func);
        this->public_key.first = public_exp;
        this->private_key.first = private_exp;
    }

   public:
    __RSA() { create_keys(); };

    ~__RSA(){};

    std::pair<lnumber, lnumber> get_public_key() { return this->public_key; }

    lnumber message_encryption(std::string &message) {
        message = get_number_string_from_string_99(message);
        lnumber number = lnumber(message);
        pow(number, number, this->public_key.first, this->public_key.second);
        message = get_string_from_lnumber_99(number);

        return number;
    }

    lnumber message_encryption(std::string &message, std::pair<lnumber, lnumber> other_public_key) {
        message = get_number_string_from_string_99(message);
        lnumber number = lnumber(message);
        pow(number, number, other_public_key.first, other_public_key.second);
        message = get_string_from_lnumber_99(number);

        return number;
    }

    lnumber message_decryption_electronic_signature(std::string &message, std::pair<lnumber, lnumber> other_public_key) {
        message = get_number_string_from_string_99(message);
        lnumber number = lnumber(message);
        pow(number, number, other_public_key.first, other_public_key.second);
        message = get_string_from_lnumber_99(number);

        return number;
    }

    std::string message_decryption(lnumber &number) {
        std::string message;
        pow(number, number, this->private_key.first, this->private_key.second);
        message = get_string_from_lnumber_99(number);

        return message;
    }

    std::string message_decryption(std::string &message) {
        message = get_number_string_from_string_99(message);
        lnumber number = lnumber(message);
        pow(number, number, this->private_key.first, this->private_key.second);
        message = get_string_from_lnumber_99(number);

        return message;
    }

    std::string message_encryption_electronic_signature(lnumber &number) {
        std::string message;
        pow(number, number, this->private_key.first, this->private_key.second);
        message = get_string_from_lnumber_99(number);

        return message;
    }

    std::string message_decryption_electronic_signature(std::string &message) {
        message = get_number_string_from_string_99(message);
        lnumber number = lnumber(message);
        pow(number, number, this->public_key.first, this->public_key.second);
        message = get_string_from_lnumber_99(number);

        return message;
    }

    std::string message_encryption_electronic_signature(std::string &message) {
        message = get_number_string_from_string_99(message);
        lnumber number = lnumber(message);
        pow(number, number, this->private_key.first, this->private_key.second);
        message = get_string_from_lnumber_99(number);

        return message;
    }

    std::string message_encryption_electronic_signature(std::string &message, std::pair<lnumber, lnumber> other_private_key) {
        message = get_number_string_from_string_99(message);
        lnumber number = lnumber(message);
        pow(number, number, other_private_key.first, other_private_key.second);
        message = get_string_from_lnumber_99(number);

        return message;
    }
};
