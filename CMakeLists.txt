cmake_minimum_required(VERSION 3.15)

project(reinhard
  LANGUAGES C
  VERSION 0.0.0
)

set(CMAKE_C_STANDARD 17)
set(CMAKE_BUILD_TYPE DEBUG)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -ggdb")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -ggdb -Wall -Wextra -Wpedantic -Werror")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)

file(GLOB SOURCE_FILES "src/*.c")
include_directories(include)
add_executable(reinhard ${SOURCE_FILES})

target_sources(reinhard PRIVATE src/main.c)

target_link_directories(reinhard PRIVATE Vulkan::Vulkan)
target_link_directories(reinhard PRIVATE GLFW::glfw)
target_link_libraries(reinhard glfw Vulkan::Vulkan)