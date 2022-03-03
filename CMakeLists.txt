cmake_minimum_required(VERSION 3.0.0)
project(optimal_path VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(Eigen3 3.3 REQUIRED NO_MODULE)
set(CMAKE_PREFIX_PATH "/home/arman/Qt/6.2.1/gcc_64/")
find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(optimal_path src/main.cpp src/graph.cpp src/mainwindow.cpp src/mythread.cpp)
target_link_libraries(optimal_path Eigen3::Eigen)
target_link_libraries(optimal_path Qt6::Widgets)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
