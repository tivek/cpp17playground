# Copyright Louis Dionne 2015
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

##############################################################################
# Setup custom functions, master targets and file lists for the examples
##############################################################################
add_custom_target(examples
    COMMENT "Build all the examples.")

# Several examples have unused parameters because the name of the parameters
# are useful for illustration, even if the implementation is not actually
# presented. We don't want to generate warnings for that or need to comment
# out all unused parameter names.
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WNO_UNUSED_PARAMETER -Wno-unused-parameter)

#   cpp17playground_add_example(<name> ...)
#
# Equivalent to `cpp17playground_add_test`, except the created test is also added
# as a dependency of the `examples` target.
function(cpp17playground_add_example name)
    cpp17playground_add_test(${ARGV})
    add_dependencies(examples ${name})
endfunction()

# A list of all the example files
#
# Examples that are not available due to caveats are removed
# from this list below.
file(GLOB_RECURSE CPP17PLAYGROUND_EXAMPLE_SOURCES "${cpp17playground_SOURCE_DIR}/example/*.cpp")

##############################################################################
# Include directories
##############################################################################
include_directories(${cpp17playground_SOURCE_DIR}/include)

##############################################################################
# Add all the examples
##############################################################################
foreach(_file IN LISTS CPP17PLAYGROUND_EXAMPLE_SOURCES)
    cpp17playground_target_name_for(_target "${_file}")
    add_executable(${_target} EXCLUDE_FROM_ALL "${_file}")
    cpp17playground_add_example(${_target} ${CMAKE_CURRENT_BINARY_DIR}/${_target})
endforeach()