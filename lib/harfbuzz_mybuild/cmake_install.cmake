# Install script for directory: C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/harfbuzz")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/harfbuzz" TYPE FILE FILES
    "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz/src/hb-aat-layout.h"
    "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz/src/hb-aat.h"
    "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz/src/hb-blob.h"
    "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz/src/hb-buffer.h"
    "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz/src/hb-common.h"
    "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz/src/hb-deprecated.h"
    "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz/src/hb-face.h"
    "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz/src/hb-font.h"
    "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz/src/hb-map.h"
    "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz/src/hb-ot-color.h"
    "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz/src/hb-ot-deprecated.h"
    "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz/src/hb-ot-font.h"
    "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz/src/hb-ot-layout.h"
    "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz/src/hb-ot-math.h"
    "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz/src/hb-ot-name.h"
    "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz/src/hb-ot-shape.h"
    "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz/src/hb-ot-var.h"
    "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz/src/hb-ot.h"
    "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz/src/hb-set.h"
    "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz/src/hb-shape-plan.h"
    "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz/src/hb-shape.h"
    "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz/src/hb-unicode.h"
    "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz/src/hb-version.h"
    "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz/src/hb.h"
    "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz/src/hb-ft.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz_mybuild/Debug/harfbuzz.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz_mybuild/Release/harfbuzz.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz_mybuild/MinSizeRel/harfbuzz.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz_mybuild/RelWithDebInfo/harfbuzz.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/harfbuzz/harfbuzzConfig.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/harfbuzz/harfbuzzConfig.cmake"
         "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz_mybuild/CMakeFiles/Export/lib/cmake/harfbuzz/harfbuzzConfig.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/harfbuzz/harfbuzzConfig-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/harfbuzz/harfbuzzConfig.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/harfbuzz" TYPE FILE FILES "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz_mybuild/CMakeFiles/Export/lib/cmake/harfbuzz/harfbuzzConfig.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/harfbuzz" TYPE FILE FILES "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz_mybuild/CMakeFiles/Export/lib/cmake/harfbuzz/harfbuzzConfig-debug.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/harfbuzz" TYPE FILE FILES "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz_mybuild/CMakeFiles/Export/lib/cmake/harfbuzz/harfbuzzConfig-minsizerel.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/harfbuzz" TYPE FILE FILES "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz_mybuild/CMakeFiles/Export/lib/cmake/harfbuzz/harfbuzzConfig-relwithdebinfo.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/harfbuzz" TYPE FILE FILES "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz_mybuild/CMakeFiles/Export/lib/cmake/harfbuzz/harfbuzzConfig-release.cmake")
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz_mybuild/test/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/박주홍/Desktop/BookInven/lib/harfbuzz_mybuild/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
