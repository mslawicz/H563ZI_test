cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME H563ZI_test)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# HAL library sources
set(HAL_SRC
	Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_cortex.c
	Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_icache.c
	Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_rcc.c
	Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_rcc_ex.c
	Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_flash.c
	Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_flash_ex.c
	Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_gpio.c
	Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_dma.c
	Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_dma_ex.c
	Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_pwr.c
	Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_pwr_ex.c
	Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal.c
	Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_exti.c
	Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_tim.c
	Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_tim_ex.c
	Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_usart.c
	Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_usart_ex.c
	Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_uart_ex.c
	Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_uart.c
)

set_source_files_properties(${HAL_SRC} PROPERTIES COMPILE_FLAGS -Wno-unused-parameter)

# project source files
file(GLOB PROJECT_SOURCE_FILES CONFIGURE_DEPENDS Core/Src/*.c)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
	Drivers/BSP/STM32H5xx_Nucleo/stm32h5xx_nucleo.c
	${HAL_SRC}
	Middlewares/Third_Party/FreeRTOS/Source/croutine.c
	Middlewares/Third_Party/FreeRTOS/Source/event_groups.c
	Middlewares/Third_Party/FreeRTOS/Source/list.c
	Middlewares/Third_Party/FreeRTOS/Source/queue.c
	Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c
	Middlewares/Third_Party/FreeRTOS/Source/tasks.c
	Middlewares/Third_Party/FreeRTOS/Source/timers.c
	Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/port.c
	Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/portasm.c
	Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c
	Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
	Core/Inc
	Drivers/STM32H5xx_HAL_Driver/Inc
	Drivers/STM32H5xx_HAL_Driver/Inc/Legacy
	Drivers/BSP/STM32H5xx_Nucleo
	Drivers/CMSIS/Device/ST/STM32H5xx/Include
	Drivers/CMSIS/Include
	Middlewares/Third_Party/FreeRTOS/Source/include/
	Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/
	Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/
	Middlewares/Third_Party/CMSIS/RTOS2/Include/
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
	USE_HAL_DRIVER
	STM32H563xx
	STM32_THREAD_SAFE_STRATEGY=2
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)
