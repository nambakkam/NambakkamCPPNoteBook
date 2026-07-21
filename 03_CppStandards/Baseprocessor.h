/* --- Baseprocessor.h --- */

/* ------------------------------------------
Author: Saikiran
Date: 7/21/2026
------------------------------------------ */

#pragma once
// 1. Base Class to practice override / final / =default / =delete
class Baseprocessor {
public:
    Baseprocessor() = default;
    virtual ~Baseprocessor() = default;

    Baseprocessor(const Baseprocessor&) = delete;
    Baseprocessor& operator=(const Baseprocessor&) = delete;
    virtual void process() = 0;
private:

};


