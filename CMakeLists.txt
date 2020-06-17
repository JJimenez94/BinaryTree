cmake_minimum_required(VERSION 3.0.0)

# Configuration of environment variables
message("=============== CONFIGURING ENVIRONMENT VARIABLES ===============")
message("VCPKG_ROOT: $ENV{VCPKG_ROOT}")
message("CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")
if(DEFINED ENV{VCPKG_ROOT})
    if(DEFINED CMAKE_TOOLCHAIN_FILE AND "${CMAKE_TOOLCHAIN_FILE}" STREQUAL "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
        message("Already added value of VCPKG_ROOT")
    else()
        if("${CMAKE_TOOLCHAIN_FILE}" STREQUAL "")
            set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
        else()
            set(CMAKE_TOOLCHAIN_FILE "${CMAKE_TOOLCHAIN_FILE};$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
        endif()
        message("Modified CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")
    endif()    
else()
    message("VCPKG_ROOT IS UNDEFINED")
endif()
message("=============== END CONFIGURING ENVIRONMENT VARIABLES ===============")

project(BinaryTree VERSION 0.1.0)

include(CTest)
enable_testing()

# Configuration of dependencies
message("=============== CONFIGURING DEPENDENCIES ===============")
find_package(SQLite3 CONFIG REQUIRED)
find_package(cpprestsdk CONFIG REQUIRED)
message("=============== END CONFIGURING DEPENDENCIES ===============")

add_executable(BinaryTree 
        main.cpp 
        src/BinaryTree.h
        src/BinaryTree.cpp
        src/Node.h)

target_link_libraries(BinaryTree PRIVATE sqlite3)
target_link_libraries(BinaryTree PRIVATE cpprestsdk::cpprest)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
