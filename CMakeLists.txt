cmake_minimum_required(VERSION 3.29)
project(SFML_Splines CXX)

if (WIN32)
  #set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>") # first change conan profile compiler.runtime to static instead of dynamic
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)

include(${CMAKE_BINARY_DIR}/generators/portable-file-dialogs-config.cmake)
find_package(SFML REQUIRED)

# automatically add all cpp files in src to the project
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

### Not needed for this project yet ------------------
# Create macro called RESOURCES_PATH that points the assets folder
#target_compile_definitions(${PROJECT_NAME} PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets") # absolute path
# target_compile_definitions(${PROJECT_NAME} PUBLIC RESOURCES_PATH="../../assets") # uncomment this line when sharing with other people to use relative path
### Not needed for this project yet -------------------

target_link_libraries(${PROJECT_NAME} PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    portable-file-dialogs::portable-file-dialogs
)

if(APPLE)
    target_link_options(${PROJECT_NAME} PRIVATE "-ObjC" "-all_load")
endif()
