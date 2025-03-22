#pragma once

namespace util_bsp
{
    /**
     * @brief Provides a generic interface for GPIO operations, allowing for flexible implementation based on specific hardware platforms.
    This class employs the Curiously Recurring Template Pattern (CRTP) to enable static polymorphism and early binding of virtual function calls. This allows for efficient and type-safe dispatching of methods to the concrete derived class.
    @tparam Implementation The derived class that inherits from `Gpio_Interface`. This allows for polymorphic behavior, where the specific implementation of methods is determined at compile time based on the actual object type.
    */
    template <typename Implementation>
    class Gpio_Interface
    {

    public:

        enum class IrqType : uint32_t
        {
            Rising                  = 0,
            Falling                 = 1,
            Rising_Falling          = 2
        };

        using Callback_OnTrigger = void (*)();

        Gpio_Interface() {}
        ~Gpio_Interface() {}

        /**
        * @brief Sets the pull-up/pull-down mode for the GPIO pin.
        The specific behavior and supported modes may vary depending on the underlying hardware implementation.
        @param mode The desired pull mode, typically defined as an enum or bitmask.
        @return A reference to the current object, allowing for method chaining.
        */
        Gpio_Interface &SetPinPull(
            uint32_t mode)
        {
            static_cast<Implementation *>(this)->SetPinPull(mode);
            return *this;
        }

        /**
         * @brief Sets the input/output mode for the GPIO pin.
        The specific behavior and supported modes may vary depending on the underlying hardware implementation.
        @param mode The desired pin mode, typically defined as an enum or bitmask.
        @return A reference to the current object, allowing for method chaining.
        */
        Gpio_Interface &SetPinMode(
            uint32_t mode)
        {
            static_cast<Implementation *>(this)->SetPinMode(mode);
            return *this;
        }

        /**
         * @brief Sets the output type for the GPIO pin (e.g., push-pull, open-drain).
        The specific behavior and supported modes may vary depending on the underlying hardware implementation.
        @param mode The desired output type, typically defined as an enum or bitmask.
        @return A reference to the current object, allowing for method chaining.
        */
        Gpio_Interface &SetOutputType(
            uint32_t mode)
        {
            return static_cast<Implementation *>(this)->SetOutputType(mode);
        }

        /**
        * @brief Sets the GPIO pin to the high state.
        The specific behavior may vary depending on the underlying hardware implementation.
        @return A reference to the current object, allowing for method chaining.
        */
        Gpio_Interface &Set()
        {
            return static_cast<Implementation *>(this)->Set();
        }

        /**
        * @brief Sets the GPIO pin to the low state.
        The specific behavior may vary depending on the underlying hardware implementation.
        @return A reference to the current object, allowing for method chaining.
        */
        Gpio_Interface &Reset()
        {
            return static_cast<Implementation *>(this)->Reset();
        }

        /**
         * @brief Toggles the state of the GPIO pin.
        The specific behavior may vary depending on the underlying hardware implementation.
        @return A reference to the current object, allowing for method chaining.
        */
        Gpio_Interface &Toggle()
        {
            return static_cast<Implementation *>(this)->Toggle();
        }

        /**
        * @brief Reads the current state of the GPIO pin.
        The specific behavior may vary depending on the underlying hardware implementation.
        @return The current state of the GPIO pin (true for high, false for low).
        */
        bool GetState()
        {
            return static_cast<Implementation *>(this)->GetState();
        }

        /**
        * @brief Configure IRQ on pin level change.
        The specific behavior may vary depending on the underlying hardware implementation.
        @return A reference to the current object, allowing for method chaining.
        */
        Gpio_Interface &ConfigureIRQ(
            IrqType type,
            Callback_OnTrigger      cb
        )
        {
            return static_cast<Implementation *>(this)->ConfigureIRQ(type, cb);
        }

        /**
        * @brief Configure pin as alternative function
        The specific behavior may vary depending on the underlying hardware implementation.
        @return A reference to the current object, allowing for method chaining.
        */
        Gpio_Interface &ConfigureAlternativeFunction(
            uint32_t function_num
        )
        {
            return static_cast<Implementation *>(this)->ConfigureAlternativeFunction(function_num);
        }

        /**
        * @brief Configure pin speed
        The specific behavior may vary depending on the underlying hardware implementation.
        @return A reference to the current object, allowing for method chaining.
        */
        Gpio_Interface &SetSpeed(
            uint32_t speed
        )
        {
            return static_cast<Implementation *>(this)->SetSpeed(speed);
        }
    private:
        /* data */
    };

}