# This file is part of the Pandaria 5.4.8 Project. See THANKS file for Copyright information
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

if( USE_COREPCH )
  include_directories(${CMAKE_CURRENT_BINARY_DIR})
endif()

file(GLOB_RECURSE sources_Database Database/*.cpp Database/*.h Database/Implementation/*.cpp Database/Implementation/*.h  )
file(GLOB_RECURSE sources_Logging Logging/*.cpp Logging/*.h)
file(GLOB_RECURSE sources_Updater Updater/*.cpp Logging/*.h)
file(GLOB sources_localdir *.cpp *.h)

source_group(CMake FILES CMakeLists.txt)
source_group(Database FILES ${sources_Database})
source_group(Logging FILES ${sources_Logging})
source_group(Updater FILES ${sources_Updater})
source_group(localdir FILES ${sources_localdir})

#
# Build database sourcelist
#

if (USE_COREPCH)
  set(database_STAT_PCH_HDR PrecompiledHeaders/databasePCH.h)
endif()

set(database_STAT_SRCS
  ${database_STAT_SRCS}
  ${sources_Database}
  ${sources_Logging}
  ${sources_Updater}
  ${sources_localdir}
)

include_directories(
  PUBLIC
    ${CMAKE_BINARY_DIR}
  PRIVATE
    ${CMAKE_SOURCE_DIR}/dep/SFMT
    ${CMAKE_SOURCE_DIR}/dep/fmt/include
    ${CMAKE_SOURCE_DIR}/src/server
    ${CMAKE_SOURCE_DIR}/src/common
    ${CMAKE_SOURCE_DIR}/src/common/Asio
    ${CMAKE_SOURCE_DIR}/src/common/Configuration
    ${CMAKE_SOURCE_DIR}/src/common/Cryptography
    ${CMAKE_SOURCE_DIR}/src/common/Debugging
    ${CMAKE_SOURCE_DIR}/src/common/Logging
    ${CMAKE_SOURCE_DIR}/src/common/Utilities
    ${CMAKE_SOURCE_DIR}/src/server/shared/Dynamic
    ${CMAKE_SOURCE_DIR}/src/server/shared/Threading
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Database
    ${CMAKE_CURRENT_SOURCE_DIR}/Logging
    ${CMAKE_CURRENT_SOURCE_DIR}/Updater
    ${MYSQL_INCLUDE_DIR}
    ${OPENSSL_INCLUDE_DIR} 
)

if (Boost_FOUND)
  include_directories(
    PRIVATE
      ${Boost_INCLUDE_DIRS}
  )
endif()

add_library(database STATIC
  ${database_STAT_SRCS}
)

target_link_libraries(database
  PRIVATE
    fmt
    common
    ${MYSQL_LIBRARY}
    ${Boost_LIBRARIES}
)


# Generate precompiled header
if (USE_COREPCH)
  target_precompile_headers(database PRIVATE ${database_STAT_PCH_HDR}) 
endif ()
