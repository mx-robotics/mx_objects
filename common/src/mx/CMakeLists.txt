configure_file(config.h.in "${CMAKE_CURRENT_BINARY_DIR}/config.h" @ONLY)

add_library(mx_objects SHARED mx_objects.cpp config.h.in)

set_target_properties(mx_objects PROPERTIES
  PUBLIC_HEADER "${CMAKE_CURRENT_BINARY_DIR}/config.h")

install(TARGETS mx_objects
  # IMPORTANT: Add the car_com library to the "export-set"
  EXPORT MXObjectsTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/car/com"
    COMPONENT dev)

add_executable(mx_objects_demo main.cpp)
target_link_libraries(mx_objects_demo mx_objects)


install(TARGETS mx_objects_demo
  # IMPORTANT: Add the joystick executable to the "export-set"
  EXPORT MXObjectsTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin)
  
