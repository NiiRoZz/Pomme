cmake_minimum_required (VERSION 3.8)

project ("Pomme"
  VERSION 0.1.0
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(antlr4-runtime REQUIRED)
find_package(antlr4-generator REQUIRED)

set(ANTLR4_JAR_LOCATION ${PROJECT_SOURCE_DIR}/thirdparty/antlr/antlr-4.9-complete.jar)

if(NOT MSVC)
  add_definitions(-Wall -Wextra -g -pedantic)
endif()

# generate both
antlr4_generate( 
  antlrpomme_lexer
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Pomme.g4
  BOTH
  FALSE
  TRUE
  "antlrpomme"
  "${ANTLR4_TOKEN_FILES_antlrpomme_lexer}"
  "${ANTLR4_TOKEN_DIRECTORY_antlrpomme_lexer}"
)

# Add directories for generated include files
include_directories( ${PROJECT_BINARY_DIR} ${ANTLR4_INCLUDE_DIR} ${ANTLR4_INCLUDE_DIR_antlrpomme_lexer} ${ANTLR4_INCLUDE_DIR_antlrpomme_parser} )

# Add source to this project's executable.
add_executable (Pomme
  src/Pomme.cpp
  ${ANTLR4_SRC_FILES_antlrpomme_lexer}
  ${ANTLR4_SRC_FILES_antlrpomme_parser}
)

add_dependencies(Pomme antlr4_static)

target_link_libraries(Pomme antlr4_static)
