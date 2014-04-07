CC      = g++
RM      = del
CFLAGS  = -Wextra -Wall -std=c++11
LDFLAGS = -Wextra -Wall -std=c++11
OBJS := SimpleStack.o MemoryInterface.o SimpleMemory.o \
		Commands\Command.o Commands\DeleteCommand.o \
		Commands\DuplicateCommand.o Commands\EqualCommand.o \
		Commands\GetVariableCommand.o Commands\IFCOmmand.o \
		Commands\LogicalNotCommand.o Commands\NegationCommand.o \
		Commands\PrintAsCharCommand.o Commands\PrintAsIntegerCommand.o \
		Commands\PushCommand.o Commands\ReadIntegerCommand.o \
		Commands\RunSubroutineCommand.o Commands\SetVariableCommand.o \
		Commands\StringCommand.o Commands\SubroutineCommand.o \
		Commands\SwapItemCommand.o Commands\ThirdToTopCommand.o \
		Commands\WhileCommand.o \
		VirtualMachine.o BaseTypes\Object.o

all: false clean

# pull in dependency info for *existing* .o files
-include $(OBJS:.o=.d)

# compile and generate dependency info
%.o: %.cpp
	@echo Compile $*
	@$(CC) -c $(CFLAGS) $*.cpp -o $*.o
	@$(CC) -MM $(CFLAGS) $*.cpp > $*.d

false: $(OBJS) interactiveshell.o
	@$(CC) -o $@ $^ $(LDFLAGS) 

.PHONY: clean cleanest

clean:
	@$(RM) /Q test.exe
	@$(RM) /Q BaseTypes\*.o
	@$(RM) /Q BaseTypes\*.d
	@$(RM) /Q Commands\*.o
	@$(RM) /Q Commands\*.d
	@$(RM) /Q Tests\*.o
	@$(RM) /Q Tests\*.d
	@$(RM) /Q *.o
	@$(RM) /Q *.d

run: all
	.\false
	
test: TESTS ResetFile BaseTypeTest ControlFlowTest \
      StackModifierOperationTest ArithmeticOperationTest \
	  LogicalOperationTest VariablesSubroutines

ResetFile:
	@echo Test 

TESTS: $(OBJS)
	
BaseTypeTest: Tests\BaseTypeTest.cpp
	@$(CC) -o test $^ $(LDFLAGS)
	@echo =========================================================
	@echo = TEST_BaseTypeTest 
	@echo =========================================================
	@.\test 
	

ControlFlowTest: Tests\ControlFlowTest.cpp
	@$(CC) -o test $^ $(LDFLAGS) $(OBJS)
	@echo =========================================================
	@echo = TEST_ControlFlowTest 
	@echo =========================================================
	@.\test 

StackModifierOperationTest: Tests\StackModifierOperationTest.cpp
	@$(CC) -o test $^ $(LDFLAGS) $(OBJS)
	@echo =========================================================
	@echo = TEST_StackModifierOperationTest
	@echo =========================================================
	@.\test 

ArithmeticOperationTest: Tests\ArithmeticOperationTest.cpp
	@$(CC) -o test $^ $(LDFLAGS) $(OBJS)
	@echo =========================================================
	@echo = TEST_ArithmeticOperationTest
	@echo =========================================================
	@.\test 

LogicalOperationTest: Tests\LogicalOperationTest.cpp
	@$(CC) -o test $^ $(LDFLAGS) $(OBJS)
	@echo =========================================================
	@echo = TEST_LogicalOperationTest
	@echo =========================================================
	@.\test 

VariablesSubroutines: Tests\VariablesSubroutines.cpp
	@$(CC) -o test $^ $(LDFLAGS) $(OBJS)
	@echo =========================================================
	@echo = TEST_VariablesSubroutines
	@echo =========================================================
	@.\test 
	
	
cleanest: clean
	@$(RM) /Q false.exe