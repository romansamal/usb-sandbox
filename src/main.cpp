#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "bsp/board_api.h"
#include "tusb.h"
#include "usb.h"
#include "system.h"
#include "gpio_f1xx.h"

static void cdc_task(
    util_bsp::usb::Cdc &usb);

int main(void)
{
    util_bsp::sys::System::ConfigureSyctemClock();
    util_bsp::sys::System::ConfigureSystick(1000);

    util_bsp::usb::Cdc usb(TUSB_ROLE_DEVICE, TUSB_SPEED_FULL);
    usb.Initialize();

    util_bsp::Gpio led(GPIOC, 13);

    led.SetPinMode(LL_GPIO_MODE_OUTPUT).Reset();

    uint32_t switch_t = 100;
    while (1)
    {
        if (util_bsp::sys::System::GetTicks() > switch_t)
        {
            led.Toggle();
            switch_t += usb.IsConnected() ? 50 : 500;
        }
        tud_task();
        cdc_task(usb);
    }
}

static void cdc_task(
    util_bsp::usb::Cdc &usb)
{
    std::array<uint8_t, 64> buf;
    buf.fill(0xAA);

    usb.Send(buf);

    usb.Receive(buf);
}

