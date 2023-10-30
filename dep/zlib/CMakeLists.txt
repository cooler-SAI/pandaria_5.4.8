file(GLOB sources *.c *.h)

set(ZLIB_SRCS
   ${sources}
)

include_directories(
   ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(zlib STATIC ${ZLIB_SRCS})

set_target_properties(zlib PROPERTIES LINKER_LANGUAGE C)
