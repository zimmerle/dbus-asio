find_path(DBUS_ASIO_INCLUDE_DIR dbus.h PATH_SUFFIXES libdbus-asio include/libdbus-asio)

set(DBUS_ASIO_NAMES ${DBUS_ASIO_NAMES} dbus-asio )
find_library(DBUS_ASIO_LIBRARY NAMES ${DBUS_ASIO_NAMES} )

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(DBUS_ASIO DEFAULT_MSG DBUS_ASIO_LIBRARY DBUS_ASIO_INCLUDE_DIR)

if(DBUS_ASIO_FOUND)
  set(DBUS_ASIO_LIBRARIES ${DBUS_ASIO_LIBRARY})
endif()

# Deprecated declarations.
set (NATIVE_DBUS_ASIO_INCLUDE_PATH ${DBUS_ASIO_INCLUDE_DIR} )
if(DBUS_ASIO_LIBRARY)
  get_filename_component (NATIVE_DBUS_ASIO_LIB_PATH ${DBUS_ASIO_LIBRARY} PATH)
endif()

mark_as_advanced(DBUS_ASIO_LIBRARY DBUS_ASIO_INCLUDE_DIR )
