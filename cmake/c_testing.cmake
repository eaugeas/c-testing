macro(c_testing_add_test test lib)
  add_executable(${test} ${test}.c)
  target_include_directories(${test}
    PRIVATE ${CMAKE_SOURCE_DIR}/source)
  target_link_libraries(${test} ${lib} testing)
  add_test(${lib}_${test} ${test})
endmacro()
