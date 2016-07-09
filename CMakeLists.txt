# Copyright Louis Dionne 2015
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

##############################################################################
# Setup project
##############################################################################
project(cpp17playground CXX)
cmake_minimum_required(VERSION 3.0)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
enable_testing()


##############################################################################
# Setup CMake options
##############################################################################
include(CMakeDependentOption)
option(CPP17PLAYGROUND_ENABLE_VALGRIND "Run the unit tests and examples under Valgrind if it is found." OFF)
option(CPP17PLAYGROUND_ENABLE_ASAN "Run the unit tests and examples using AddressSanitizer." OFF)
option(CPP17PLAYGROUND_ENABLE_COVERAGE "Run the unit tests and examples with code coverage instrumentation." OFF)
option(CPP17PLAYGROUND_ENABLE_WERROR "Fail and stop if a warning is triggered." OFF)
option(CPP17PLAYGROUND_ENABLE_DEBUG_INFORMATION "Includes debug information in the binaries." OFF)
option(CPP17PLAYGROUND_ENABLE_ASSERTIONS "Enables assertions." OFF)

##############################################################################
# Setup compiler flags (more can be set on a per-target basis or in subdirectories)
##############################################################################
# Compiler flags:
include(CheckCXXCompilerFlag)
macro(cpp17playground_append_flag testname flag)
    check_cxx_compiler_flag(${flag} ${testname})
    if (${testname})
        add_compile_options(${flag})
    endif()
endmacro()

# Language flag: version of the C++ standard to use
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_STDCXX1z -std=c++1z)

# PITA warning flags:
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WSHADOW -Wshadow)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WUNUSED -Wunused)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WUNUSED_FUNCTION -Wunused-function)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WUNUSED_LABEL -Wunused-label)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WUNUSED_PARAMETER -Wunused-parameter)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WUNUSED_VALUE -Wunused-value)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WUNUSED_VARIABLE -Wunused-variable)

# Warning flags:
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WALL -Wall)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WEXTRA -Wextra)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WDEPRECATED -Wdeprecated)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WDOCUMENTATION -Wdocumentation)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WCOMMENT -Wcomment)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_PEDANTIC -Wpedantic)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WSTACK_PROTECTOR -Wstack-protector)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WSTRICT_ALIASING "-Wstrict-aliasing=2")
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WSTRICT_OVERFLOW "-Wstrict-overflow=5")
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WDISABLED_OPTIMIZATION -Wdisabled-optimization)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WINLINE -Winline)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WRETURN_TYPE -Wreturn-type)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WCAST_ALIGN -Wcast-align)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WCAST_QUAL -Wcast-qual)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WSIGN_COMPARE -Wsign-compare)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WSIGN_PROMO -Wsign-promo)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WFORMAT "-Wformat=2")
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WFORMAT_NONLITERAL -Wformat-nonliteral)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WFORMAT_SECURITY -Wformat-security)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WFORMAT_Y2K -Wformat-y2k)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WMISSING_BRACES -Wmissing-braces)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WMISSING_FIELD_INITIALIZERS -Wmissing-field-initializers)
#cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WMISSING_INCLUDE_DIRS -Wmissing-include-dirs)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WOVERLOADED_VIRTUAL -Woverloaded-virtual)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WCHAR_SUBSCRIPTS -Wchar-subscripts)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WFLOAT_EQUAL -Wfloat-equal)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WPOINTER_ARITH -Wpointer-arith)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WINVALID_PCH -Winvalid-pch)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WIMPORT -Wimport)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WINIT_SELF -Winit-self)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WREDUNDANT_DECLS -Wredundant-decls)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WPACKED -Wpacked)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WPARENTHESES -Wparentheses)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WSEQUENCE_POINT -Wsequence-point)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WSWITCH -Wswitch)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WSWITCH_DEFAULT -Wswitch-default)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WTRIGRAPHS -Wtrigraphs)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WUNINITIALIZED -Wuninitialized)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WUNKNOWN_PRAGMAS -Wunknown-pragmas)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WUNREACHABLE_CODE -Wunreachable-code)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WVARIADIC_MACROS -Wvariadic-macros)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WVOLATILE_REGISTER_VAR -Wvolatile-register-var)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WWRITE_STRINGS -Wwrite-strings)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WNO_ATTRIBUTES -Wno-attributes)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WUNNEEDED_INTERNAL_DECLARATION -Wunneeded-internal-declaration)

