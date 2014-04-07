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
	@echo =========================================================
	@echo = TEST_BaseTypeTest 
	@echo =========================================================
	@.\test 
	

VirtualMachineTest: tests\VirtualMachineTest.cpp
	$(CC) -o test $^ $(LDFLAGS)
	@echo =========================================================
	@echo = TEST_VirtualMachineTest 
	@echo =========================================================
	@.\test 

StackModifierOperationTest: tests\StackModifierOperationTest.cpp
	$(CC) -o test $^ $(LDFLAGS)
	@echo =========================================================
	@echo = TEST_StackModifierOperationTest
	@echo =========================================================
	@.\test 

ArithmeticOperationTest: tests\ArithmeticOperationTest.cpp
	$(CC) -o test $^ $(LDFLAGS)
	@echo =========================================================
	@echo = TEST_ArithmeticOperationTest
	@echo =========================================================
	@.\test 

LogicalOperationTest: tests\LogicalOperationTest.cpp
	$(CC) -o test $^ $(LDFLAGS)
	@echo =========================================================
	@echo = TEST_LogicalOperationTest
	@echo =========================================================
	@.\test 

VariablesSubroutines: tests\VariablesSubroutines.cpp
	$(CC) -o test $^ $(LDFLAGS)
	@echo =========================================================
	@echo = TEST_VariablesSubroutines
	@echo =========================================================
	@.\test 
	
test: ResetFile BaseTypeTest VirtualMachineTest StackModifierOperationTest ArithmeticOperationTest LogicalOperationTest VariablesSubroutines
	
	
cleanest: clean
	$(RM) false.exe