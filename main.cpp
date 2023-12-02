#include <iostream>
#include <numeric>
#include <future>
#include "compfunc.h"

typedef os::lab1::compfunc::comp_result<unsigned> shortDT;

namespace os::lab1::compfunc {
    comp_result<unsigned> compfunc(int);
}

template<typename t>
t calculate_gcd(t a, t b) {
    return std::gcd(a, b);
}


shortDT f(int x) {
    auto result = os::lab1::compfunc::compfunc(x);

    while (std::holds_alternative<os::lab1::compfunc::soft_fault>(result)) {
        std::cout << "." << std::flush;
        result = os::lab1::compfunc::compfunc(x);
    }

    std::cout <<"f(" << x << "): " << result << std::endl;

    return result;

}
shortDT g(int x){
    auto result = os::lab1::compfunc::compfunc(x);

    while (std::holds_alternative<os::lab1::compfunc::soft_fault>(result)) {
        std::cout << "." << std::flush;
        result = os::lab1::compfunc::compfunc(x);
    }

    std::cout <<"g(" << x << "): " << result << std::endl;

    return result;
}

void manager(){
    int x = 0;
    unsigned int valueF;
    unsigned int valueG;


    while (x != -1) {
        std::cin >> x;

        auto fResult = std::async(std::launch::async, f, x);

        auto gResult = std::async(std::launch::async, g, x);

        shortDT resF = fResult.get();
        shortDT resG = gResult.get();


        if (std::holds_alternative<unsigned int>(resF) && std::holds_alternative<unsigned int>(resG)) {
            valueF = std::get<unsigned int>(resF);
            valueG = std::get<unsigned int>(resG);
            std::cout << calculate_gcd(valueF,valueG) << std::endl;
        }



    }

}

int main() {

    manager();
    return 0;
}