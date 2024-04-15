#include <stdlib.h>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

class lnumber {
   public:
    static const int base = 1e9;
    std::vector<int> digits;
    bool is_negative_number = false;

    lnumber(){};
    lnumber(std::string str);
    lnumber(long long number);
    lnumber(int number);

    void remove_leading_zeros();

    class divide_by_zero : public std::exception {};

    operator std::string() const;
    friend bool operator==(const lnumber&, const lnumber&);
    friend bool operator<(const lnumber&, const lnumber&);
    friend bool operator!=(const lnumber&, const lnumber&);
    friend bool operator<=(const lnumber&, const lnumber&);
    friend bool operator>(const lnumber&, const lnumber&);
    friend bool operator>=(const lnumber&, const lnumber&);
    friend const lnumber operator+(lnumber, const lnumber&);
    friend const lnumber operator-(lnumber, const lnumber&);
    friend const lnumber operator*(const lnumber&, const lnumber&);
    friend const lnumber operator/(const lnumber&, const lnumber&);
    friend const lnumber operator%(const lnumber&, const lnumber&);
    const lnumber operator-() const;
    const lnumber operator+() const;
    lnumber& operator+=(const lnumber&);
    lnumber& operator-=(const lnumber&);
    lnumber& operator*=(const lnumber&);
    lnumber& operator/=(const lnumber&);
    lnumber& operator%=(const lnumber&);
    const lnumber operator++();
    const lnumber operator++(int);
    const lnumber operator--();
    const lnumber operator--(int);
    void shift_right();
    bool odd() const;
    bool even() const;
    friend std::ostream& operator<<(std::ostream& stream, const lnumber& lnum);
    friend const lnumber pow(lnumber& result, lnumber multiplier, lnumber power);
    friend const lnumber pow(lnumber& result, lnumber multiplier, lnumber power, lnumber mod);
};

lnumber::lnumber(std::string str) {
    if (str.length() == 0) {
        this->is_negative_number = false;
    } else {
        if (str[0] == '-') {
            str = str.substr(1);
            this->is_negative_number = true;
        } else
            this->is_negative_number = false;
        for (long long i = str.length(); i > 0; i -= 9) {
            if (i < 9)
                this->digits.push_back(atoi(str.substr(0, i).c_str()));
            else {
                this->digits.push_back(atoi(str.substr(i - 9, 9).c_str()));
            }
        }
        this->remove_leading_zeros();
    }
}

lnumber::lnumber(long long num) {
    if (num < 0) {
        this->is_negative_number = true;
        num = -num;
    }
    while (num != 0) {
        this->digits.push_back(num % base);
        num /= base;
    }
}

lnumber::lnumber(int i) {
    this->digits.push_back(i % lnumber::base);
    i /= lnumber::base;
    if (i != 0) this->digits.push_back(i);
}

void lnumber::remove_leading_zeros() {
    while (this->digits.size() > 1 && this->digits.back() == 0) this->digits.pop_back();

    if (this->digits.size() == 1 && this->digits[0] == 0) this->is_negative_number = false;
}

std::ostream& operator<<(std::ostream& stream, const lnumber& lnum) {
    if (lnum.digits.empty())
        stream << 0;
    else {
        if (lnum.is_negative_number) stream << '-';
        stream << lnum.digits.back();
        char old_fill = stream.fill('0');
        for (long long i = static_cast<long long>(lnum.digits.size() - 2); i >= 0; --i) {
            stream << std::setw(9) << lnum.digits[i];
        }
        stream.fill(old_fill);
    }
    return stream;
}

lnumber::operator std::string() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

bool operator==(const lnumber& left, const lnumber& right) {
    if (left.digits.empty()) {
        if (right.digits.empty() || (right.digits.size() == 1 && right.digits[0] == 0))
            return true;
        else
            return false;
    }

    if (right.digits.empty()) {
        if (left.digits.empty() || (left.digits.size() == 1 && left.digits[0] == 0))
            return true;
        else
            return false;
    }

    if (left.is_negative_number != right.is_negative_number) return false;
    if (left.digits.size() != right.digits.size())
        return false;
    else
        for (long long i = static_cast<long long>(left.digits.size() - 1); i >= 0; --i) {
            if (left.digits[i] != right.digits[i]) return false;
        }
    return true;
}

bool operator<(const lnumber& left, const lnumber& right) {
    if (left == right) return false;

    if (left.is_negative_number) {
        if (right.is_negative_number)
            return (-right) < (-left);
        else
            return true;
    } else if (right.is_negative_number)
        return false;
    else if (left.digits.size() != right.digits.size())
        return left.digits.size() < right.digits.size();
    else {
        for (long long i = static_cast<long long>(left.digits.size() - 1); i >= 0; --i) {
            if (left.digits[i] != right.digits[i]) return left.digits[i] < right.digits[i];
        }
    }
    return false;
}

bool operator!=(const lnumber& left, const lnumber& right) { return !(left == right); }

bool operator<=(const lnumber& left, const lnumber& right) { return (left == right || left < right); }

bool operator>(const lnumber& left, const lnumber& right) { return right < left; }

bool operator>=(const lnumber& left, const lnumber& right) { return (left == right || left > right); }

const lnumber lnumber::operator+() const { return lnumber(*this); }

const lnumber lnumber::operator-() const {
    lnumber copy(*this);
    if (copy != 0) copy.is_negative_number = !copy.is_negative_number;
    return copy;
}

