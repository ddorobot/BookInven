# CMake generated Testfile for 
# Source directory: C:/work/BookInven/lib/opencv_contrib/modules/rgbd
# Build directory: C:/work/BookInven/lib/opencv_mybuild/modules/rgbd
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(opencv_test_rgbd "C:/work/BookInven/lib/opencv_mybuild/bin/Debug/opencv_test_rgbdd.exe" "--gtest_output=xml:opencv_test_rgbd.xml")
  set_tests_properties(opencv_test_rgbd PROPERTIES  LABELS "Extra;opencv_rgbd;Accuracy" WORKING_DIRECTORY "C:/work/BookInven/lib/opencv_mybuild/test-reports/accuracy")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(opencv_test_rgbd "C:/work/BookInven/lib/opencv_mybuild/bin/Release/opencv_test_rgbd.exe" "--gtest_output=xml:opencv_test_rgbd.xml")
  set_tests_properties(opencv_test_rgbd PROPERTIES  LABELS "Extra;opencv_rgbd;Accuracy" WORKING_DIRECTORY "C:/work/BookInven/lib/opencv_mybuild/test-reports/accuracy")
else()
  add_test(opencv_test_rgbd NOT_AVAILABLE)
endif()
