// Copyright (C) 2016 hutchimw@miamiOH.edu

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hutchimw_NumberCheck.cpp
 * Author: Mark Hutchinson
 *
 * Created on October 17, 2017, 9:43 PM
 */

#include <omp.h>
#include <iostream>
#include <string>

std::string palindrome;
std::string prime;
std::string primeFactorable;
std::string factorial;

bool isPrime(int num) {
    bool isPrime = true;
    if (num % 2 == 0 && num != 2) {
        isPrime = false;
    } else {
        for (int i = 1; i < num; ++i) {
            if (num % i == 0 && i != 1) {
                isPrime = false;
            }
        }
    }
    if (num == 2) {
        isPrime = true;
    }
    if (num == 1) {
        isPrime = false;
    }
    return isPrime;
}

bool isPrimeFactorable(int num) {
    bool primeFactorable = false;
    for (int i = 1; i < num; ++i) {
        if (num % i == 0) {
            int multiplier = num / i;
            if (isPrime(i) && isPrime(multiplier)) {
                primeFactorable = true;
            } else {
                primeFactorable = false;
            }
        }
    }
    return primeFactorable;
}

bool isPalindromic(int num) {
    bool palindromic = false;
    std::string number = std::to_string(num);
    if (number == std::string(number.rbegin(), number.rend())) {
        palindromic = true;
    }
    return palindromic;
}

int computeFactorial(int num) {
    int fact = 1;
#pragma omp parallel for
    for (int counter = 1; counter <= num; ++counter) {
        fact = fact * counter;
    }
    return fact;
}

bool isFactorial(int num) {
    bool factorial = false;
#pragma omp parallel for
    for (int i = 0; i < num/2; ++i) {
        if (computeFactorial(i) == num) {
            factorial = true;
        }
    }
    return factorial;
}

std::string primeCheck(int i) {
    if (isPrime(i)) {
        prime = "is prime";
    } else {
        prime = "not prime";
    }
    return prime;
}

std::string primeFactorCheck(int i) {
    if (isPrimeFactorable(i)) {
        primeFactorable = "is factorable";
    } else {
        primeFactorable = "not factorable";
    }
    return primeFactorable;
}

std::string factorialCheck(int i) {
    if (isFactorial(i)) {
        factorial = "is factorial";
    } else {
        factorial = "not factorial";
    }
    return factorial;
}

std::string palindromeCheck(int i) {
    if (isPalindromic(i)) {
        palindrome = "is palindromic";
    } else {
        palindrome = "not palindromic";
    }
    return palindrome;
}

int main(int argc, char** argv) {
    int start = atoi(argv[1]);
    int stop = atoi(argv[2]);
    
// #pragma omp parallel for
    for (int i = start; i < stop+1; ++i) {
        primeCheck(i);
        primeFactorCheck(i);
        factorialCheck(i);
        palindromeCheck(i);
        
        std::cout << i << ": " << prime << ", " << primeFactorable
                << ", " << factorial << ", " << palindrome << std::endl;
    }
    return 0;
}