# Template diagnostic flags
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_FDIAGNOSTIC_SHOW_TEMPLATE_TREE -fdiagnostics-show-template-tree)
cpp17playground_append_flag(CPP17PLAYGROUND_HAS_FTEMPLATE_BACKTRACE_LIMIT "-ftemplate-backtrace-limit=0")
cpp17playground_append_flag(CPP17PLAYGROUND_HAS___EXTERN_ALWAYS_INLINE -D__extern_always_inline=inline)

# Compiler flags controlled by CMake options above
if (CPP17PLAYGROUND_ENABLE_WERROR)
    cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WERROR -Werror)
    cpp17playground_append_flag(CPP17PLAYGROUND_HAS_WX -WX)
  endif()

if (CPP17PLAYGROUND_ENABLE_ASAN)
  cpp17playground_append_flag(CPP17PLAYGROUND_HAS_SANITIZE "-fsanitize=address,integer,undefined,leak")
  cpp17playground_append_flag(CPP17PLAYGROUND_HAS_NO_OMIT_FRAME_POINTER -fno-omit-frame-pointer)
  cpp17playground_append_flag(CPP17PLAYGROUND_HAS_NO_SANITIZE "-fno-sanitize=unsigned-integer-overflow")
else()
  cpp17playground_append_flag(CPP17PLAYGROUND_HAS_OMIT_FRAME_POINTER -fomit-frame-pointer)
endif()

if (CPP17PLAYGROUND_ENABLE_DEBUG_INFORMATION)
  cpp17playground_append_flag(CPP17PLAYGROUND_HAS_G3 -g3)
else()
  cpp17playground_append_flag(CPP17PLAYGROUND_HAS_G0 -g0)
endif()

if (NOT CPP17PLAYGROUND_ENABLE_ASSERTIONS)
  cpp17playground_append_flag(CPP17PLAYGROUND_HAS_NDEBUG -DNDEBUG)
endif()

if (CPP17PLAYGROUND_ENABLE_COVERAGE)
  if (CMAKE_BUILD_TYPE STREQUAL "Release")
    message(FATAL_ERROR "code coverage instrumentation requires CMAKE_BUILD_TYPE=Debug")
  endif()
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
endif()

# Optimization flags: debug
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  cpp17playground_append_flag(CPP17PLAYGROUND_HAS_O0 -O0)
  cpp17playground_append_flag(CPP17PLAYGROUND_HAS_NO_INLINE -fno-inline)
  cpp17playground_append_flag(CPP17PLAYGROUND_HAS_STACK_PROTECTOR_ALL -fstack-protector-all)
endif()

# Optimization flags: release
if (CMAKE_BUILD_TYPE STREQUAL "Release")
  cpp17playground_append_flag(CPP17PLAYGROUND_HAS_OFAST -Ofast)
  cpp17playground_append_flag(CPP17PLAYGROUND_HAS_MARCH_NATIVE "-march=native")
  cpp17playground_append_flag(CPP17PLAYGROUND_HAS_MTUNE_NATIVE "-mtune=native")
  cpp17playground_append_flag(CPP17PLAYGROUND_HAS_STRICT_ALIASING "-fstrict-aliasing")
  cpp17playground_append_flag(CPP17PLAYGROUND_HAS_VECTORIZE "-fvectorize")
  # Others could be: -pipe pfdata-sections -ffunction-sections
  # for clang: -mllvm -inline-threshold=X (X=1000, 10000, ...)
endif()

##############################################################################
# Search for packages.
#
# Behavior when the package is found or not is customized at the
# point where the package is required.
##############################################################################

# Git: parses current project commit
find_package(Git)
if (GIT_FOUND)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
    OUTPUT_VARIABLE CPP17PLAYGROUND_CURRENT_COMMIT
    OUTPUT_STRIP_TRAILING_WHITESPACE
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()

