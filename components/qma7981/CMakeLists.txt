


SET(include_dir "." "include")


idf_component_register(
    SRCS "qma7981.c"
    INCLUDE_DIRS ${include_dir}
    REQUIRES driver  
    )

# set_property(TARGET ${COMPONENT_LIB} APPEND PROPERTY LINK_INTERFACE_MULTIPLICITY 3)