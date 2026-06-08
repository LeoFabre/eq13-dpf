cmake_minimum_required(VERSION 3.22)
project(EQ13 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(dpf)

dpf_add_plugin(EQ13
    TARGETS vst3 lv2
    FILES_DSP plugin/Eq13Plugin.cpp)

target_compile_definitions(EQ13 PUBLIC DISTRHO_PLUGIN_HAS_UI=0)

target_include_directories(EQ13 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/plugin
    ${CMAKE_CURRENT_SOURCE_DIR}/dsp)
