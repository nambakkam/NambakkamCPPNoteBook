/* --- DataBuffer.h --- */

/* ------------------------------------------
Author: Saikiran
Date: 7/21/2026
------------------------------------------ */

#pragma once
#include <memory>
// 2. Move-only class to practice move semantics & rvalue references
class DataBuffer {
public:
    explicit DataBuffer(size_t size);
    ~DataBuffer();

    DataBuffer(const DataBuffer&) = delete; // Disable copy constructor

    DataBuffer& operator=(const DataBuffer&) = delete; // Disable copy assignment

    DataBuffer(DataBuffer&& other) noexcept;
    
    DataBuffer& operator=(DataBuffer&& other) noexcept;

    size_t size() const;
private:
    size_t m_size;
    int* m_data;
    

};

