#include "usb.h"
#include "stm32f1xx_hal.h"

namespace util_bsp
{
    namespace usb
    {
        Device::Device(
            tusb_role_t role,
            tusb_speed_t speed
        ) : init_s(
            {
                role,
                speed
            }
        )
        {
            __HAL_RCC_USB_CLK_ENABLE();
        }

        Device::~Device()
        {
        }

        bool Device::Initialize()
        {
            tusb_init(BOARD_TUD_RHPORT, &init_s);
            return true;
        }

        void Device::OnIrq()
        {
            tud_int_handler(0);
        }

        bool Cdc::IsConnected() const
        {
            return tud_cdc_connected();
        }

        Cdc::Cdc(
            tusb_role_t role,
            tusb_speed_t speed
        ) : Device(role, speed)
        {

        }

        Cdc::~Cdc()
        {

        }

    }

}