# cmake_minimum_required(VERSION 3.10)
# project(SFMLProject)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # Find the SFML library
# set(SFML_STATIC_LIBRARIES TRUE)
# set(SFML_DIR "C:/SFML-2.6.0/lib/cmake/SFML")
# find_package(SFML 2.6 COMPONENTS system window graphics network audio REQUIRED)


# # Add your source files here
# add_executable(main main.cpp)

# # Link your executable to SFML
# target_link_libraries(main PRIVATE sfml-system sfml-window sfml-graphics sfml-network sfml-audio opengl32)

cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

file(GLOB SRCS CONFIGURE_DEPENDS 
    ${CMAKE_SOURCE_DIR}/src/*.cpp 
    ${CMAKE_SOURCE_DIR}/src/framework/*.cpp
    ${CMAKE_SOURCE_DIR}/src/activities/*.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/*.cpp
)

add_executable(game ${SRCS})
target_link_libraries(game PRIVATE sfml-graphics sfml-window sfml-system)
target_compile_features(game PRIVATE cxx_std_17)
target_include_directories(game PRIVATE 
    ${CMAKE_SOURCE_DIR}/include 
    ${CMAKE_SOURCE_DIR}/include/framework
    ${CMAKE_SOURCE_DIR}/include/activities
    ${CMAKE_SOURCE_DIR}/include/gui
)

if(WIN32)
    add_custom_command(
        TARGET game
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:game>
        VERBATIM)
endif()

install(TARGETS game)

# cmake -S. -Bbuild -G "MinGW Makefiles"
# cmake --build build
# cmake --build build --verbose 