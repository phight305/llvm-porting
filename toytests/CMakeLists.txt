set(TOY_TEST_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/toytests)

set(TESTS
    basic
    if_else
    loop
    loop_loop
)

# Copy regression.sh
add_custom_command(
    OUTPUT ${TOY_TEST_DIR}/regression.sh
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
            ${CMAKE_CURRENT_SOURCE_DIR}/regression.sh
            ${TOY_TEST_DIR}/regression.sh
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/regression.sh
    COMMENT "Copying regression.sh ..."
)

add_custom_target(copyScript ALL
    DEPENDS ${TOY_TEST_DIR}/regression.sh
)

# Copy all of the .ll files
foreach(TEST ${TESTS})
    add_custom_command(
        OUTPUT ${TOY_TEST_DIR}/${TEST}/${TEST}.ll 
        COMMAND ${CMAKE_COMMAND} -E copy_if_different 
                ${CMAKE_CURRENT_SOURCE_DIR}/${TEST}/${TEST}.ll
                ${TOY_TEST_DIR}/${TEST}/${TEST}.ll
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${TEST}/${TEST}.ll
        COMMENT "Copying ${TEST}/${TEST}.ll ..."
    )
endforeach() 

# Compile all of the .ll using llc and generate the verifiers
foreach(TEST ${TESTS})
    add_custom_command(
        OUTPUT ${TOY_TEST_DIR}/${TEST}/${TEST}.o
        COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/llc -filetype=obj ${TOY_TEST_DIR}/${TEST}/${TEST}.ll 
        DEPENDS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/llc
                ${TOY_TEST_DIR}/${TEST}/${TEST}.ll
        WORKING_DIRECTORY ${TOY_TEST_DIR}/${TEST} 
        COMMENT "Generating ${TEST}/${TEST}.o ..."
    )
    set(COMPILETEST ${COMPILETEST} ${TOY_TEST_DIR}/${TEST}/${TEST}.o)

    add_executable(${TEST}_verifier ${CMAKE_CURRENT_SOURCE_DIR}/${TEST}/${TEST}_verifier.cpp)
    set_target_properties(${TEST}_verifier PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${TOY_TEST_DIR}/${TEST}
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON
    )
endforeach()

add_custom_target(compileTOYTest ALL
    DEPENDS ${COMPILETEST}
)