const lnumber operator+(lnumber left, const lnumber& right) {
    if (left.is_negative_number) {
        if (right.is_negative_number)
            return -((-left) + (-right));
        else
            return right - (-left);
    } else if (right.is_negative_number)
        return left - (-right);
    int carry = 0;
    for (size_t i = 0; i < std::max(left.digits.size(), right.digits.size()) || carry != 0; ++i) {
        if (i == left.digits.size()) left.digits.push_back(0);
        left.digits[i] += carry + (i < right.digits.size() ? right.digits[i] : 0);
        if (left.digits[i] >= lnumber::base) {
            carry = left.digits[i] / lnumber::base;
            left.digits[i] %= lnumber::base;
        } else
            carry = 0;
    }
    return left;
}

const lnumber operator-(lnumber left, const lnumber& right) {
    if (left == 0) {
        return -right;
    }
    if (right.is_negative_number)
        return left + (-right);
    else if (left.is_negative_number)
        return -(-left + right);
    if (left < right) return -(right - left);
    int carry = 0;
    for (size_t i = 0; i < right.digits.size() || carry != 0; ++i) {
        left.digits[i] -= carry + (i < right.digits.size() ? right.digits[i] : 0);
        carry = (left.digits[i] < 0);
        if (carry != 0) left.digits[i] += lnumber::base;
    }
    left.remove_leading_zeros();

    return left;
}

lnumber& lnumber::operator+=(const lnumber& value) { return *this = (*this + value); }

lnumber& lnumber::operator-=(const lnumber& value) { return *this = (*this - value); }

const lnumber lnumber::operator++() { return (*this += 1); }

const lnumber lnumber::operator++(int) {
    *this += 1;
    return *this - 1;
}

const lnumber lnumber::operator--() { return *this -= 1; }

const lnumber lnumber::operator--(int) {
    *this -= 1;
    return *this + 1;
}

const lnumber operator*(const lnumber& left, const lnumber& right) {
    lnumber result;
    result.digits.resize(left.digits.size() + right.digits.size());
    for (size_t i = 0; i < left.digits.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < right.digits.size() || carry != 0; ++j) {
            long long current = carry + left.digits[i] * 1ll * (j < right.digits.size() ? right.digits[j] : 0) + result.digits[i + j];
            result.digits[i + j] = static_cast<int>(current % lnumber::base);
            carry = static_cast<int>(current / lnumber::base);
        }
    }
    result.is_negative_number = (left.is_negative_number != right.is_negative_number);
    result.remove_leading_zeros();

    return result;
}

void lnumber::shift_right() {
    if (this->digits.size() == 0) {
        this->digits.push_back(0);
    } else {
        this->digits.push_back(this->digits[this->digits.size() - 1]);
        for (long long i = this->digits.size() - 2; i > 0; --i) {
            this->digits[i] = this->digits[i - 1];
        }
        this->digits[0] = 0;
    }
}

const lnumber operator/(const lnumber& left, const lnumber& right) {
    if (right == 0) throw lnumber::divide_by_zero();
    lnumber copy_right = right;
    copy_right.is_negative_number = false;
    lnumber result, current;
    result.digits.resize(left.digits.size());
    for (long long i = static_cast<long long>(left.digits.size() - 1); i >= 0; --i) {
        current.shift_right();
        current.digits[0] = left.digits[i];
        current.remove_leading_zeros();
        int x = 0, l = 0, r = lnumber::base;
        while (l <= r) {
            int m = (l + r) / 2;
            lnumber temp = copy_right * m;
            if (temp <= current) {
                x = m;
                l = m + 1;
            } else
                r = m - 1;
        }

        result.digits[i] = x;
        current = current - copy_right * x;
    }
    result.is_negative_number = (left.is_negative_number != right.is_negative_number);
    result.remove_leading_zeros();
    return result;
}

const lnumber operator%(const lnumber& left, const lnumber& right) {
    lnumber a = left / right;
    lnumber b = a * right;
    lnumber result = left - b;
    if (result.is_negative_number) result += right;
    return result;
}

bool lnumber::odd() const {
    if (this->digits.size() == 0) return false;
    return this->digits[0] & 1;
}

bool lnumber::even() const { return !this->odd(); }

const lnumber pow(lnumber& result, lnumber multiplier, lnumber power) {
    if (power == 0) {
        return lnumber(1);
    }
    if (power.even()) {
        result = pow(result, multiplier * multiplier, power / 2);
    } else {
        --power;
        result = pow(result, multiplier, power);
        result *= multiplier;
    }
    return result;
}

const lnumber pow(lnumber& result, lnumber multiplier, lnumber power, lnumber mod) {
    if (power == 0) {
        return lnumber(1);
    }
    if (power.even()) {
        multiplier = (multiplier * multiplier) % mod;
        result = pow(result, multiplier, power / 2, mod);
    } else {
        result %= mod;
        --power;
        result = pow(result, multiplier, power, mod) % mod;
        result = (result * multiplier) % mod;
    }
    return (result + mod) % mod;
}

lnumber& lnumber::operator*=(const lnumber& value) { return *this = (*this * value); }

lnumber& lnumber::operator/=(const lnumber& value) { return *this = (*this / value); }

lnumber& lnumber::operator%=(const lnumber& value) { return *this = (*this % value); }