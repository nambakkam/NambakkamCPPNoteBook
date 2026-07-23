/* --- CPP11Concurrency.h --- */

/* ------------------------------------------
Author: Saikiran
Date: 7/22/2026
------------------------------------------ */

#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <future>
#include <atomic>
#include <chrono>
class CPP11Concurrency {
public:
    CPP11Concurrency();
    ~CPP11Concurrency() = default;
    void producer(int num_tasks);
    void consumer();
    int getProcessedCount() const;
    static int computeFactorial(int n);
private:
    std::queue<int> m_taskQueue;
    std::mutex m_queueMutex;
    std::condition_variable m_cv;
    std::atomic<int> m_processedCount;
    bool m_status;

};

