cmake_minimum_required (VERSION 3.8)

project ("Pomme"
  VERSION 0.1.0
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(Java COMPONENTS Runtime REQUIRED)

set(JAVACC_JAR_LOCATION ${PROJECT_SOURCE_DIR}/thirdparty/javacc/javacc-7.0.10.jar)
set(JAVACC_InputFile Pomme)
set(JAVACC_GeneratedSrcDir ${CMAKE_BINARY_DIR}/javacc_generated_src)
set(JJTREE_INPUT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/src/${JAVACC_InputFile}.jjt)

# Add directories for generated include files
include_directories( ${PROJECT_BINARY_DIR} ${JAVACC_GeneratedSrcDir} "src/" )

# Add source to this project's executable.
add_executable(Pomme
  "src/Pomme.cpp" "src/VirtualMachine.cpp" "src/Compiler.cpp" "src/CompilerVisitor.cpp" "src/PommeNode.cpp")

add_custom_target(
  JavaCCTarget
  COMMAND
    "${Java_JAVA_EXECUTABLE}" -cp "${JAVACC_JAR_LOCATION}" jjtree -OUTPUT_DIRECTORY="${JAVACC_GeneratedSrcDir}" "${JJTREE_INPUT_FILE}"
  COMMAND
    "${Java_JAVA_EXECUTABLE}" -cp "${JAVACC_JAR_LOCATION}" javacc -OUTPUT_DIRECTORY="${JAVACC_GeneratedSrcDir}" "${JAVACC_GeneratedSrcDir}/${JAVACC_InputFile}.jj"
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
)
add_dependencies(Pomme JavaCCTarget)

file(COPY ${PROJECT_SOURCE_DIR}/input.pomme DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB JAVACC_SRC_FILES ${JAVACC_GeneratedSrcDir}/*.cc)
target_sources(Pomme PUBLIC ${JAVACC_SRC_FILES})
