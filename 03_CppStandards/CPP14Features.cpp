/* --- CPP14Features.cpp --- */

/* ------------------------------------------
author: Saikiran
date: 7/23/2026
------------------------------------------ */

#include "CPP14Features.h"

void CPP14Features::demonstrate_lambda_captures()
{
    int flag_mask = 0b1100'1010;
    long max_units = 1'000'000;

    auto mass = 5.0_kg;
// 5 kilograms is converted to 5000 grams
    std::cout << "Converted Mass: " << mass << " flagMask: " << flag_mask << " max_units: " << max_units <<  "\n";

    auto data_block = std::make_unique<std::string>("Heap Resource Managed by Unique Pointer");

    auto processor = [block = std::move(data_block)](const auto& prefix){
        std::cout << prefix << ": " << *block << "\n";
    };

    processor("Processing Data");
    processor(101);
}

