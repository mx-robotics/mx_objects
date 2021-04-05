enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(tests foo_test.cpp)
target_link_libraries(tests GTest::GTest GTest::Main)
gtest_discover_tests(tests)
