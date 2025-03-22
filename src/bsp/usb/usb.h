
#include <array>

extern "C"
{
    #include "tusb.h"
}

namespace util_bsp
{

    namespace usb
    {
        class Device
        {
        public:
        
            /**
             * Enable USB RCC Clock system
             * - role device/host role selection
             * - speed endpoint speed selection (low/full/high)
             */
            Device(
                tusb_role_t role,
                tusb_speed_t speed
            );

            ~Device();

            /**
             * Initialize internal middleware of USB
             * + true, if successful
             */
            bool Initialize();

            /**
             * This function should be called from USB IRQ to notify middleware, so middleware can process it
             */
            static void OnIrq();

        private:
            const tusb_rhport_init_t init_s;
        };

        class Cdc : public Device
        {
        public:
            Cdc(
                tusb_role_t role,
                tusb_speed_t speed
            );

            ~Cdc();

            /**
             * Is CDC device connected to host
             * true if so
             */
            bool IsConnected() const;

            /**
             * Transmit data to host (CDC Mode)
             * buf data to be sent
             */
            template <size_t Size>
            bool Send(
                std::array<uint8_t, Size> &buf
            )
            {
                if (!tud_cdc_connected()
                    || (tud_cdc_write_available() == 0)
                )
                {
                    return false;
                }

                tud_cdc_write(buf.data(), Size);
                
                tud_cdc_write_flush();

                return true;
            }

            /**
             * Read data from host (CDC Mode)
             * buf where data will be stored
             */
            template <size_t Size>
            bool Receive(
                std::array<uint8_t, Size> &buf
            )
            {
                if (!tud_cdc_available())
                {
                    return false;
                }

                tud_cdc_read(buf.data(), Size);

                return true;
            }
        };

    }

} // namespace util_bsp
