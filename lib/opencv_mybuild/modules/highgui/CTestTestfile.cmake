# CMake generated Testfile for 
# Source directory: C:/work/BookInven/lib/opencv/modules/highgui
# Build directory: C:/work/BookInven/lib/opencv_mybuild/modules/highgui
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(opencv_test_highgui "C:/work/BookInven/lib/opencv_mybuild/bin/Debug/opencv_test_highguid.exe" "--gtest_output=xml:opencv_test_highgui.xml")
  set_tests_properties(opencv_test_highgui PROPERTIES  LABELS "Main;opencv_highgui;Accuracy" WORKING_DIRECTORY "C:/work/BookInven/lib/opencv_mybuild/test-reports/accuracy")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(opencv_test_highgui "C:/work/BookInven/lib/opencv_mybuild/bin/Release/opencv_test_highgui.exe" "--gtest_output=xml:opencv_test_highgui.xml")
  set_tests_properties(opencv_test_highgui PROPERTIES  LABELS "Main;opencv_highgui;Accuracy" WORKING_DIRECTORY "C:/work/BookInven/lib/opencv_mybuild/test-reports/accuracy")
else()
  add_test(opencv_test_highgui NOT_AVAILABLE)
endif()
