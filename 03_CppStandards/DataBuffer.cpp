/* --- DataBuffer.cpp --- */

/* ------------------------------------------
author: Saikiran
date: 7/21/2026
------------------------------------------ */

#include "DataBuffer.h"

DataBuffer::DataBuffer(size_t size) : m_size(size), m_data(new int[size]) {
    // Constructor
}

DataBuffer::~DataBuffer() {
    // Destructor
    delete[] m_data;
}

DataBuffer::DataBuffer(DataBuffer &&other) noexcept :  m_size(other.m_size), m_data(other.m_data) {
    other.m_data = nullptr;
    other.m_size = 0;
}

DataBuffer &DataBuffer::operator=(DataBuffer &&other) noexcept
{
    if(this != &other) {
        delete[] m_data; // Free existing resource
        m_data = other.m_data;
        m_size = other.m_size;

        other.m_data = nullptr;
        other.m_size = 0;
    }
    return *this;
}

size_t DataBuffer::size() const
{
    return m_size;
}
