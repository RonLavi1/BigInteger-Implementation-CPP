//
// Created by ron.lavi1 on 8/25/18.
//

#include "big_integer.h"


/**
 * constructor that gets an int and create a big int object
 * @param number
 */
big_integer::big_integer(int number) //ctor c
{
    if (number >= 0)
    {
        _data = std::to_string(number);
        _isPositive = true;
    }
    else
    {
        _data = std::to_string(-1 * number);
        _isPositive = false;
    }
    _reverseString(_data);
    _length = _data.length();

}

/**
 *
 * constructor that gets a string create a big int object, when given a bad input uses the
 * default constructor
 * @param input
 */
big_integer::big_integer(const std::string &input) //ctor d
{
    if (input.at(0) == '-')
    {
        if (_isValidString(input.substr(1)))
        {

            _data = input.substr(1);
            _reverseString(_data);
            _length = _data.length();
            _isPositive = false;
            _removeUnnecessaryZeros();
        }
    }
    else if (_isValidString(input))
    {
        _data = input;
        _reverseString(_data);
        _length = _data.length();
        _removeUnnecessaryZeros();
        _isPositive = true;

    }
    else
    {
        big_integer();
    }
}

/**
 *
 * @param rhs
 * @return
 */
bool big_integer::operator<(const big_integer &rhs) const
{
    if (_isPositive < rhs._isPositive)
    {
        return true;
    }
    if (_isPositive > rhs._isPositive)
    {
        return false;
    }
    if (_data == rhs._data)
    {
        return false;
    }
    return _compareLowerThan(rhs);

}
/**
 *
 * @param rhs
 * @return
 */
bool big_integer::operator<=(const big_integer &rhs) const
{
    return *this < rhs || *this == rhs;
}
/**
 *
 * @param rhs
 * @return
 */
bool big_integer::operator>(const big_integer &rhs) const
{
    return rhs < *this;
}
/**
 *
 * @param rhs
 * @return
 */
bool big_integer::operator>=(const big_integer &rhs) const
{
    return !(*this < rhs);
}
/**
 *
 * @param rhs
 * @return
 */
bool big_integer::operator==(const big_integer &rhs) const
{
    return _data == rhs._data && _isPositive == rhs._isPositive;
}
/**
 *
 * @param rhs
 * @return
 */
bool big_integer::operator!=(const big_integer &rhs) const
{
    return !(*this == rhs);
}


std::ostream &operator<<(std::ostream &os, const big_integer &integer)
{
    if (!integer._isPositive)
    {
        os << '-';
    }
    for (size_t i = integer._data.length() - 1; i >= 1; i--)
    {
        os << integer._data.at(i);
    }
    os << integer._data.at(0);
    return os;
}
/**
 *
 * @param other
 * @return
 */
big_integer big_integer::operator+(const big_integer &other)
{

    const auto &newOther = other;
    std::string result;
    if (_isLeftLarger(other))
    {
        result = _plusMinusOperationsHelper(*this, newOther);
    }
    else
    {
        result = _plusMinusOperationsHelper(newOther, *this);
    }
    _reverseString(result);
    return big_integer(result);
}
/**
 *
 * @param other
 * @return
 */
big_integer &big_integer::operator+=(const big_integer &other)
{
    const auto &newOther = other;
    std::string result;
    if (_isLeftLarger(other))
    {
        result = _plusMinusOperationsHelper(*this, newOther);
    }
    else
    {
        result = _plusMinusOperationsHelper(newOther, *this);
    }
    if (result.back() == '-')
    {
        result.pop_back();
        _isPositive = !(result != "0");
    }
    else
    {
        this->_isPositive = true;
    }
    this->_length = result.length();
    this->_data = result;
    return *this;
}

/**
 *
 * @param other
 * @return
 */
big_integer big_integer::operator-(const big_integer &other)
{
    big_integer newOther = other;
    newOther._isPositive = !newOther._isPositive;
    return *this + newOther;
}

/**
 *
 * @param other
 * @return
 */
big_integer &big_integer::operator-=(const big_integer &other)
{
    big_integer newOther = other;
    newOther._isPositive = !newOther._isPositive;
    return *this += newOther;
}

/**
 *
 * @param other
 * @return
 */
big_integer big_integer::operator*(const big_integer &other)
{
    if (_data == "0" || other._data == "0")
    {
        return big_integer();
    }
    std::string stringResult = _multiply(other);
    _reverseString(stringResult);
    big_integer result = big_integer(stringResult);
    result._isPositive = _isPositive == other._isPositive;
    return result;
}

/**
 *
 * @param other
 * @return
 */
big_integer &big_integer::operator*=(const big_integer &other)
{
    if (_data == "0" || other._data == "0")
    {
        *this = big_integer();
        return *this;
    }
    std::string stringResult = _multiply(other);
    _isPositive = _isPositive == other._isPositive;
    _length = stringResult.length();
    _data = stringResult;
    return *this;
}

/**
 *
 * @param other
 * @return
 */
