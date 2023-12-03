#include <iostream>
#include <numeric>
#include <future>
#include <chrono>
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

    if(x != 0){ x = x * 3 + 1; }

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
    shortDT resF;
    shortDT resG;

    bool f_done = false;
    bool g_done = false;
    auto time = std::chrono::milliseconds(500);
    auto timeout = std::chrono::seconds(4);
    bool timeoutFlag = false;


    while (x != -1) {


        std::cin >> x;
        f_done = false;
        g_done = false;

        auto fResult = std::async(std::launch::async , f, x);
        std::future_status statusF;


        auto gResult = std::async(std::launch::async , g, x);
        std::future_status statusG;

        auto start_time = std::chrono::steady_clock::now();


        do {
            switch(statusF = fResult.wait_for( time); statusF) {
                case std::future_status::timeout:
                    std::cout << "WaitingF\n";
                    break;
                case std::future_status::ready:
                    if(!f_done){
                    std::cout << "readyF(x)!\n";
                    f_done = true;
                    }

                    break;
            }

            switch(statusG = gResult.wait_for(time); statusG) {
                case std::future_status::timeout:
                    std::cout << "WaitingG\n";
                    break;
                case std::future_status::ready:
                    if(!g_done){
                        std::cout << "readyG(x)!\n";
                        g_done = true;
                    }
                    break;
            }

            if(std::chrono::steady_clock::now() - start_time >= timeout){
                std::cout << "time out" << std::endl;
                timeoutFlag = true;
                break;
            }
        } while (
                (statusF != std::future_status::ready || statusG != std::future_status::ready));


        if(timeoutFlag){
            std::cout<< "Timeout. Calculation Failed" << std::endl;
            //kill f g
            break;
        }else{
            resF = fResult.get();
            resG = gResult.get();
        }

        if (std::holds_alternative<unsigned int>(resF) && std::holds_alternative<unsigned int>(resG)) {
            valueF = std::get<unsigned int>(resF);
            valueG = std::get<unsigned int>(resG);
            std::cout << "GSD(f(x),g(x)): "<<  calculate_gcd(valueF,valueG) << std::endl;
        }else if(!std::holds_alternative<unsigned int>(resF) && std::holds_alternative<unsigned int>(resG)){
            std::cout << "Calculation failed. Function F(x) did not response" << std::endl;
        }else if(std::holds_alternative<unsigned int>(resF) && !std::holds_alternative<unsigned int>(resG)){
            std::cout << "Calculation failed. Function G(x) did not response" << std::endl;
        }else{
            std::cout << "Calculation failed. Both function did not response" << std::endl;
        }

    }

}

int main() {

    manager();
    return 0;
}