/* --- CPP11Features.h --- */

/* ------------------------------------------
Author: Saikiran
Date: 7/21/2026
------------------------------------------ */

#pragma once
#include "Baseprocessor.h"
#include "DataBuffer.h"
#include <vector>
#include <initializer_list>
#include <memory>
#include <string>

struct SharedTask {
    int taskId;
    std::string taskName;
    // Additional fields can be added as needed
    SharedTask(int id, const std::string& name) : taskId{id}, taskName{name} {}
};

class CPP11Features final : public Baseprocessor {
public:
    CPP11Features();
    explicit CPP11Features(int maxBufferSize);
    ~CPP11Features() = default;

    static constexpr int calculateDefaultBufferSize(int multiplier){
        return 1024 * multiplier;
    }

    void process() override;
     void runInitializerListDemo(std::initializer_list<int> values);
private:
    std::vector<std::unique_ptr<DataBuffer>> m_buffers; // Using smart pointers to manage DataBuffer objects
    int m_maxBufferSize;
    std::vector<std::shared_ptr<SharedTask>> m_sharedTasks;

};

