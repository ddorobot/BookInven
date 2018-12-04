# CMake generated Testfile for 
# Source directory: C:/work/BookInven/lib/opencv_contrib/modules/ximgproc
# Build directory: C:/work/BookInven/lib/opencv_mybuild/modules/ximgproc
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(opencv_test_ximgproc "C:/work/BookInven/lib/opencv_mybuild/bin/Debug/opencv_test_ximgprocd.exe" "--gtest_output=xml:opencv_test_ximgproc.xml")
  set_tests_properties(opencv_test_ximgproc PROPERTIES  LABELS "Extra;opencv_ximgproc;Accuracy" WORKING_DIRECTORY "C:/work/BookInven/lib/opencv_mybuild/test-reports/accuracy")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(opencv_test_ximgproc "C:/work/BookInven/lib/opencv_mybuild/bin/Release/opencv_test_ximgproc.exe" "--gtest_output=xml:opencv_test_ximgproc.xml")
  set_tests_properties(opencv_test_ximgproc PROPERTIES  LABELS "Extra;opencv_ximgproc;Accuracy" WORKING_DIRECTORY "C:/work/BookInven/lib/opencv_mybuild/test-reports/accuracy")
else()
  add_test(opencv_test_ximgproc NOT_AVAILABLE)
endif()
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(opencv_perf_ximgproc "C:/work/BookInven/lib/opencv_mybuild/bin/Debug/opencv_perf_ximgprocd.exe" "--gtest_output=xml:opencv_perf_ximgproc.xml")
  set_tests_properties(opencv_perf_ximgproc PROPERTIES  LABELS "Extra;opencv_ximgproc;Performance" WORKING_DIRECTORY "C:/work/BookInven/lib/opencv_mybuild/test-reports/performance")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(opencv_perf_ximgproc "C:/work/BookInven/lib/opencv_mybuild/bin/Release/opencv_perf_ximgproc.exe" "--gtest_output=xml:opencv_perf_ximgproc.xml")
  set_tests_properties(opencv_perf_ximgproc PROPERTIES  LABELS "Extra;opencv_ximgproc;Performance" WORKING_DIRECTORY "C:/work/BookInven/lib/opencv_mybuild/test-reports/performance")
else()
  add_test(opencv_perf_ximgproc NOT_AVAILABLE)
endif()
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(opencv_sanity_ximgproc "C:/work/BookInven/lib/opencv_mybuild/bin/Debug/opencv_perf_ximgprocd.exe" "--gtest_output=xml:opencv_perf_ximgproc.xml" "--perf_min_samples=1" "--perf_force_samples=1" "--perf_verify_sanity")
  set_tests_properties(opencv_sanity_ximgproc PROPERTIES  LABELS "Extra;opencv_ximgproc;Sanity" WORKING_DIRECTORY "C:/work/BookInven/lib/opencv_mybuild/test-reports/sanity")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(opencv_sanity_ximgproc "C:/work/BookInven/lib/opencv_mybuild/bin/Release/opencv_perf_ximgproc.exe" "--gtest_output=xml:opencv_perf_ximgproc.xml" "--perf_min_samples=1" "--perf_force_samples=1" "--perf_verify_sanity")
  set_tests_properties(opencv_sanity_ximgproc PROPERTIES  LABELS "Extra;opencv_ximgproc;Sanity" WORKING_DIRECTORY "C:/work/BookInven/lib/opencv_mybuild/test-reports/sanity")
else()
  add_test(opencv_sanity_ximgproc NOT_AVAILABLE)
endif()
