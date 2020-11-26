cmake_minimum_required( VERSION 3.0 )
project( matrix )

# include
include_directories( ./include )

# target
add_executable( matrix ./tests/test.cpp )