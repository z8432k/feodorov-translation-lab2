set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE  ON)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

flex_target(Lexer lexer.l
        ${CMAKE_CURRENT_SOURCE_DIR}/lexer.c
        DEFINES_FILE ${CMAKE_CURRENT_LIST_DIR}/lexer.h)

bison_target(Parser parser.y
        ${CMAKE_CURRENT_SOURCE_DIR}/parser.c
        DEFINES_FILE ${CMAKE_CURRENT_LIST_DIR}/parser.h)

add_flex_bison_dependency(Lexer Parser)

add_library(lexer
        OBJECT
        ${FLEX_Lexer_OUTPUTS})
target_compile_options(lexer PRIVATE "-Wno-sign-compare" "-Wno-unused-function")
target_include_directories(lexer
        PRIVATE
        ${GLIB2_INCLUDE_DIRS})

add_library(actions
        OBJECT
        actions.c)
target_include_directories(actions
        PUBLIC
        ${GLIB2_INCLUDE_DIRS})
target_compile_options(actions PRIVATE "-Wno-unused-parameter")

add_library(parser
        OBJECT
        ${BISON_Parser_OUTPUT_SOURCE})
target_link_libraries(parser
        PRIVATE
        actions)

