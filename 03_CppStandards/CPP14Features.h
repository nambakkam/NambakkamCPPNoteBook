/* --- CPP14Features.h --- */

/* ------------------------------------------
Author: Saikiran
Date: 7/23/2026
------------------------------------------ */

#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>

template<typename T>
constexpr T default_scale = T(1.5);

constexpr long double operator"" _kg(long double value) {
return value * 1000.0;
}

class CPP14Features {
public:
    CPP14Features() = default; 
    ~CPP14Features() = default;

    static constexpr int calculate_checksum(int base, int iterations)
    {
        int sum = base;
        for(int i = 0; i < iterations; i++){
            sum += (i*2);
        }
        return sum;
    }

    auto compute_capacity(int count)
    {
        return count * default_scale<double>;
    }


    void demonstrate_lambda_captures();

private:

};

