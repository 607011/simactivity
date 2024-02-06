cmake_minimum_required(VERSION 3.16)

project(iamhere
        VERSION 0.9.0
        DESCRIPTION "Fake User Presence"
        LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_library(FRAMEWORK_CARBON Carbon)
find_library(FRAMEWORK_IOKIT IOKIt)

if(LINUX)
  FindX11()
endif()

if(APPLE)
  set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64" CACHE STRING "" FORCE)
  set(PLATFORM_SOURCES src/platform/fake_mac.c)
elseif(LINUX)
  set(PLATFORM_SOURCES src/platform/fake_linux.c)
elseif(WIN32)
  set(PLATFORM_SOURCES src/platform/fake_win.c)
endif()

if(UNIX)
  set(CMAKE_C_FLAGS "-pthread -Wno-deprecated-declarations")
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -O0 -g3 -ggdb -DDEBUG -pedantic -Wall -Wextra -Wconversion -Wreorder -Wuninitialized -Wtype-limits -Wno-pragmas")
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -Os -DNDEBUG -Wno-deprecated")
elseif(WIN32)
  set(CMAKE_C_FLAGS_DEBUG "/Od /Wall /Zi /D_CRT_SECURE_NO_WARNINGS /D__STDC_WANT_SECURE_LIB__")
  set(CMAKE_C_FLAGS_RELEASE "/Os /W1 /DNDEBUG /D_CRT_SECURE_NO_WARNINGS /D__STDC_WANT_SECURE_LIB__")
endif(UNIX)

add_definitions(-DPROJECT_NAME="${CMAKE_PROJECT_NAME}" -DPROJECT_VERSION="${CMAKE_PROJECT_VERSION}")

set(SOURCES
  ${PLATFORM_SOURCES}
  src/main.c
)

add_executable(iamhere ${SOURCES})

target_include_directories(iamhere
PRIVATE
  src
PUBLIC
)

target_link_libraries(iamhere
  PUBLIC
  ${FRAMEWORK_CARBON}
  ${FRAMEWORK_IOKIT}
)

if(UNIX)
  if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_custom_command(TARGET iamhere
      POST_BUILD
      COMMAND strip iamhere)
  endif()
endif(UNIX)

install(TARGETS iamhere RUNTIME DESTINATION bin)


