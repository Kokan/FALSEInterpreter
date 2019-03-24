function(new_test name)
  add_executable(${name} ${name}.cpp)
  target_link_libraries(${name} VMInterface VMSimple Commands BaseTypes)
  add_test(${name} ${name})

  add_custom_command(TARGET ${name}
                     POST_BUILD
                     COMMAND ${name}
                     WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                     COMMENT "Running ${name}" VERBATIM)
endfunction()

enable_testing()

new_test(BaseTypeTest)
new_test(ControlFlowTest)
new_test(StackModifierOperationTest)
new_test(ArithmeticOperationTest)
new_test(LogicalOperationTest)
new_test(VariablesSubroutines)

