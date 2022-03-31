//
// RollingDice.cpp -- Application main file
//

#include <iostream>
#include <future>
#include <random>
#include <chrono>
#include <thread>

#include <conio.h>

int main()
{
    std::cout << "Rolling Dice (2x W6)\n"
        << "Press any key to exit\n";

    std::atomic<bool> running{ true };
    auto runner = std::async(
        std::launch::async,
        [&running]() -> void {
            constexpr const int sleepSteps = 10;
            constexpr const std::chrono::milliseconds sleepDur{ 1000 / sleepSteps };

            std::default_random_engine eng{ std::chrono::system_clock::now().time_since_epoch().count() };
            std::uniform_int_distribution<int> distr{ 1, 6 };

            while (running) {
                // sleep one second in steps of 100ms for faster exit when running goes false
                for (int slp = 1; slp < sleepSteps && running; slp++) {
                    std::this_thread::sleep_for(sleepDur);
                }

                int die1 = distr(eng);
                int die2 = distr(eng);

                std::cout << "\t" << die1 << " " << die2 << "    (" << (die1 + die2) << ")" << std::endl;
            }
        }
    );

#pragma warning(suppress: 6031)
    _getch();

    std::cout << "Stopping\n";
    running = false;
    runner.wait();

    std::cout << "Stopped  " << std::endl;
}
