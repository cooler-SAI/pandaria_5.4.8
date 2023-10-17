# Copyright (C) 2011-2016 Project SkyFire <http://www.projectskyfire.org/
# Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

# Set build-directive (used in core to tell which buildtype we used)
add_definitions(-D_BUILD_DIRECTIVE='"${CMAKE_BUILD_TYPE}"')
add_definitions(-fno-delete-null-pointer-checks)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections -s -w" CACHE INTERNAL "EXE_LINKER_FLAGS" FORCE)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections" CACHE INTERNAL "C_FLAGS" FORCE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(COMPILER_FLAGS "")

if (WITH_SANITIZER)
  set(COMPILER_FLAGS "${COMPILER_FLAGS} -fsanitize=address -fsanitize-recover=address")
endif()

if (BUILD_DEPLOY)
  set(COMPILER_FLAGS "${COMPILER_FLAGS} -march=native -fno-strict-aliasing -g3")
  if (NOT INSTALL_PREFIX)
    set(INSTALL_PREFIX "/server/wow/horizon")
  endif()
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMPILER_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILER_FLAGS}")

if( WITH_WARNINGS )
  add_definitions(-Wall -Wfatal-errors -Wextra)
  message(STATUS "GCC: All warnings enabled")
else()
  add_definitions(--no-warnings)
  message(STATUS "GCC: All warnings disabled")
endif()

if( WITH_COREDEBUG )
  add_definitions(-ggdb3)
  message(STATUS "GCC: Debug-flags set (-g3)")
endif()
