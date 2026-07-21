#include <iostream>
#include "CPP11Features.h"
#include "Baseprocessor.h"
int main() {
    static_assert(CPP11Features::calculateDefaultBufferSize(2) == 2048, "Compile-time buffer size calculation failed.");

    std::unique_ptr<Baseprocessor> processor = std::make_unique<CPP11Features>(500);

    processor->process();

    CPP11Features conceptDemo;
    conceptDemo.runInitializerListDemo({1, 2, 3, 4, 5});
    return 0;
}
