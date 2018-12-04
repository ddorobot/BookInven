# CMake generated Testfile for 
# Source directory: C:/work/BookInven/lib/opencv_contrib/modules/structured_light
# Build directory: C:/work/BookInven/lib/opencv_mybuild/modules/structured_light
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(opencv_test_structured_light "C:/work/BookInven/lib/opencv_mybuild/bin/Debug/opencv_test_structured_lightd.exe" "--gtest_output=xml:opencv_test_structured_light.xml")
  set_tests_properties(opencv_test_structured_light PROPERTIES  LABELS "Extra;opencv_structured_light;Accuracy" WORKING_DIRECTORY "C:/work/BookInven/lib/opencv_mybuild/test-reports/accuracy")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(opencv_test_structured_light "C:/work/BookInven/lib/opencv_mybuild/bin/Release/opencv_test_structured_light.exe" "--gtest_output=xml:opencv_test_structured_light.xml")
  set_tests_properties(opencv_test_structured_light PROPERTIES  LABELS "Extra;opencv_structured_light;Accuracy" WORKING_DIRECTORY "C:/work/BookInven/lib/opencv_mybuild/test-reports/accuracy")
else()
  add_test(opencv_test_structured_light NOT_AVAILABLE)
endif()
