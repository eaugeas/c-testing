include(ExternalProject)

set(CFLAGS_BINARY_DIR ${DEPS_BINARY_DIR}/c-flags-prefix/src/c-flags-build)

ExternalProject_Add(c-flags
  URL https://github.com/eaugeas/c-flags/archive/refs/tags/v0.0.2.zip
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CFLAGS_BINARY_DIR}
  DOWNLOAD_NO_PROGRESS true
  DOWNLOAD_EXTRACT_TIMESTAMP NEW
)

file(MAKE_DIRECTORY ${CFLAGS_BINARY_DIR}/lib)
file(MAKE_DIRECTORY ${CFLAGS_BINARY_DIR}/include)
file(TOUCH ${CFLAGS_BINARY_DIR}/lib/libflags.a)

add_library(flags STATIC IMPORTED GLOBAL)
add_dependencies(flags c-flags)
set_target_properties(flags PROPERTIES IMPORTED_LOCATION ${CFLAGS_BINARY_DIR}/lib/libflags.a)
set_target_properties(flags PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${CFLAGS_BINARY_DIR}/include)
