cmake_minimum_required(VERSION 3.10)

set(APP Pomme)

project (${APP}
  VERSION 0.1.0
  LANGUAGES CXX C
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(Java COMPONENTS Runtime REQUIRED)

set(JAVACC_JAR_LOCATION ${PROJECT_SOURCE_DIR}/thirdparty/javacc/javacc-7.0.10.jar)
set(JAVACC_INPUT_FILE Pomme)
set(JAVACC_GENERATED_SRC_DIR ${CMAKE_BINARY_DIR}/javacc_generated_src)
set(JJTREE_INPUT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/src/${JAVACC_INPUT_FILE}.jjt)

option(BUILD_TESTING "Build tests" ON)

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

include(GNUInstallDirs)

# Add directories for generated include files
include_directories( ${PROJECT_BINARY_DIR} ${JAVACC_GENERATED_SRC_DIR} "src/" )

# Add source to this project's executable.
add_library(${APP}
  "src/Pomme.cpp" "src/VirtualMachine.cpp" "src/Compiler.cpp" "src/CompilerVisitor.cpp" "src/PommeNode.cpp")

add_custom_target(
  JavaCCTarget
  COMMAND
    "${Java_JAVA_EXECUTABLE}" -cp "${JAVACC_JAR_LOCATION}" jjtree -OUTPUT_DIRECTORY="${JAVACC_GENERATED_SRC_DIR}" "${JJTREE_INPUT_FILE}"
  COMMAND
    "${Java_JAVA_EXECUTABLE}" -cp "${JAVACC_JAR_LOCATION}" javacc -OUTPUT_DIRECTORY="${JAVACC_GENERATED_SRC_DIR}" "${JAVACC_GENERATED_SRC_DIR}/${JAVACC_INPUT_FILE}.jj"
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
)
add_dependencies(${APP} JavaCCTarget)

file(COPY ${PROJECT_SOURCE_DIR}/input.pomme DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB JAVACC_SRC_FILES ${JAVACC_GENERATED_SRC_DIR}/*.cc)
target_sources(${APP} PRIVATE ${JAVACC_SRC_FILES})

install(
  TARGETS ${APP}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)