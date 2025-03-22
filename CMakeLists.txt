cmake_minimum_required(VERSION 3.20)

####################### CONSTANTS ######################################
set (MFPU_FPV4_SP_D16                 "-mfpu=fpv4-sp-d16")
set (MFPU_FPV5_D16                    "-mfpu=fpv5-d16")
set (MFLOAT_ABI_SOFTWARE              "-mfloat-abi=soft")
set (MFLOAT_ABI_HARDWARE              "-mfloat-abi=hard")
set (MFLOAT_ABI_MIX                   "-mfloat-abi=softfp")
set (CMAKE_CXX_STANDARD					20)
set (CMAKE_CXX_STANDARD_REQUIRED		ON)
set (CMAKE_CXX_EXTENSIONS				OFF)

###################### VARIABLES ######################################
set (PROJECT_NAME             "cdc_sample")
set (LINKER_SCRIPT            "${CMAKE_SOURCE_DIR}/STM32F103C8TX_FLASH.ld")
set (MCPU                     "-mcpu=Cortex-M3")



set(LIB_CMSIS_F1XX_INC
	lib/CMSIS/Device/ST/STM32F1xx/Include
	lib/CMSIS/Include
)

set(LIB_HAL_LL_INC
	${LIB_CMSIS_F1XX_INC}
	lib/STM32F1xx_HAL_Driver/Inc
)

set(LIB_HAL_LL_SRC 
	lib/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
	lib/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c
	lib/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c
	lib/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c
	lib/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c
	lib/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c
	lib/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
	lib/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pcd_ex.c
	lib/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pcd.c
	lib/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c
	lib/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c
	lib/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
	lib/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
	lib/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_exti.c
	lib/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_gpio.c
	lib/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_rcc.c
	lib/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_usb.c
	lib/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_utils.c
)


set(LIB_TINYUSB_INC
	lib/tinyusb/src
	lib/tinyusb/hw/bsp
	lib/tinyusb/hw
	lib/tinyusb/src/class/audio
	lib/tinyusb/src/class/bth
	lib/tinyusb/src/class/cdc
	lib/tinyusb/src/class/dfu
	lib/tinyusb/src/class/hid
	lib/tinyusb/src/class/midi
	lib/tinyusb/src/class/msc
	lib/lib/tinyusb/src/class/net
	lib/tinyusb/src/class/usbtmc
	lib/tinyusb/src/class/vendor
	lib/tinyusb/src/class/video
	lib/tinyusb/src/common
	lib/tinyusb/src/device
	lib/tinyusb/src/typec
	lib/tinyusb/src/portable/st/stm32_fsdev
)

set(LIB_TINYUSB_SRC
	lib/tinyusb/src/tusb.c
	lib/tinyusb/src/class/audio/audio_device.c
	lib/tinyusb/src/class/bth/bth_device.c
	lib/tinyusb/src/class/cdc/cdc_device.c
	lib/tinyusb/src/class/cdc/cdc_host.c
	lib/tinyusb/src/class/cdc/cdc_rndis_host.c
	lib/tinyusb/src/class/dfu/dfu_device.c
	lib/tinyusb/src/class/dfu/dfu_rt_device.c
	lib/tinyusb/src/class/hid/hid_device.c
	lib/tinyusb/src/class/hid/hid_host.c
	lib/tinyusb/src/class/midi/midi_device.c
	lib/tinyusb/src/class/msc/msc_device.c
	lib/tinyusb/src/class/msc/msc_host.c
	lib/tinyusb/src/class/net/ecm_rndis_device.c
	lib/tinyusb/src/class/net/ncm_device.c
	lib/tinyusb/src/class/usbtmc/usbtmc_device.c
	lib/tinyusb/src/class/vendor/vendor_device.c
	lib/tinyusb/src/class/video/video_device.c
	lib/tinyusb/src/common/tusb_fifo.c
	lib/tinyusb/src/device/usbd_control.c
	lib/tinyusb/src/device/usbd.c
	lib/tinyusb/src/typec/usbc.c
	lib/tinyusb/src/portable/st/stm32_fsdev/dcd_stm32_fsdev.c
)


set (PROJECT_SOURCES
	src/bsp/startup_stm32f103c8tx.s
	src/bsp/usb/usb.cpp
	src/bsp/usb/tinyusb_application.cpp
	src/bsp/system/system.cpp
	src/bsp/system/irq.cpp
	src/bsp/stub.c
	src/bsp/system_stm32f1xx.c
	src/main.cpp
	#src/main_test.cpp
	
)

set (DEFS_COMMON
	STM32F103xB
)

set (PROJECT_INCLUDES
	src
	src/bsp
	src/bsp/usb
	src/bsp/system
	src/bsp/gpio
)

################## PROJECT SETUP ######################################
project(${PROJECT_NAME})
enable_language(CXX ASM C)

set (COMPILE_DEFS_STM32F1
	-mcpu=Cortex-M3
	-mthumb
	-fdata-sections
	-ffunction-sections
	-fno-exceptions
	-Wall
	-Os
	-g3
)

set (LINK_DEFS_STM32F1
	-T${LINKER_SCRIPT}
	-mcpu=Cortex-M3
	-mthumb
	--specs=nano.specs
	--specs=nosys.specs
    -lnosys
    -lstdc++
	-Wl,-Map=test.map
)

add_library(${PROJECT_NAME}_hal ${LIB_HAL_LL_SRC})
target_include_directories(${PROJECT_NAME}_hal PRIVATE ${LIB_HAL_LL_INC} ${PROJECT_INCLUDES})
target_compile_options(${PROJECT_NAME}_hal PRIVATE
	${COMPILE_DEFS_STM32F1}
)

add_library(${PROJECT_NAME}_tinyusb ${LIB_TINYUSB_SRC})
target_include_directories(${PROJECT_NAME}_tinyusb PRIVATE ${LIB_TINYUSB_INC} ${PROJECT_INCLUDES} ${LIB_HAL_LL_INC})
target_compile_options(${PROJECT_NAME}_tinyusb PRIVATE
	${COMPILE_DEFS_STM32F1}
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_compile_options(${PROJECT_NAME} PRIVATE
	${COMPILE_DEFS_STM32F1}
)
target_link_options(${PROJECT_NAME} PRIVATE
	${LINK_DEFS_STM32F1}
)
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>)
target_include_directories(${PROJECT_NAME} PRIVATE ${LIB_TINYUSB_INC} ${LIB_HAL_LL_INC} ${PROJECT_INCLUDES})

target_link_libraries(${PROJECT_NAME} PRIVATE
	${PROJECT_NAME}_tinyusb
	${PROJECT_NAME}_hal
)

add_compile_definitions (${DEFS_COMMON})

set (CMAKE_EXECUTABLE_SUFFIX ".elf")
set (CMAKE_STATIC_LIBRARY_SUFFIX ".a")