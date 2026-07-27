#include <iostream>
#include "CPP11Features.h"
#include "CPP14Features.h"
#include "Baseprocessor.h"
#include "CPP11Concurrency.h"
#include <thread>
#include <future>

int main() {
    static_assert(CPP11Features::calculateDefaultBufferSize(2) == 2048, "Compile-time buffer size calculation failed.");

    std::unique_ptr<Baseprocessor> processor = std::make_unique<CPP11Features>(500);

    processor->process();

    CPP11Features conceptDemo;
    conceptDemo.runInitializerListDemo({1, 2, 3, 4, 5});

    CPP11Concurrency demo;

    std::thread producerThread(&CPP11Concurrency::producer, &demo, 5);
    std::thread consumerThread(&CPP11Concurrency::consumer, &demo);

    std::future<int> asyncResult = std::async(std::launch::async,&CPP11Concurrency::computeFactorial,9);

    producerThread.join();
    consumerThread.join();

    // // Retrieve output from future
    std::cout << "Async Factorial(9) Result: " << asyncResult.get() << "\n";
    std::cout << "Total Tasks Processed (Atomic): " << demo.getProcessedCount() << "\n";
    

    /**************CPP 14 Features Demo ************/
    static_assert(CPP14Features::calculate_checksum(10, 5) == 30, "C++14 constexpr check failed!");

    CPP14Features cpp14demo;
    std::cout << "--- Executing C++14 Module ---\n";
    std::cout << "Computed Capacity: " << cpp14demo.compute_capacity(100) << "\n";
    
    cpp14demo.demonstrate_lambda_captures();
    return 0;

}