big_integer big_integer::operator/(const big_integer &other)
{
    if (other._data == "0")
    {
        return big_integer();
    }
    big_integer denominator = other;
    big_integer numerator = *this;
    denominator._isPositive = true;
    numerator._isPositive = true;
    std::string result = _divide(numerator, denominator);
    _reverseString(result);
    result = _removeUnnecessaryZeros(result);
    _reverseString(result);
    if (_isPositive == other._isPositive)
    {
        return big_integer(result);
    }
    std::string minusFinal = '-' + result;
    return big_integer(minusFinal);
}

/**
 *
 * @param other
 * @return
 */
big_integer &big_integer::operator/=(const big_integer &other)
{
    if (other._data == "0")
    {
        *this = big_integer();
        return *this;
    }
    big_integer denominator = other;
    big_integer numerator = *this;
    denominator._isPositive = true;
    numerator._isPositive = true;
    std::string result = _divide(numerator, denominator);
    _reverseString(result);
    result = _removeUnnecessaryZeros(result);
    _reverseString(result);
    _isPositive = _isPositive == other._isPositive;
    if (result == "0")
    {
        _isPositive = true;
    }
    _reverseString(result);
    _data = result;
    return *this;
}

/**
 *
 * @param other
 * @return
 */
big_integer big_integer::operator%(const big_integer &other)
{
    if (other._data == "0")
    {
        return big_integer();
    }
    return *this - ((*this / other) * other); // inspirited by NAND
}

/**
 *
 * @param rVal
 * @return
 */
big_integer &big_integer::operator=(const big_integer &rVal)
= default;

/**
 * removes zero from the stars of the data as ""00xy" is no valid number(number has to
 * begin left to right with a digit other than '0'.
 */
void big_integer::_removeUnnecessaryZeros()
{
    while (_length)
    {
        if (_data.at(_length - 1) == '0')
        {
            _data.pop_back();
            --_length;
        }
        else
        {
            break;
        }
    }
    if (_data.empty())
    {
        _data = "0";
        _length = 1;
        _isPositive = true;
    }
}

/**
 * removes zero from the stars of the string as ""00xy" is no valid number(number has to
 * begin left to right with a digit other than '0'.
 * @param number
 * @return
 */
std::string big_integer::_removeUnnecessaryZeros(std::string &number)
{
    size_t length = number.length();
    while (length)
    {
        if (number.at(length - 1) == '0')
        {
            number.pop_back();
            --length;
        }
        else
        {
            break;
        }
    }
    if (number.empty())
    {
        return "0";
    }
    return number;
}

/**
 * string validatior for the input given to the string constructor
 * @param toValid
 * @return
 */
bool big_integer::_isValidString(const std::string &toValid)
{

    for (char c : toValid)
    {
        if (!std::isdigit(c))
        {
            return false;
        }
    }
    return true;
}

/**
 * Reverse the string given
 * @param stringToReverse
 */
void big_integer::_reverseString(std::string &stringToReverse)
{
    size_t n = stringToReverse.length();
    for (size_t i = 0; i < n / 2; i++)
    {
        std::swap(stringToReverse.at(i), stringToReverse.at(n - i - 1));
    }
}

/**
 * helper function to the < operator implementation. assumes both numbers has the same sign.
 * @param rhs
 * @return is *this smaller than rhs.
 */
bool big_integer::_compareLowerThan(const big_integer &rhs) const
{
    if (_isPositive)
    {
        if (_length < rhs._length)
        {
            return true;
        }
        if (_length > rhs._length)
        {
            return false;
        }
        for (size_t i = _length - 1; i >= 1; i--)
        {
            if (_data.at(i) - '0' < rhs._data.at(i) - '0')
            {
                return true;
            }
            if (_data.at(i) - '0' > rhs._data.at(i) - '0')
            {
                return false;
            }
        }
        return _data.at(0) - '0' < rhs._data.at(0) - '0';
    }
    else
    {
        if (_length < rhs._length)
        {
            return false;
        }
        if (_length > rhs._length)
        {
            return true;
        }
        for (size_t i = _length - 1; i > 0; i--)
        {
            if (_data.at(i) > rhs._data.at(i))
            {
                return true;
            }
            if (_data.at(i) < rhs._data.at(i))
            {
                return false;
            }
        }
        return _data.at(0) > rhs._data.at(0);
    }
}

/**
 * helper function than culculates the number of times the part integer contained in divider.
 * assumes 9 at most.
 * @param divider
 * @param part
 * @return
 */
big_integer big_integer::_divideHelper(big_integer &divider, big_integer &part)
{
    for (int i = 0; i < 10; i++)
    {
        if (part < (big_integer(i) * divider))
        {
            return big_integer(i - 1);
        }
    }
    return big_integer(9);
}

/**
 * Uses long division algorithm to divide the numerator/denominator
 * @param numerator
 * @param denominator
 * @return the result of the devision
 */
