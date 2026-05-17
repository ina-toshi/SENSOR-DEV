# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(VL53L5CX C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(VL53L5CX main.c )

pico_set_program_name(VL53L5CX "VL53L5CX")
pico_set_program_version(VL53L5CX "0.1")

target_compile_definitions(VL53L5CX PRIVATE
        PICO_DEFAULT_UART=0
        PICO_DEFAULT_UART_TX_PIN=0
        PICO_DEFAULT_UART_RX_PIN=1
        PICO_DEFAULT_UART_BAUD_RATE=115200
)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(VL53L5CX 1)
pico_enable_stdio_usb(VL53L5CX 0)


target_sources(VL53L5CX PRIVATE
    main.c
    lib/vl53l5cx/vl53l5cx_api.c
    lib/vl53l5cx/platform.c
)
# Add the standard library to the build
target_link_libraries(VL53L5CX
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(VL53L5CX PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

target_include_directories(VL53L5CX PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/lib/vl53l5cx
)

# Add any user requested libraries
target_link_libraries(VL53L5CX 
        hardware_i2c)

pico_add_extra_outputs(VL53L5CX)
