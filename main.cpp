#include <iostream>
#include <numeric>
#include <future>
#include "compfunc.h"

namespace os::lab1::compfunc {
    comp_result<unsigned> compfunc(int );
}

template<typename t>
t calculate_gcd(t a, t b) {
    return std::gcd(a, b);
}


os::lab1::compfunc::comp_result<unsigned> f(int x) {
    auto result = os::lab1::compfunc::compfunc(x);

    while (std::holds_alternative<os::lab1::compfunc::soft_fault>(result)) {
        std::cout << "." << std::flush;
        result = os::lab1::compfunc::compfunc(x);
    }

    std::cout <<"f(" << x << "): " << result << std::endl;

    return result;

}
os::lab1::compfunc::comp_result<unsigned> g(int x){
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
    while (x != -1) {
        std::cin >> x;

        auto futureF = std::async(std::launch::async,f, x);
        auto futureG = std::async(std::launch::async,  g, x);

        os::lab1::compfunc::comp_result<unsigned> resF = futureF.get();
        os::lab1::compfunc::comp_result<unsigned> resG = futureG.get();

        std::cout << "f(x): " << resF << " g(x): " << resG << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

}

int main() {

    manager();
    return 0;
}
