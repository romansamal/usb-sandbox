#include "system.h"
#include "usb.h"

extern "C"
{
    void USB_HP_CAN1_TX_IRQHandler(void)
    {
        util_bsp::usb::Device::OnIrq();
    }

    void USB_LP_CAN1_RX0_IRQHandler(void)
    {
        util_bsp::usb::Device::OnIrq();
    }

    void USBWakeUp_IRQHandler(void)
    {
        util_bsp::usb::Device::OnIrq();
    }

    void SysTick_Handler(void)
    {
        util_bsp::sys::System::IRQHandler::OnSysTick();
    }

    void HardFault_Handler(void)
    {
        __asm("BKPT #0\n");
    }
}