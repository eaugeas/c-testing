add_library(testing STATIC prints.c runner.c)
target_link_libraries(testing flags)

c_verify_clang_format(testing)
c_verify_clang_tidy(testing)
