cmake_minimum_required(VERSION 3.16)
project(Platformer LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(Platformer src/main.cpp src/Button.cpp src/Hitbox.cpp src/GUI.cpp src/Level.cpp src/Player)
target_link_libraries(Platformer PRIVATE sfml-graphics)
target_compile_features(Platformer PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET Platformer
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Platformer>
        VERBATIM)
endif()

install(TARGETS Platformer)
