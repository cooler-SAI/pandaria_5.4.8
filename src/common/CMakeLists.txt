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

file(GLOB_RECURSE sources_Cryptography Cryptography/*.cpp Cryptography/*.h Cryptography/Authentication/*.cpp Cryptography/Authentication/*.h)
file(GLOB_RECURSE sources_Utilities Utilities/*.cpp Utilities/*.h)
file(GLOB sources_localdir *.cpp *.h)

source_group(CMake FILES CMakeLists.txt)
source_group(Configuration FILES ${sources_Configuration})
source_group(Cryptography FILES ${sources_Cryptography})
source_group(Utilities FILES ${sources_Utilities})

if (USE_COREPCH)
  set(common_STAT_PCH_HDR PrecompiledHeaders/commonPCH.h)
endif()

set(common_STAT_SRCS
  ${common_STAT_SRCS}
  ${sources_Cryptography}
  ${sources_Utilities}
  ${sources_localdir}
)

include_directories(
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Cryptography
    ${CMAKE_CURRENT_SOURCE_DIR}/Cryptography/Authentication  
    ${CMAKE_BINARY_DIR}
    ${OPENSSL_INCLUDE_DIR}   
  PRIVATE
    ${CMAKE_SOURCE_DIR}/dep/SFMT
    ${CMAKE_SOURCE_DIR}/dep/fmt/include
    ${CMAKE_SOURCE_DIR}/dep/utf8cpp
)

if (Boost_FOUND)
  include_directories(
    PRIVATE
      ${Boost_INCLUDE_DIRS}
  )
endif()

add_library(common STATIC
  ${common_STAT_SRCS}
)

target_link_libraries(common
  PRIVATE
    sfmt
    fmt
    ${OPENSSL_LIBRARIES}
)


# Generate precompiled header
if (USE_COREPCH)
  target_precompile_headers(common PRIVATE ${common_STAT_PCH_HDR}) 
endif ()
