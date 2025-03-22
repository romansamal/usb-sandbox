# USB sandbox

## Description
Sandbox for testing TinyUSB stack on STM32F103.

## How to build

	cmake -B build -DCMAKE_TOOLCHAIN_FILE=toolchain-gcc.cmake
	cd build
	cmake --build .

