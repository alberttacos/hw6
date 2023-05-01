#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>


typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        unsigned long long w[5] = {0};
        size_t LimOfHash = k.length()/6;

        if(k.length() % 6){
          LimOfHash++;
        }

        for(size_t i = 0; i < LimOfHash; i++){
          unsigned long base = 1;
          unsigned long long number = 0;
          

          for(size_t j = i * 6; j < (i * 6) + 6; j++){
            if(j < k.length()){
              number += letterDigitToNumber(k[k.length() - j - 1]) * base;
            }
            base *= 36;
          }
          w[4-i] = number;
        }
        return rValues[0] * w[0] + rValues[1] * w[1] + rValues[2] * w[2] + rValues[3] * w[3] + rValues[4] * w[4];
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if(letter >= 'A' && letter <= 'Z'){
          letter -= 'A' - 'a';
        }
        if(letter >= 'a' && letter <= 'z'){
          return letter - 'a';
        }
        if(letter >= '0' && letter <= '9'){
          return letter - '0' + 26; 
        }else{
          throw std::runtime_error("Invalid Character");
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
