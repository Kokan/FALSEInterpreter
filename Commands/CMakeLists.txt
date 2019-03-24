
set(SOURCE
    Command.cpp 
    DeleteCommand.cpp
    DuplicateCommand.cpp
    EqualCommand.cpp
    GetVariableCommand.cpp
    IFCommand.cpp
    LogicalNotCommand.cpp
    NegationCommand.cpp
    PrintAsCharCommand.cpp
    PrintAsIntegerCommand.cpp
    PushCommand.cpp
    ReadIntegerCommand.cpp
    RunSubroutineCommand.cpp
    SetVariableCommand.cpp
    StringCommand.cpp
    SubroutineCommand.cpp
    SwapItemCommand.cpp
    ThirdToTopCommand.cpp
    WhileCommand.cpp
)


add_library(Commands SHARED ${SOURCE})

