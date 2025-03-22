#pragma once
#include <stdint.h>

namespace util_bsp
{
    namespace sys
    {
        class System
        {
        public:

            System() = delete;
            ~System() = delete;

            class IRQHandler
            {
            public:
                IRQHandler() = delete;
                ~IRQHandler() = delete;

                /**
                 * This function should be caled from SysTick interrupt handler.
                 */
                static void OnSysTick();
            };

            /**
             * Configure system clocks for ALL the busses.
             * + true if successfull
             */
            static bool ConfigureSyctemClock() __attribute__((weak));

            /**
             * Configure systick timer for specific frequency
             * + true if successfull
             */
            static bool ConfigureSystick(uint32_t freq_hz);

            /**
             * Get current system frequency
             * + frequency value
             */
            static uint32_t GetSystemFrequency();
            
            /**
             * Get systick value. See ConfigureSystick to configure the frequency of systick timer
             * + ticks count
             */
            static uint32_t GetTicks();
            

        private:
            static inline uint32_t SysFrequency = 8000000;

        };

    }

} // namespace util_bsp
