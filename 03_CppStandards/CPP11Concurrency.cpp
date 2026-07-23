/* --- CPP11Concurrency.cpp --- */

/* ------------------------------------------
author: Saikiran
date: 7/22/2026
------------------------------------------ */

#include "CPP11Concurrency.h"

CPP11Concurrency::CPP11Concurrency() : m_processedCount{0},m_status{false}
{
}

void CPP11Concurrency::producer(int num_tasks)
{
    for (int i = 0; i < num_tasks; ++i) {
        {
            std::lock_guard<std::mutex> lock(m_queueMutex);
            m_taskQueue.push(i);
            std::cout << "[Producer] Pushed task " << i << "\n";
        } 
        
        // Notify the consumer as soon as a new task is pushed
        m_cv.notify_one(); 

        // Simulate some work producing items (optional)
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    // Signal completion once all tasks have been produced
    {
        std::lock_guard<std::mutex> lock(m_queueMutex);
        m_status = true; // Indicates no more tasks will be added
    }
    
    // Wake up all waiting consumers to check m_status and exit safely
    m_cv.notify_all(); 
}

void CPP11Concurrency::consumer()
{
    while (true)
    {
        int task = 0;

        {
            std::unique_lock<std::mutex> lock(m_queueMutex);

            // Wait until queue is NOT empty OR producer sets m_status = true
            m_cv.wait(lock, [this]() {
                return !m_taskQueue.empty() || m_status;
            });

            // Exit condition: Queue is empty AND producer is finished
            if (m_taskQueue.empty() && m_status) {
                break;
            }

            // Extract the task from the queue
            task = m_taskQueue.front();
            m_taskQueue.pop();
        } // Lock is automatically released here!

        // Do work OUTSIDE the lock to allow high concurrency
        std::cout << "[Consumer] Processing task " << task << "\n";

        // Increment processed count (assuming m_processedCount is std::atomic<int>)
        m_processedCount++; 
    }
}

int CPP11Concurrency::getProcessedCount() const
{
    return m_processedCount.load();
}

int CPP11Concurrency::computeFactorial(int n)
{
    int result = 1;
    for(int i = 1; i <= n; i++){
        result *= i;
    }
    return result;
}