std::string big_integer::_divide(big_integer &numerator, big_integer &denominator)
{
    big_integer miCalc;
    std::string strResult;
    std::string strNumerator = numerator._data;
    _reverseString(strNumerator);
    big_integer partial = big_integer(strNumerator.at(0) - '0');
    for (size_t i = 0; i < numerator._data.length(); i++)
    {
        miCalc = _divideHelper(denominator, partial);
        partial = partial - (miCalc * denominator);
        strResult += miCalc._data;
        if (i == numerator._data.length() - 1)
        {
            break;
        }
        partial = big_integer(strNumerator.at(i + 1) - '0') + partial * big_integer(10);
    }
    return strResult;
}

/**
 * calcultes the multupications of *this and other
 * @param second
 * @return
 */
std::string big_integer::_multiply(const big_integer &other)
{
    int carry, currentDigit, currentOtherDigit, sum;
    big_integer tempResult = big_integer();
    big_integer result = big_integer();
    std::string current;
    for (size_t i = 0; i < other._data.length(); i++)
    {
        current = "";
        tempResult._data = '0';
        currentOtherDigit = other._data.at(i) - '0';
        _addZeroes(current, i);
        carry = 0;
        for (char j : this->_data)
        {
            currentDigit = j - '0';
            sum = carry + (currentDigit * currentOtherDigit);
            carry = sum / 10;
            current.push_back(static_cast<char>((sum % 10) + '0'));
        }
        if (carry)
        {
            current.push_back(static_cast<char>(carry) + '0');
        }
        tempResult._data = current;
        result += tempResult;
    }
    return result._data;
}

/**
 * pad a string with zeroes for further use in long division
 * @param currentNumber empty string to pad with zeroes
 * @param numOfZeroesToAdd
 */
void big_integer::_addZeroes(std::string &currentNumber, size_t numOfZeroesToAdd)
{
    for (size_t j = 0; j < numOfZeroesToAdd; j++)
    {
        currentNumber.push_back('0');
    }
}

/**
 * helper function to get the < relation. assumes both numbers has the same sign.
 * @param other
 * @return
 */
bool big_integer::_isLeftLarger(const big_integer &other)
{
    // if left is large than the right
    if (_data.length() < other._data.length())
    {
        return false;
    }
    if (_data.length() == other._data.length())
    {
        return !_smallerThanOperator(other);
    }
    return true;

}

/**
 * Helper to the + and - operations
 * @param longer
 * @param shorter
 * @return
 */
std::string big_integer::_plusMinusOperationsHelper(const big_integer &large, const big_integer &small)
{
    std::string result;
    if (large._isPositive == small._isPositive)
    {
        result = _add(large, small);
        if (large._isPositive)
        {
            return result;
        }
        else
        {
            result.push_back('-');
        }
    }
    else
    {
        result = _subtractHelper(large, small);
        if (!large._isPositive && small._isPositive)
        {
            if (large._data != small._data)
            {
                result.push_back('-');
            }
        }
    }
    return result;
}

/**
 * Given two numbers of the same size(number of digits). Assumes positivity of the two numbers
 * @param rhs
 * @return true if the object(this) is smaller than rhs (*this < rhs)
 */
bool big_integer::_smallerThanOperator(const big_integer &rhs) const
{
    for (size_t i = _length - 1; i > 0; i--)
    {
        if ((_data.at(i) - '0') < (rhs._data.at(i) - '0'))
        {
            return true;
        }
        if ((_data.at(i) - '0') > (rhs._data.at(i) - '0'))
        {
            return false;
        }
    }
    return _data.at(0) - '0' < rhs._data.at(0) - '0';
}
/**
 * Implemnting long addition algorithm
 * @param small the smaller number digit wise
 * @param large the larger number digit wise
 * @return
 */
std::string big_integer::_add(const big_integer &large, const big_integer &small) const
{
    // add until the small ends:
    int carry = 0, curShort, curLong, totalSum;
    std::string result;
    for (size_t i = 0; i < large._data.length(); i++)
    {
        if (i >= small._data.length())
        {
            curShort = 0;
        }
        else
        {
            curShort = small._data.at(i) - '0';
        }
        curLong = large._data.at(i) - '0';
        totalSum = curShort + curLong + carry;

        result.push_back('0' + (char) (totalSum % 10));
        carry = totalSum / 10;
    }
    if (carry == 1)
    {
        result.push_back('1');
    }
    return result;
}
/**
 * helper function for the subtract case,
 * @param shorter
 * @param longer
 * @return
 */
std::string big_integer::_subtractHelper(const big_integer &large, const big_integer &small)
{
    std::string result;
    int carry = 0;
    int curShort, curLong, totalSum;
    for (size_t i = 0; i < large._data.length(); i++)
    {
        if (i < small._length)
        {
            curShort = small._data.at(i) - '0';
        }
        else
        {
            curShort = 0;
        }
        curLong = large._data.at(i) - '0' - carry;
        totalSum = curLong - curShort;
        if (totalSum < 0)
        {
            carry = 1;
            totalSum += 10;
        }
        else
        {
            carry = 0;
        }

        result.push_back(static_cast<char>(totalSum + '0'));
    }
    result = _removeUnnecessaryZeros(result);
    return result;
}