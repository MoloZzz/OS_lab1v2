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

    comp_result<unsigned> compfunc(int n) {
        switch(n) {
            case 0:
                std::this_thread::sleep_for(3s);
                return comp_result<unsigned>(0xaa55U);
            case 1:
                std::this_thread::sleep_for(1s);
                return hard_fault();
            case 2:
            {
                std::condition_variable cv;
                std::mutex m;
                std::unique_lock<std::mutex> lock(m);
                cv.wait(lock, []{return false;});
                return {};
            }
            case 3:
                static constinit int attempts = CASE3_ATTEMPTS;
                std::this_thread::sleep_for(.5s);
                if (attempts-- > 0)
                    return soft_fault();
                attempts = CASE3_ATTEMPTS;
                return ~0U;

            default:
                return hard_fault();
        }
    }
}
