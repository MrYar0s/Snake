cmake_minimum_required(VERSION 3.11)
project(snake)

enable_language(CXX)
add_compile_options(-Wall -Werror)

add_executable(${PROJECT_NAME} main.cpp)

#For SFML
#set(SFML_DIR SFML/lib/cmake/SFML)
#find_package(SFML 2.5 COMPONENTS graphics REQUIRED window system network audio REQUIRED)
#target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system sfml-network sfml-audio)

file(GLOB_RECURSE GAME_SOURCES Gview/*.[ch]pp Tview/*.[ch]pp Game/*.[ch]pp main.cpp)
set(GAME_SOURCES ${GAME_SOURCES})

add_library(Game SHARED ${GAME_SOURCES})
target_include_directories(Game PUBLIC Game/ Gview/ Tview/)

target_link_libraries(${PROJECT_NAME} Game)

if(TIDY)
        set(CMAKE_CXX_CLANG_TIDY
        clang-tidy;
        --format-style=file;
        --header-filter=*.hpp;
			)
        message(STATUS "clang-tidy ON")
endif()

if(FORMAT)
        file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.hpp)
        add_custom_target(
                format
                COMMAND clang-format
    	        -style=file
                -i
                ${ALL_SOURCE_FILES}
		)
        message(STATUS "clang-format ON")
endif()

add_custom_target(run COMMENT "Running the game" COMMAND ./${PROJECT_NAME})
add_dependencies(run ${PROJECT_NAME})