# Doxygen
find_package(Doxygen)

# Valgrid
if (CPP17PLAYGROUND_ENABLE_VALGRIND)
  find_program(MEMORYCHECK_COMMAND valgrind)
  if(MEMORYCHECK_COMMAND-NOTFOUND)
    message(FATAL_ERROR "valgrind not found")
  endif()
  set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full")
  include(Dart)
endif()

find_package(Boost)

# find_package(Meta)
# find_package(MPL11)
# find_package(PythonInterp 2.7)
# find_package(Ruby 2.1)


if (NOT ${Boost_FOUND})
    message(WARNING
        "The Boost library headers were not found; targets depending "
        "on Boost won't be available.")
endif()



##############################################################################
# Setup the URL to the official repository on GitHub.
#
# If there is a GITHUB_TOKEN environment variable, we assume this token allows
# us to push to the GitHub repository and we use that in the URL. This token
# will give us push access for updating the 'gh-pages' branch and doing other
# useful things e.g. from Travis. Otherwise, if there's no such environment
# variable, the URL just refers to the GitHub repository without authentication.
# In this case, we'll be asked for our username and password when/if we try to
# push to the repository.
##############################################################################
#if (DEFINED ENV{GITHUB_TOKEN})
#  set(CPP17PLAYGROUND_ORIGIN_URL "https://github_user:$ENV{GITHUB_TOKEN}@github.com/github_user/cpp17playground")
#else()
#  set(CPP17PLAYGROUND_ORIGIN_URL "https://github.com/github_user/cpp17playground")
#endif()

if (DEFINED ENV{GITHUB_TOKEN})
  set(CPP17PLAYGROUND_ORIGIN_URL "https://tivek:$ENV{GITHUB_TOKEN}@github.com/tivek/cpp17playground")
else()
  set(CPP17PLAYGROUND_ORIGIN_URL "https://github.com/tivek/cpp17playground")
endif()


##############################################################################
# Setup custom functions to ease the creation of targets
##############################################################################
#   cpp17playground_target_name_for(<output variable> <source file> [ext])
#
# Return the target name associated to a source file. If the path of the
# source file relative from the root of cpp17playground is `path/to/source/file.ext`,
# the target name associated to it will be `path.to.source.file`.
#
# The extension of the file should be specified as a last argument. If no
# extension is specified, the `.cpp` extension is assumed.
function(cpp17playground_target_name_for out file)
    if (NOT ARGV2)
        set(_extension ".cpp")
    else()
        set(_extension "${ARGV2}")
    endif()

    file(RELATIVE_PATH _relative ${cpp17playground_SOURCE_DIR} ${file})
    string(REPLACE "${_extension}" "" _name ${_relative})
    string(REGEX REPLACE "/" "." _name ${_name})
    set(${out} "${_name}" PARENT_SCOPE)
endfunction()

#   cpp17playground_add_test(<name> <command> [<arg>...])
#
# Creates a test called `name`, which runs the given `command` with the given
# `arg`uments.
function(cpp17playground_add_test name)
  add_test(${name} ${ARGN})
endfunction()

#   cpp17playground_list_remove_glob(<list> <GLOB|GLOB_RECURSE> [globbing expressions]...)
#
# Generates a list of files matching the given glob expressions, and remove
# the matched elements from the given <list>.
macro(cpp17playground_list_remove_glob list glob)
    file(${glob} _bhlrg10321023_avoid_macro_clash_matches ${ARGN})
    list(REMOVE_ITEM ${list} ${_bhlrg10321023_avoid_macro_clash_matches})
endmacro()


##############################################################################
# Setup subdirectories
##############################################################################
#add_subdirectory(benchmark)
add_subdirectory(site)
add_subdirectory(example)
add_subdirectory(test)


##############################################################################
# Setup the `check` target to build and then run all the tests and examples.
##############################################################################
add_custom_target(check ALL
    COMMAND ${CMAKE_CTEST_COMMAND} --VV #--output-on-failure
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS tests examples
    COMMENT "Build and then run all the tests and examples.")

