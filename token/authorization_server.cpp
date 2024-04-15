#include <ctime>

#include "../update_RSA.hpp"

struct payload {
    std::string login;
    std::string password;
    const time_t exp = 300;  // in seconds
    time_t time_of_creation;
} typedef payload;

class token {
   private:
    std::string get_payload(payload second) {
        std::string result = second.login;
        result += '/' + second.password;
        result += '/' + std::to_string(second.exp);
        result += '/' + std::to_string(second.time_of_creation);
        return result;
    }

    std::pair<std::string, std::string> header = std::pair<std::string, std::string>("RSA", "JWT");
    payload second_part;
    __RSA rsa = __RSA();
    std::string signature;
    void get_signature() {
        this->signature = this->header.first + this->header.second + "." + get_payload(this->second_part);
        rsa.message_encryption_electronic_signature(this->signature);
    }

    void get_signature(std::pair<lnumber, lnumber> other_private_key) {
        this->signature = this->header.first + this->header.second + "." + get_payload(this->second_part);
        rsa.message_encryption_electronic_signature(this->signature, other_private_key);
    }

   public:
    token(std::string login, std::string password) {
        this->second_part.login = login;
        this->second_part.password = password;
        time(&this->second_part.time_of_creation);
        get_signature();
    };

    token(std::string login, std::string password, std::pair<lnumber, lnumber> other_private_key) {
        this->second_part.login = login;
        this->second_part.password = password;
        time(&this->second_part.time_of_creation);
        get_signature(other_private_key);
    };

    ~token(){};

    std::string get_token() {
        std::string first = this->header.first + this->header.second;
        rsa.message_encryption_electronic_signature(first);
        std::string second = get_payload(this->second_part);
        rsa.message_encryption_electronic_signature(second);

        std::string result = first + "." + second + "." + this->signature;
        return result;
    }

    std::string get_token(std::pair<lnumber, lnumber> other_private_key) {
        std::string first = this->header.first + this->header.second;
        rsa.message_encryption_electronic_signature(first, other_private_key);
        std::string second = get_payload(this->second_part);
        rsa.message_encryption_electronic_signature(second, other_private_key);

        std::string result = first + "." + second + "." + this->signature;
        return result;
    }

    std::pair<lnumber, lnumber> get_public_key() { return this->rsa.get_public_key(); }

    time_t get_time_of_creation() { return this->second_part.time_of_creation; }
};

int main() {
    std::cout << "Your login: ";
    std::string login, password;
    std::pair<lnumber, lnumber> private_key;
    std::pair<std::string, std::string> private_key_string;
    std::cin >> login;
    std::cout << "Your password: ";
    std::cin >> password;
    std::cout << "Your private key:\n FIRST NUMBER:\n";
    std::cin >> private_key_string.first;
    std::cout << "SECOND NUMBER:\n";
    std::cin >> private_key_string.second;
    private_key = private_key_string;

    token jwt_token = token(login, password, private_key);

    std::cout << "TOKEN:\n" << jwt_token.get_token(private_key) << '\n';

    return 0;
}
