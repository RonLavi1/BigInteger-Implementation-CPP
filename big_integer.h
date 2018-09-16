//
// Created by ron.lavi1 on 8/25/18.
//

#ifndef CPP_BIG_INTEGER_H
#define CPP_BIG_INTEGER_H

#include <iostream>

/**
 * This class allows to create a big integer(bigger than unsigned long) numbers. it uses the
 * string format to do so. each object has fields to describe its data,length, positivity.
 * the class supports the following operations between two objects : +,+=,-,-=,*,*=,/,/=,%,<<,=,
 * ==,!=,<,<=,>,>=.
 */
class big_integer
{
private:

    std::string _data; //Stores a reverse representation of the big int(such that the most
    // significant digit is at the end of the string) e.g for 1204 _data[0] = 4.

    bool _isPositive; //True if the number is 0 or higher(false o.w).

    size_t _length; //stores the length of the string(for iterations reasons)

    /**
     * Implemnting long addition algorithm
     * @param small the smaller number digit wise
     * @param large the larger number digit wise
     * @return
     */
    std::string _add(const big_integer &small, const big_integer &large) const;


    /**
     * pad a string with zeroes for further use in long division
     * @param currentNumber empty string to pad with zeroes
     * @param numOfZeroesToAdd
     */
    void _addZeroes(std::string &currentNumber, size_t numOfZeroesToAdd);


    /**
     * helper function to the < operator implementation. assumes both numbers has the same sign.
     * @param rhs
     * @return is *this smaller than rhs.
     */
    bool _compareLowerThan(const big_integer &rhs) const;

    /**
     * Uses long division algorithm to divide the numerator/denominator
     * @param numerator
     * @param denominator
     * @return the result of the devision
     */
    std::string _divide(big_integer &numerator, big_integer &denominator);

    /**
     * helper function than culculates the number of times the part integer contained in divider.
     * assumes 9 at most.
     * @param divider
     * @param part
     * @return
     */
    big_integer _divideHelper(big_integer &divider, big_integer &part);

    /**
     * helper function to get the < relation. assumes both numbers has the same sign.
     * @param other
     * @return
     */
    bool _isLeftLarger(const big_integer &other);

    /**
     * string validatior for the input given to the string constructor
     * @param toValid
     * @return
     */
    bool _isValidString(const std::string &toValid);

    /**
     * calcultes the multupications of *this and other
     * @param second
     * @return
     */
    std::string _multiply(const big_integer &other);

    /**
     * Helper to the + and - operations
     * @param longer
     * @param shorter
     * @return
     */
    std::string _plusMinusOperationsHelper(const big_integer &large, const big_integer &small);

    /**
     * removes zero from the stars of the data as ""00xy" is no valid number(number has to
     * begin left to right with a digit other than '0'.
     */
    void _removeUnnecessaryZeros();

    /**
     * removes zero from the stars of the string as ""00xy" is no valid number(number has to
     * begin left to right with a digit other than '0'.
     * @param number
     * @return
     */
    std::string _removeUnnecessaryZeros(std::string &number);

    /**
     * Reverse the string given
     * @param stringToReverse
     */
    void _reverseString(std::string &stringToReverse);

    /**
     * Given two numbers of the same size(number of digits). Assumes positivity of the two numbers
     * @param rhs
     * @return true if the object(this) is smaller than rhs (*this < rhs)
     */
    bool _smallerThanOperator(const big_integer &rhs) const;

    /**
     * helper function for the subtract case,
     * @param shorter
     * @param longer
     * @return
     */
    std::string _subtractHelper(const big_integer &large, const big_integer &small);

public:

////////////////CONSTRUCTORS//////////////////////

    /**
     * default constructor
     */
    big_integer() : _data("0"), _isPositive(true), _length(1)
    {};

    /**
     * copy constructor
     */
    big_integer(const big_integer &to_copy) : _data(to_copy._data),
                                              _isPositive(to_copy._isPositive),
                                              _length(to_copy._length)
    {}; //COPY CTOR

    /**
     * constructor that gets an int and create a big int object
     */
    big_integer(int number);


    /**
     * constructor that gets a string create a big int object, when given a bad input uses the
     * default constructor
     */
    big_integer(const std::string &input);



//////////////////////////////////////////////////


////////////OPERATORS///////////////

    /**
     *
     * @param other
     * @return
     */
    big_integer &operator+=(const big_integer &other);

    /**
     *
     * @param other
     * @return
     */
    big_integer &operator-=(const big_integer &other);

    /**
     *
     * @param other
     * @return
     */
    big_integer &operator*=(const big_integer &other);

    /**
     *
     * @param other
     * @return
     */
    big_integer &operator/=(const big_integer &other);

    /**
     *
     * @param other
     * @return
     */
    big_integer operator+(const big_integer &other);

    /**
     *
     * @param other
     * @return
     */
    big_integer operator-(const big_integer &other);

    /**
     *
     * @param other
     * @return
     */
    big_integer operator*(const big_integer &other);

    /**
     *
     * @param other
     * @return
     */
    big_integer operator/(const big_integer &other);

    /**
     *
     * @param other
     * @return
     */
    big_integer operator%(const big_integer &other);

    /**
     *
     * @param rVal
     * @return
     */
    big_integer &operator=(const big_integer &rVal);


    ///////////RELATIONAL OPERATORS//////////////
    /**
     *
     * @param rhs
     * @return
     */
    bool operator<(const big_integer &rhs) const;

    /**
     *
     * @param rhs
     * @return
     */
    bool operator>(const big_integer &rhs) const;

    /**
     *
     * @param rhs
     * @return
     */
    bool operator<=(const big_integer &rhs) const;

    /**
     *
     * @param rhs
     * @return
     */
    bool operator>=(const big_integer &rhs) const;


    /////////////EQUALITY OPERATOR////////////////

    /**
     *
     * @param rhs
     * @return
     */
    bool operator==(const big_integer &rhs) const;

    /**
     *
     * @param rhs
     * @return
     */
    bool operator!=(const big_integer &rhs) const;

    /**
     * create a printable version on the big number .
     * @param os
     * @param integer
     * @return
     */
    friend std::ostream &operator<<(std::ostream &os, const big_integer &integer);

};


#endif //CPP_BIG_INTEGER_H
