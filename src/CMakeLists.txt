# SPDX-FileCopyrightText: 1994-2025 Ondrej Popp <ondrej.popp70@gmail.com>
# SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL

add_custom_target(
  BuildInfo ALL
  COMMAND ${PROJECT_SOURCE_DIR}/src/scripts/mkBuild > ${PROJECT_SOURCE_DIR}/src/src/Build.h
  COMMENT "Generating build info"
)

set(S_SRCS
  ${S_SRCS}
  Usage.cc
  Driver.cc
  main.cc
 )

add_subdirectory(objects)
add_subdirectory(src)
add_subdirectory(util)

add_executable(S ${S_SRCS})

if(MINGW OR MSYS)
  message(STATUS "MinGW detected.")
  target_link_libraries(S regex)
endif()

install(TARGETS S DESTINATION $ENV{HOME}/bin)

target_include_directories(
 S
 PRIVATE
 .
 util
 objects
)
