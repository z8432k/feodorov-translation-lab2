set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE  ON)

add_library(check
        OBJECT
        check.c)
target_include_directories(check
        PRIVATE
        ${GLIB2_INCLUDE_DIRS})
target_link_libraries(check
        PUBLIC
        runner
        ${GLIB2_LDFLAGS})

list(APPEND _tests
        parser_test0
        parser_test1
        parser_test2
        parser_test3
        parser_test4
        parser_test5
        parser_test6
        parser_test7
        parser_test8
        parser_test9
        parser_test10)

foreach(_test IN LISTS _tests)
                add_executable(${_test} ${_test}.c)
                target_link_libraries(${_test}
                        PRIVATE
                        check
                        runner)
endforeach()

add_test(NAME test_'n'
        COMMAND $<TARGET_FILE:parser_test0>)

add_test(NAME test_'n*m'
        COMMAND $<TARGET_FILE:parser_test1>)

add_test(NAME test_'n+m*k'
        COMMAND $<TARGET_FILE:parser_test2>)

add_test(NAME test_'n*m+k+m'
        COMMAND $<TARGET_FILE:parser_test3>)

add_test(NAME test_'n*m+m*n'
        COMMAND $<TARGET_FILE:parser_test4>)

add_test(NAME test_'n*m+k*m+m*m*m+k*m'
        COMMAND $<TARGET_FILE:parser_test5>)

add_test(NAME test_'n*m*k+k*m+m+m*m+k*k*m+m+n*m'
        COMMAND $<TARGET_FILE:parser_test6>)

add_test(NAME test_fail_'n*mm'
        COMMAND $<TARGET_FILE:parser_test7>)
set_tests_properties(test_fail_'n*mm' PROPERTIES WILL_FAIL true)

add_test(NAME test_fail_'n++m'
        COMMAND $<TARGET_FILE:parser_test8>)
set_tests_properties(test_fail_'n++m' PROPERTIES WILL_FAIL true)

add_test(NAME test_fail_'n**'
        COMMAND $<TARGET_FILE:parser_test9>)
set_tests_properties(test_fail_'n**' PROPERTIES WILL_FAIL true)

add_test(NAME test_'n*m-k*m+n*m'
        COMMAND $<TARGET_FILE:parser_test10>)

enable_testing()


