//
// RollingDice.cpp -- Application main file
//

#include <iostream>
#include <future>
#include <random>
#include <chrono>
#include <thread>

#include <conio.h>

#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <winmeta.h>
#include <TraceLoggingProvider.h>

TRACELOGGING_DECLARE_PROVIDER(g_traceloggingProvider);

// https://docs.microsoft.com/en-us/windows/win32/api/traceloggingprovider/nf-traceloggingprovider-tracelogging_define_provider
// [System.Diagnostics.Tracing.EventSource]::new("RollingDice").Guid
TRACELOGGING_DEFINE_PROVIDER(g_traceloggingProvider,
    "RollingDice",
    (0x0d6910e0, 0xb0fe, 0x5ee8, 0x00, 0xe3, 0xc6, 0xbb, 0x1c, 0x97, 0x9a, 0x53));

int main()
{
    std::cout << "Rolling Dice (2x W6)\n"
        << "Press any key to exit\n";

    TraceLoggingRegister(g_traceloggingProvider);

    std::atomic<bool> running{ true };
    auto runner = std::async(
        std::launch::async,
        [&running]() -> void {
            constexpr const int sleepSteps = 10;
            constexpr const std::chrono::milliseconds sleepDur{ 1000 / sleepSteps };

            std::default_random_engine eng{ static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()) };
            std::uniform_int_distribution<int> distr{ 1, 6 };

            while (running) {
                // sleep one second in steps of 100ms for faster exit when running goes false
                for (int slp = 1; slp < sleepSteps && running; slp++) {
                    std::this_thread::sleep_for(sleepDur);
                }

                int die1 = distr(eng);
                int die2 = distr(eng);

                int sum = die1 + die2;

                std::cout << "\t" << die1 << " " << die2 << "    (" << sum << ")" << std::endl;

                TraceLoggingWrite(g_traceloggingProvider,
                    "Rolling Dice",
                    TraceLoggingDescription("Rolled 2x W6 dice"),
                    TraceLoggingInt32(die1, "Die1", "First die"),
                    TraceLoggingInt32(die2, "Die2", "Second die"),
                    TraceLoggingInt32(sum, "Dice", "Summary value of dice")
                );

            }
        }
    );

#pragma warning(suppress: 6031)
    _getch();

    std::cout << "Stopping\n";
    running = false;
    runner.wait();

    std::cout << "Stopped  " << std::endl;

    TraceLoggingUnregister(g_traceloggingProvider);
}
