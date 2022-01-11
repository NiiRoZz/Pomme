get_filename_component(POMME_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
include(CMakeFindDependencyMacro)

if(NOT TARGET Pomme::Pomme)
    include("${POMME_CMAKE_DIR}/PommeTargets.cmake")
endif()
