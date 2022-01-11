cmake_minimum_required(VERSION 3.10)

set(APP Pomme)

project (${APP}
  VERSION 0.1.0
  LANGUAGES CXX C
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if(JAVACC_GENERATE MATCHES ON)
find_package(Java COMPONENTS Runtime REQUIRED)
endif()

option(JAVACC_GENERATE "Generate JAVACC files" OFF)

if(JAVACC_GENERATE MATCHES ON)
  set(JAVACC_JAR_LOCATION ${PROJECT_SOURCE_DIR}/thirdparty/javacc/javacc-7.0.10.jar)
  set(JAVACC_GENERATED_SRC_DIR ${CMAKE_BINARY_DIR}/javacc_generated_src)
  set(JAVACC_INPUT_FILE Pomme)
  set(JJTREE_INPUT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/src/${JAVACC_INPUT_FILE}.jjt)
else()
  set(JAVACC_GENERATED_SRC_DIR ${PROJECT_SOURCE_DIR}/include/javacc)
endif()

option(BUILD_TESTING "Build tests" ON)

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

include(GNUInstallDirs)

# Add directories for generated include files
include_directories( ${PROJECT_BINARY_DIR} ${JAVACC_GENERATED_SRC_DIR} "src/" "include/Pomme" )

file(GLOB JAVACC_SOURCE_FILES
    src/Javacc/*.cc
)

# Add source to this project's executable.
add_library(${APP}
  "src/VM/ObjectMemory.cpp"
  "src/VM/VirtualMachine.cpp"
  "src/VM/Chunk.cpp"
  "src/VM/Object.cpp"
  "src/VM/Value.cpp"
  "src/Automate/Automaton.cpp"
  "src/Compiler.cpp"
  "src/TypeChecker.cpp"
  "src/CompilerVisitor.cpp"
  "src/TypeCheckerVisitor.cpp"
  "src/PommeNode.cpp"
  "src/CommonVisitorFunction.cpp"
  "src/AutomateVisitor.cpp"
  ${JAVACC_SOURCE_FILES})

if(JAVACC_GENERATE MATCHES ON)
  add_custom_target(
    JavaCCTarget
    COMMAND
      "${Java_JAVA_EXECUTABLE}" -cp "${JAVACC_JAR_LOCATION}" jjtree -OUTPUT_DIRECTORY="${JAVACC_GENERATED_SRC_DIR}" "${JJTREE_INPUT_FILE}"
    COMMAND
      "${Java_JAVA_EXECUTABLE}" -cp "${JAVACC_JAR_LOCATION}" javacc -OUTPUT_DIRECTORY="${JAVACC_GENERATED_SRC_DIR}" "${JAVACC_GENERATED_SRC_DIR}/${JAVACC_INPUT_FILE}.jj"
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
  )
  add_dependencies(${APP} JavaCCTarget)
endif()

file(GLOB MY_TESTS_FILES
  ${PROJECT_SOURCE_DIR}/tests/result_tests/*.txt
)
file(COPY ${MY_TESTS_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/tests)
file(COPY ${PROJECT_SOURCE_DIR}/library/std.pomme DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if(JAVACC_GENERATE MATCHES ON)
  file(GLOB JAVACC_SRC_FILES ${JAVACC_GENERATED_SRC_DIR}/*.cc)
else()
  file(GLOB JAVACC_SRC_FILES include/javacc/*.cc)
endif()

target_sources(${APP} PRIVATE ${JAVACC_SRC_FILES})

if(NOT MSVC)
  target_compile_options(${APP} PRIVATE -Wall -Wextra -g -pedantic)
elseif(MSVC)
  target_compile_options(${APP} PRIVATE )
endif()

install(
  TARGETS ${APP}
  EXPORT ${APP}Targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(
  DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/Pomme"
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
  EXPORT ${APP}Targets
  NAMESPACE Pomme::
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Pomme"
)

install(
  FILES PommeConfig.cmake
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Pomme"
)