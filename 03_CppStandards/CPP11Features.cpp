/* --- CPP11Features.cpp --- */

/* ------------------------------------------
author: Saikiran
date: 7/21/2026
------------------------------------------ */

#include "CPP11Features.h"
#include <iostream>
CPP11Features::CPP11Features() : CPP11Features(100) {
    // Constructor
}

CPP11Features::CPP11Features(int maxBufferSize)
    : m_maxBufferSize(maxBufferSize)
{
}


void CPP11Features::process()
{
    std::cout << "Executing process() with override...\n";

        // Trailing return type & decltype demonstration
        auto computeTax = [] (double amount) -> 
        decltype(amount * 0.1) {
            return amount * 0.1; // 10% tax
        };

        // nullptr usage
        int* ptr = nullptr;
        if (ptr == nullptr) {
            std::cout << "nullptr checked safely.\n";
        }
        // 2. SHARED POINTER DEMO (Shared Ownership & Reference Counting)
        auto task1 = std::make_shared<SharedTask>(101, "Data Processing");
        m_sharedTasks.push_back(task1); // Use count becomes 2

        std::cout << "Task ID: " << task1->taskId << ", Task Name: " << task1->taskName 
                  << " | Reference Count: " << task1.use_count() << "\n";

        auto task2 = task1; // Shared ownership, use count becomes 3
        
        std::cout << "Task ID: " << task1->taskId << ", Task Name: " << task1->taskName 
                  << " | Reference Count: " << task1.use_count() << "\n";
        
        task2.reset(); // Release ownership, use count becomes 2
        std::cout << "Task ID: " << task1->taskId << ", Task Name: " << task1->taskName 
                  << " | Reference Count: " << task1.use_count() << "\n";
        
        auto task3 = std::weak_ptr<SharedTask>(task1); // Weak pointer, does not affect use count

        std::cout << "Task ID: " << task1->taskId << ", Task Name: " << task1->taskName 
                  << " | Reference Count: " << task1.use_count() << "\n";
        // Move resource into smart pointer container
        constexpr int buf_size = calculateDefaultBufferSize(2); // Evaluated at compile-time
        DataBuffer raw_buf(buf_size);
        
        // Move semantics with unique_ptr
        m_buffers.push_back(std::make_unique<DataBuffer>(std::move(raw_buf)));

        std::cout << "Calculated Tax: " << computeTax(1000.0) << "\n";
        std::cout << "Buffer created with size: " << m_buffers.back()->size() << " bytes\n";
}

void CPP11Features::runInitializerListDemo(std::initializer_list<int> values)
{
    std::cout << "Initializer List Demo: ";
    for(auto val : values) {
        std::cout << val << " ";
    }
    std::cout << "\n";
}
