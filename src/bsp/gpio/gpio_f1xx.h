#pragma once

#include "gpio_interface.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_exti.h"

namespace util_bsp
{
    class Gpio : public Gpio_Interface<Gpio>
    {
    public:

        static const uint32_t      PinCount = 16;

        Gpio(
            GPIO_TypeDef *GPIOx,
            uint32_t pin) : GPIOx(GPIOx), pin(pin)
        {
            if (GPIOx == GPIOA)
            {
                LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
            }
            else if (GPIOx == GPIOB)
            {
                LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
            }
            else if (GPIOx == GPIOC)
            {
                LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
            }
            else if (GPIOx == GPIOD)
            {
                LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOD);
            }
            else if (GPIOx == GPIOE)
            {
                LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOE);
            }
        }

        Gpio_Interface &SetPinPull(
            uint32_t mode)
        {
            const uint32_t pin_mask = GetPinMask();
            LL_GPIO_SetPinPull(this->GPIOx, pin_mask, mode);
            return *this;
        }

        Gpio_Interface &SetPinMode(
            uint32_t mode)
        {
            const uint32_t pin_mask = GetPinMask();
            LL_GPIO_SetPinMode(this->GPIOx, pin_mask, mode);
            return *this;
        }

        Gpio_Interface &SetOutputType(
            uint32_t mode)
        {
            const uint32_t pin_mask = GetPinMask();
            LL_GPIO_SetPinOutputType(this->GPIOx, pin_mask, mode);
            return *this;
        }

        Gpio_Interface &Set()
        {
            const uint32_t pin_mask = GetPinMask();
            LL_GPIO_SetOutputPin(this->GPIOx, pin_mask);
            return *this;
        }

        Gpio_Interface &Reset()
        {
            const uint32_t pin_mask = GetPinMask();
            LL_GPIO_ResetOutputPin(this->GPIOx, pin_mask);
            return *this;
        }

        Gpio_Interface &Toggle()
        {
            const uint32_t pin_mask = GetPinMask();
            LL_GPIO_TogglePin(this->GPIOx, pin_mask);
            return *this;
        }

        bool GetState()
        {
            return (LL_GPIO_ReadInputPort(this->GPIOx) >> this->pin) & 1;
        }

        Gpio_Interface &ConfigureIRQ(
            IrqType                 type,
            Callback_OnTrigger      cb
        )
        {
            if (cb == nullptr) return *this;

            return *this;
        }

        Gpio_Interface &SetSpeed(
            uint32_t speed
        )
        {
            const uint32_t pin_mask = GetPinMask();
            LL_GPIO_SetPinSpeed(GPIOx, pin_mask, speed);

            return *this;
        }

        static void RemapCan1()
        {
            EnableAFIO();
            LL_GPIO_AF_RemapPartial2_CAN1();
        }

        static void RemapUsart1()
        {
            EnableAFIO();
            LL_GPIO_AF_EnableRemap_USART1();
        }

        static Callback_OnTrigger  Callbacks[PinCount];

    private:

        static inline void EnableAFIO()
        {
            LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_AFIO);
        }

        inline uint32_t GetPinMask() const
        {
            switch (this->pin)
            {
                case 0:
                    return LL_GPIO_PIN_0;
                break;

                case 1:
                    return LL_GPIO_PIN_1;
                break;

                case 2:
                    return LL_GPIO_PIN_2;
                break;

                case 3:
                    return LL_GPIO_PIN_3;
                break;

                case 4:
                    return LL_GPIO_PIN_4;
                break;

                case 5:
                    return LL_GPIO_PIN_5;
                break;

                case 6:
                    return LL_GPIO_PIN_6;
                break;

                case 7:
                    return LL_GPIO_PIN_7;
                break;

                case 8:
                    return LL_GPIO_PIN_8;
                break;

                case 9:
                    return LL_GPIO_PIN_9;
                break;

                case 10:
                    return LL_GPIO_PIN_10;
                break;

                case 11:
                    return LL_GPIO_PIN_11;
                break;

                case 12:
                    return LL_GPIO_PIN_12;
                break;

                case 13:
                    return LL_GPIO_PIN_13;
                break;

                case 14:
                    return LL_GPIO_PIN_14;
                break;

                case 15:
                    return LL_GPIO_PIN_15;
                break;
            }

            return LL_GPIO_PIN_0;
        }

        GPIO_TypeDef        *GPIOx;
        uint32_t            pin;
    };

}