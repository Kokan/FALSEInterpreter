CC      = g++
RM      = del /Q
CFLAGS  = -Wextra -Wall -std=c++11 -O3
LDFLAGS = -Wextra -Wall -std=c++11 -O3
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

all: | false clean

# pull in dependency info for *existing* .o files
-include $(OBJS:.o=.d)

# compile and generate dependency info
%.o: makefile %.cpp
	@echo Compile $*
	@$(CC) -c  $(CFLAGS) $*.cpp -o $*.o
	@$(CC) -MM $(CFLAGS) $*.cpp > $*.d

false: $(OBJS) interactiveshell.o
	@$(CC) -o $@ $^ $(LDFLAGS) 

.PHONY: clean cleanest

clean:
	@$(RM) test*.exe
	@$(RM) BaseTypes\*.o
	@$(RM) BaseTypes\*.d
	@$(RM) Commands\*.o
	@$(RM) Commands\*.d
	@$(RM) Tests\*.o
	@$(RM) Tests\*.d
	@$(RM) *.o
	@$(RM) *.d

run: all
	.\false
	
test: BaseTypeTest ControlFlowTest \
      StackModifierOperationTest ArithmeticOperationTest \
	  LogicalOperationTest VariablesSubroutines
	@$(RM) test*.exe
	
BaseTypeTest: $(OBJS) Tests\BaseTypeTest.cpp
	@$(CC) -o test001 $^ $(LDFLAGS)
	@echo =========================================================
	@echo = TEST_BaseTypeTest 
	@echo =========================================================
	@.\test001 
	

ControlFlowTest: $(OBJS) Tests\ControlFlowTest.cpp
	@$(CC) -o test002 $^ $(LDFLAGS)
	@echo =========================================================
	@echo = TEST_ControlFlowTest 
	@echo =========================================================
	@.\test002 

StackModifierOperationTest: $(OBJS) Tests\StackModifierOperationTest.cpp
	@$(CC) -o test003 $^ $(LDFLAGS)
	@echo =========================================================
	@echo = TEST_StackModifierOperationTest
	@echo =========================================================
	@.\test003 

ArithmeticOperationTest: $(OBJS) Tests\ArithmeticOperationTest.cpp
	@$(CC) -o test004 $^ $(LDFLAGS)
	@echo =========================================================
	@echo = TEST_ArithmeticOperationTest
	@echo =========================================================
	@.\test004 

LogicalOperationTest: $(OBJS) Tests\LogicalOperationTest.cpp
	@$(CC) -o test004 $^ $(LDFLAGS)
	@echo =========================================================
	@echo = TEST_LogicalOperationTest
	@echo =========================================================
	@.\test004 

VariablesSubroutines: $(OBJS) Tests\VariablesSubroutines.cpp
	@$(CC) -o test005 $^ $(LDFLAGS)
	@echo =========================================================
	@echo = TEST_VariablesSubroutines
	@echo =========================================================
	@.\test005 
	
	
cleanest: clean
	@$(RM) false.exe