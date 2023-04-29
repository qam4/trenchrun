cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    trenchrun
    VERSION 0.1.0
    DESCRIPTION "Star Wars themed chess-like engine"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    trenchrun_lib OBJECT
    source/Board.cpp
    source/Common.cpp
    source/Move.cpp
    source/MoveGenerator.cpp
    source/MoveList.cpp
    source/Output.cpp
    source/Parser.cpp
    source/MiniMax.cpp
    source/NegaMax.cpp
    source/AlphaBeta.cpp
    source/Quiesce.cpp
    source/Zobrist.cpp
    source/ValidateMove.cpp
)

target_include_directories(
    trenchrun_lib ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(trenchrun_lib PUBLIC cxx_std_17)

# ---- Declare executable ----

add_executable(trenchrun_exe source/Trenchrun.cpp)
add_executable(trenchrun::exe ALIAS trenchrun_exe)

set_property(TARGET trenchrun_exe PROPERTY OUTPUT_NAME trenchrun)

target_compile_features(trenchrun_exe PRIVATE cxx_std_17)

target_link_libraries(trenchrun_exe PRIVATE trenchrun_lib)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT trenchrun_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of trenchrun"
  )
endif()

include(cmake/dev-mode.cmake)
