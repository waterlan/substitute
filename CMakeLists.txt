# SPDX-FileCopyrightText: 1994-2025 Ondrej Popp <ondrej.popp70@gmail.com>
# SPDX-License-Identifier: GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL

cmake_minimum_required(VERSION 3.16)

set(MAJOR_VERSION 1)
set(MINOR_VERSION 0)

set(VERSION "${MAJOR_VERSION}.${MINOR_VERSION}")

set(CMAKE_CXX_STANDARD 23)

add_compile_options(-Wall -Wextra)

project(S VERSION ${VERSION} LANGUAGES CXX)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

include(FeatureSummary)
feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

add_subdirectory(src)
