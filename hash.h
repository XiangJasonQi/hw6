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
        // Add your code here
        HASH_INDEX_T stored_array[28] = {};

        for(int i = 0; i < k.size(); i++){
            stored_array[i] = letterDigitToNumber(k[i]);
        }

        unsigned long long converted_value[5] = {0};
        int index = k.size() - 1;
        int j = 4;
        unsigned long long temp = 0;


        for(int i = k.size(); i > 0; i-=6){
            if(i >= 6){
                for(int x = 0; x < 6; x++){
                    temp += stored_array[index - x]*std::pow(36, x);
                }
                converted_value[j] = temp;
                index -= 6;
                j--;
            } else if(i < 6 && i >= 0){
                int x = i;
                int z = 0;
                for(x; x > 0; x--){
                    temp += stored_array[index - z]*std::pow(36, z);
                    z++;
                }
                converted_value[j] = temp;
            }
            temp = 0;
        }

        temp = 0;

        for(int i = 0; i < 5; i++){
            temp += rValues[i]*converted_value[i];
        }

        return temp;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35

    //return -1 if not error
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if(65 <= letter && letter <= 90){
            letter = letter + 32;
        }

        if(97 <= letter && letter <= 122){
            return letter - 'a';
        } else if(48 <= letter && letter <= 57){
            return letter + 26 - '0';
        }

        return -1;
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
