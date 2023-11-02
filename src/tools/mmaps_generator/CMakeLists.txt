# Copyright (C) 2011-2016 Project SkyFire <http://www.projectskyfire.org/>
# Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

file(GLOB_RECURSE mmap_gen_sources *.cpp *.h)

include_directories(
  PUBLIC
    ${CMAKE_BINARY_DIR}
  PRIVATE  
    ${ACE_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/dep/zlib
    ${CMAKE_SOURCE_DIR}/dep/bzip2
    ${CMAKE_SOURCE_DIR}/dep/g3dlite/include
    ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Recast
    ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Recast/Include
    ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Detour
    ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Detour/Include
    ${CMAKE_SOURCE_DIR}/src/common
    ${CMAKE_SOURCE_DIR}/src/common/Logging
    ${CMAKE_SOURCE_DIR}/src/common/Utilities
    ${CMAKE_SOURCE_DIR}/src/server/shared
    ${CMAKE_SOURCE_DIR}/src/server/shared/Database
    ${CMAKE_SOURCE_DIR}/src/server/shared/Utilities   
    ${CMAKE_SOURCE_DIR}/src/server/game/Conditions
    ${CMAKE_SOURCE_DIR}/src/server/game/Miscellaneous
    ${CMAKE_SOURCE_DIR}/src/server/collision
    ${CMAKE_SOURCE_DIR}/src/server/collision/Management
    ${CMAKE_SOURCE_DIR}/src/server/collision/Maps
    ${CMAKE_SOURCE_DIR}/src/server/collision/Models
)

add_executable(mmaps_generator ${mmap_gen_sources})

target_link_libraries(mmaps_generator
  PRIVATE
    common
    shared
    collision
    g3dlib
    Recast
    Detour
    ${ACE_LIBRARY}
    ${BZIP2_LIBRARIES}
    ${ZLIB_LIBRARIES}
    ${Boost_LIBRARIES}
    Threads::Threads
)

if( UNIX )
  install(TARGETS mmaps_generator DESTINATION bin)
elseif( WIN32 )
  install(TARGETS mmaps_generator DESTINATION "${CMAKE_INSTALL_PREFIX}")
endif()
