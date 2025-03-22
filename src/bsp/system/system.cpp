#include "system.h"

#include "stm32f1xx_hal.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_cortex.h"
#include "stm32f1xx_ll_utils.h"

bool util_bsp::sys::System::ConfigureSyctemClock()
{
    // Desired user frequency
    uint32_t prev_sysclk_value = util_bsp::sys::System::SysFrequency;
    util_bsp::sys::System::SysFrequency = 72000000;

    bool is_success = true;
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
    while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_2)
    {
        __asm("nop");
    }
    LL_RCC_HSE_Enable();

    /* Wait till HSE is ready */
    while(LL_RCC_HSE_IsReady() != 1)
    {
        __asm("nop");
    }
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE_DIV_1, LL_RCC_PLL_MUL_9);
    LL_RCC_PLL_Enable();

    /* Wait till PLL is ready */
    while(LL_RCC_PLL_IsReady() != 1)
    {
        __asm("nop");
    }
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

    /* Wait till System clock is ready */
    while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
    {
        __asm("nop");
    }

    LL_SetSystemCoreClock(SysFrequency);

    /* Update the time base */
    if (HAL_InitTick (TICK_INT_PRIORITY) != HAL_OK)
    {
        is_success = false;
    }
    LL_RCC_SetUSBClockSource(LL_RCC_USB_CLKSOURCE_PLL_DIV_1_5);

    if (is_success == false)
    {
        util_bsp::sys::System::SysFrequency = prev_sysclk_value;
    }

    return is_success;
}

bool util_bsp::sys::System::ConfigureSystick(uint32_t freq_hz)
{
    return (SysTick_Config(util_bsp::sys::System::SysFrequency / freq_hz) == 0);
}

uint32_t util_bsp::sys::System::GetSystemFrequency()
{
    return util_bsp::sys::System::SysFrequency;
}

uint32_t util_bsp::sys::System::GetTicks()
{
    return HAL_GetTick();
}

void util_bsp::sys::System::IRQHandler::OnSysTick()
{
    HAL_IncTick();
}