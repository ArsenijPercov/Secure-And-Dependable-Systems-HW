# 
# pnmhide/src/CMakeLists.txt --
#

pkg_check_modules(NETPBM netpbm)
add_definitions(${NETPBM_CFLAGS})

add_executable(pnmhide pnmhide.c image.c hide.c)
if(NETPBM_FOUND)
  target_link_libraries(pnmhide ${NETPBM_LDFLAGS})
else()
  add_definitions(-DFLAT_NETPBM)
  target_link_libraries(pnmhide netpbm)
endif()

if(CMAKE_C_COMPILER_ID MATCHES "GNU")
  add_definitions(--std=c99 -O0 -Wall)
endif()

if(CMAKE_C_COMPILER_ID MATCHES "Clang")
  add_definitions(--std=c99 -O0 -Wall)
endif()

