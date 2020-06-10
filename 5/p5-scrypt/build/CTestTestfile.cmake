# CMake generated Testfile for 
# Source directory: /home/apercov/Documents/Secure and Dependable Systems/5/p5-scrypt
# Build directory: /home/apercov/Documents/Secure and Dependable Systems/5/p5-scrypt/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(misc "/home/apercov/Documents/Secure and Dependable Systems/5/p5-scrypt/build/test/check-scrypt")
set_tests_properties(misc PROPERTIES  _BACKTRACE_TRIPLES "/home/apercov/Documents/Secure and Dependable Systems/5/p5-scrypt/CMakeLists.txt;19;add_test;/home/apercov/Documents/Secure and Dependable Systems/5/p5-scrypt/CMakeLists.txt;0;")
subdirs("src")
subdirs("test")
