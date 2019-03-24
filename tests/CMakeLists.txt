function(new_test name)
  add_executable(${name} ${name}.cpp)
  target_link_libraries(${name} VMInterface VMSimple Commands BaseTypes)
  add_test(${name} ${name})
endfunction()


new_test(BaseTypeTest)
new_test(ControlFlowTest)
new_test(StackModifierOperationTest)
new_test(ArithmeticOperationTest)
new_test(LogicalOperationTest)
new_test(VariablesSubroutines)

