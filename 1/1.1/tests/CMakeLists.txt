cmake_minimum_required(VERSION 2.4 FATAL_ERROR)

pkg_check_modules(CHECK REQUIRED check)

include_directories(${CMAKE_SOURCE_DIR}/src ${CHECK_INCLUDE_DIRS})
link_directories(${CHECK_LIBRARY_DIRS})
add_executable(check_stack check_stack.c)

target_link_libraries(check_rpn-stack rpn-stack
	${CHECK_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(check_rpn rpn rpn-stack
	${CHECK_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT})
