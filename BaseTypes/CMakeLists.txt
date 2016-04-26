project(BaseTypes)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE
    Object.cpp
)

add_library(BaseTypes SHARED ${SOURCE})
    
