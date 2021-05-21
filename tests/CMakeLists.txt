find_package(Threads REQUIRED)

add_executable(pomme_tests
  main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/src/gtest-all.cc
  test1.cpp
)


target_include_directories(pomme_tests
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include
    ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest
)

target_link_libraries(pomme_tests
  PRIVATE
    Pomme
    Threads::Threads
)

add_test(
  NAME POMME_TEST
  COMMAND pomme_tests
)