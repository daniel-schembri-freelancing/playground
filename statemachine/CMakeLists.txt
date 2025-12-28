# Subprojekt "statemachine"
add_executable(statemachine
    main.cpp
    statemachine_template.cpp
)

target_include_directories(statemachine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
