cmake_minimum_required(VERSION 3.0.0)


if(${CMAKE_VERSION} VERSION_LESS 3.28)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.28)
endif()

project(MoranModel 
        VERSION 0.1.0 
        LANGUAGES C CXX
        DESCRIPTION "Moran model simulator"
        )


include(CTest)
enable_testing()

configure_file(MoranConfig.h.in MoranConfig.h)

add_subdirectory(MoranModel)
add_subdirectory(utils)
# add_library(MoranModel MoranModel/MoranModel.cpp MoranModel/MoranModel.h)
# add_library(utils utils/utils.cpp utils/utils.h)

add_executable(MoranSimulator main.cpp)

target_link_libraries(MoranSimulator PUBLIC MoranModel utils)
target_include_directories(MoranSimulator PUBLIC "${PROJECT_BINARY_DIR}"
                                       "${PROJECT_SOURCE_DIR}/MoranModel"
                                       "${PROJECT_SOURCE_DIR}/utils")



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
