CC      = g++
RM      = del
CFLAGS  = 
LDFLAGS = -Wextra -Wall -std=c++11

all: false clean

false: interactiveshell.cpp
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean cleanest

clean:
	$(RM) test.exe

run: all
	.\false

ResetFile:
	@echo Test 
	
BaseTypeTest: tests\BaseTypeTest.cpp
	$(CC) -o test $^ $(LDFLAGS)
	@echo TEST_BaseTypeTest 
	@.\test 
	

VirtualMachineTest: tests\VirtualMachineTest.cpp
	$(CC) -o test $^ $(LDFLAGS)
	@echo TEST_VirtualMachineTest 
	@.\test 
	
test: ResetFile BaseTypeTest VirtualMachineTest
	
	
cleanest: clean
	$(RM) false.exe