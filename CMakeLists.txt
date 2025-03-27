# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.10)

project ("op")

if(NOT $ENV{BLACKBONE_ROOT} STREQUAL "")
    set(blackbone_include_path "$ENV{BLACKBONE_ROOT}/src")

    set(blackbone_lib32_dbg_path "$ENV{BLACKBONE_ROOT}/build/Win32/Debug")
    set(blackbone_lib64_dbg_path "$ENV{BLACKBONE_ROOT}/build/X64/Debug")

    set(blackbone_lib32_rel_path "$ENV{BLACKBONE_ROOT}/build/Win32/Release")
    set(blackbone_lib64_rel_path "$ENV{BLACKBONE_ROOT}/build/X64/Release")
endif()

option(build_swig_py "build swig py,requrie python" ON)

# 检查头文件是否设置正确
if(EXISTS ${blackbone_include_path}/BlackBone/Process/Process.h)
    message(STATUS "${blackbone_include_path}/BlackBone/Process/Process.h finded" )
else()
    message(FATAL_ERROR "${blackbone_include_path}/BlackBone/Process/Process.h not finded" )
endif()

# 检查库是否设置正确

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
if(EXISTS ${blackbone_lib32_dbg_path}/BlackBone.lib)
    message(STATUS "32 Debug blackbone lib find" )
else()
message(FATAL_ERROR "${blackbone_lib32_dbg_path}/BlackBone.lib NOT find" )
endif()
if(EXISTS ${blackbone_lib64_dbg_path}/BlackBone.lib)
    message(STATUS "64 Debug BlackBone lib find" )
else()
message(FATAL_ERROR "${blackbone_lib64_dbg_path}/blackbone.lib NOT find" )
endif()
else()
if(EXISTS ${blackbone_lib32_rel_path}/BlackBone.lib)
    message(STATUS "32 Release blackbone lib find" )
else()
message(FATAL_ERROR "${blackbone_lib32_rel_path}/BlackBone.lib NOT find" )
endif()
if(EXISTS ${blackbone_lib64_rel_path}/BlackBone.lib)
    message(STATUS "64 Release BlackBone lib find" )
else()
message(FATAL_ERROR "${blackbone_lib64_rel_path}/blackbone.lib NOT find" )
endif()
endif()

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

set(CMAKE_CXX_STANDARD 17)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    MESSAGE(STATUS "----------------Now is MSVC EHA----------------")
    set(CMAKE_CXX_FLAGS_RELEASE "/MT /O2 /EHa")
    set(CMAKE_C_FLAGS_RELEASE   "/MT /O2 /EHa")
    set(CMAKE_CXX_FLAGS_DEBUG   "/MTd /Zi /EHa")
    set(CMAKE_C_FLAGS_DEBUG     "/MTd /Zi /EHa")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "/MT /O2 /EHa")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO    "/MT /O2 /EHa")
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    link_directories(
        ${CMAKE_SOURCE_DIR}/3rd_party/lib/x64
        ${blackbone_lib64_dbg_path}
    )
    set(op_com op_x64)
	MESSAGE(STATUS "----------------Platform x64 Debug----------------")
else()
    link_directories(
        ${CMAKE_SOURCE_DIR}/3rd_party/lib/x64
        ${blackbone_lib64_rel_path}
    )
    set(op_com op_x64)
	MESSAGE(STATUS "----------------Platform x64 Release----------------")
endif()
else()
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    link_directories(
        ${CMAKE_SOURCE_DIR}/3rd_party/lib/x86
        ${blackbone_lib32_dbg_path}
        )
    set(op_com op_x86)
	MESSAGE(STATUS "----------------Platform x86 Debug----------------")
else()
    link_directories(
        ${CMAKE_SOURCE_DIR}/3rd_party/lib/x86
        ${blackbone_lib32_path}
        )
    set(op_com op_x86)
	MESSAGE(STATUS "----------------Platform x86 Release----------------")
endif()
endif()

include_directories( 
  ./
  ${CMAKE_SOURCE_DIR}/3rd_party/include/
  ${CMAKE_SOURCE_DIR}/3rd_party/include/3rd_party
  ${blackbone_include_path}
  ${blackbone_include_path}/3rd_party
) 

# 包含子项目。
## libop主项目
add_subdirectory ("libop")
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/libop/com/op_i.h")
    ## tools项目
    add_subdirectory("tools")
    ## 测试项目
    add_subdirectory("tests")
endif()
## swig 项目
if(build_swig_py)
    add_subdirectory("swig")
endif()


