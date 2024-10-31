
file(GLOB libvsc_tr_SRC
  "*.h"
  "*.cpp"
  )
  
add_library(vsc-tr SHARED ${libvsc_tr_SRC})

target_include_directories(vsc-tr PUBLIC
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/include
    ${vsc_dm_INCDIR}
    ${debug_mgr_INCDIR}
    )
   
target_link_directories(vsc-tr PRIVATE
    ${CMAKE_BINARY_DIR}/lib
    ${CMAKE_BINARY_DIR}/lib64
    "${debug_mgr_LIBDIR}"
    )
  
install(TARGETS vsc-tr
    DESTINATION lib
    EXPORT libvsc-tr-targets)


