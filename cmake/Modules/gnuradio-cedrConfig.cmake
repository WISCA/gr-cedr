find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_CEDR gnuradio-cedr)

FIND_PATH(
    GR_CEDR_INCLUDE_DIRS
    NAMES gnuradio/cedr/api.h
    HINTS $ENV{CEDR_DIR}/include
        ${PC_CEDR_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_CEDR_LIBRARIES
    NAMES gnuradio-cedr
    HINTS $ENV{CEDR_DIR}/lib
        ${PC_CEDR_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-cedrTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_CEDR DEFAULT_MSG GR_CEDR_LIBRARIES GR_CEDR_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_CEDR_LIBRARIES GR_CEDR_INCLUDE_DIRS)
