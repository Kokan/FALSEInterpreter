cmake_minimum_required(VERSION 2.6)

project(FALSEInterpreter)

set(CMAKE_CXX_STANDARD 11)

add_library(VMInterface SHARED VirtualMachine.cpp MemoryInterface.cpp)
add_library(VMSimple    SHARED SimpleStack.cpp SimpleMemory.cpp)

add_subdirectory(Commands)
add_subdirectory(BaseTypes)
add_subdirectory(tests)

add_executable(false Commands BaseTypes
    interactiveshell.cpp
)
target_link_libraries(false Commands BaseTypes VMInterface VMSimple)

