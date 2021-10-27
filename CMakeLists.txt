cmake_minimum_required(VERSION 3.0)

project(FALSEInterpreter CXX)

set(CMAKE_CXX_STANDARD 17)
enable_testing()

add_library(VMInterface SHARED VirtualMachine.cpp MemoryInterface.cpp)
add_library(VMSimple    SHARED SimpleStack.cpp SimpleMemory.cpp)

add_subdirectory(Commands)
add_subdirectory(BaseTypes)
add_subdirectory(tests)

add_executable(false interactiveshell.cpp)
target_link_libraries(false Commands BaseTypes VMInterface VMSimple)

