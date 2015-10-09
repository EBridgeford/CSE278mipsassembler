set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -g")
file(GLOB SRCS *.cpp *.h)
add_executable(mips_assembler ${SRCS})
install(TARGETS mips_assembler DESTINATION bin)
