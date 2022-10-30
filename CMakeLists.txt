cmake_minimum_required(VERSION 3.10)
# SET(CNAKE_C_COMPILER /usr/bin/gcc)

# set the project name
project(Matrix)


include_directories(include)
aux_source_directory (src MAT_SRC)
add_library(${PROJECT_NAME} SHARED ${MAT_SRC})


# target_link_libraries(${PROJECT_NAME} Mat)
add_executable(MatDemo demo.c)
target_link_libraries(MatDemo ${PROJECT_NAME})

add_executable(MatCppDemo cppdemo.cpp)
target_link_libraries(MatCppDemo ${PROJECT_NAME})

add_custom_target(debug
  COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
  COMMENT "Switch CMAKE_BUILD_TYPE to Debug"
  add_executable(Calculator demo.cpp ${DIR_SRCS})
  )

# add_custom_target(release
#   COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Release ${CMAKE_SOURCE_DIR}
#   COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
#   COMMENT "Switch CMAKE_BUILD_TYPE to Release"
#   add_executable(Calculator main.cpp ${DIR_SRCS})
#   )

# # add the executable
