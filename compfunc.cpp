//
// Created by megao on 01.12.2023.
//

#include "compfunc.h"

#include <chrono>
#include <thread>
#include <condition_variable>


namespace os::lab1::compfunc {

    using namespace std::chrono_literals;
    using duration = std::chrono::seconds;

    const int CASE3_ATTEMPTS = 3;

    comp_result<int> compfunc(int newN) {
        int n = newN;

        if(n%2 == 1 && n != 1 && n != 0 && n != 51 && n != 10){
            n = 3;
        }


        switch(n) {
            case 0:
                std::this_thread::sleep_for(std::chrono::seconds(3));
                return 24;
            case 1:
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return hard_fault();
            case 2:
            {
                std::condition_variable cv;
                std::mutex m;
                std::unique_lock<std::mutex> lock(m);
                cv.wait(lock, []{return false;});
                return soft_fault();
            }
            case 3:
            {static constinit int attempts = 3;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                if (attempts-- > 0)
                    return soft_fault();
                attempts = 3;
                return n;
            }
            case 10:
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return hard_fault();
            case 51:
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return hard_fault();
            default:
                return n;
        }
    }
}
