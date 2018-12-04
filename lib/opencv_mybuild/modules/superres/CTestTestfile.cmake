# CMake generated Testfile for 
# Source directory: C:/work/BookInven/lib/opencv_contrib/modules/superres
# Build directory: C:/work/BookInven/lib/opencv_mybuild/modules/superres
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(opencv_test_superres "C:/work/BookInven/lib/opencv_mybuild/bin/Debug/opencv_test_superresd.exe" "--gtest_output=xml:opencv_test_superres.xml")
  set_tests_properties(opencv_test_superres PROPERTIES  LABELS "Extra;opencv_superres;Accuracy" WORKING_DIRECTORY "C:/work/BookInven/lib/opencv_mybuild/test-reports/accuracy")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(opencv_test_superres "C:/work/BookInven/lib/opencv_mybuild/bin/Release/opencv_test_superres.exe" "--gtest_output=xml:opencv_test_superres.xml")
  set_tests_properties(opencv_test_superres PROPERTIES  LABELS "Extra;opencv_superres;Accuracy" WORKING_DIRECTORY "C:/work/BookInven/lib/opencv_mybuild/test-reports/accuracy")
else()
  add_test(opencv_test_superres NOT_AVAILABLE)
endif()
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(opencv_perf_superres "C:/work/BookInven/lib/opencv_mybuild/bin/Debug/opencv_perf_superresd.exe" "--gtest_output=xml:opencv_perf_superres.xml")
  set_tests_properties(opencv_perf_superres PROPERTIES  LABELS "Extra;opencv_superres;Performance" WORKING_DIRECTORY "C:/work/BookInven/lib/opencv_mybuild/test-reports/performance")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(opencv_perf_superres "C:/work/BookInven/lib/opencv_mybuild/bin/Release/opencv_perf_superres.exe" "--gtest_output=xml:opencv_perf_superres.xml")
  set_tests_properties(opencv_perf_superres PROPERTIES  LABELS "Extra;opencv_superres;Performance" WORKING_DIRECTORY "C:/work/BookInven/lib/opencv_mybuild/test-reports/performance")
else()
  add_test(opencv_perf_superres NOT_AVAILABLE)
endif()
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(opencv_sanity_superres "C:/work/BookInven/lib/opencv_mybuild/bin/Debug/opencv_perf_superresd.exe" "--gtest_output=xml:opencv_perf_superres.xml" "--perf_min_samples=1" "--perf_force_samples=1" "--perf_verify_sanity")
  set_tests_properties(opencv_sanity_superres PROPERTIES  LABELS "Extra;opencv_superres;Sanity" WORKING_DIRECTORY "C:/work/BookInven/lib/opencv_mybuild/test-reports/sanity")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(opencv_sanity_superres "C:/work/BookInven/lib/opencv_mybuild/bin/Release/opencv_perf_superres.exe" "--gtest_output=xml:opencv_perf_superres.xml" "--perf_min_samples=1" "--perf_force_samples=1" "--perf_verify_sanity")
  set_tests_properties(opencv_sanity_superres PROPERTIES  LABELS "Extra;opencv_superres;Sanity" WORKING_DIRECTORY "C:/work/BookInven/lib/opencv_mybuild/test-reports/sanity")
else()
  add_test(opencv_sanity_superres NOT_AVAILABLE)
endif()
