# 测试目录的CMakeLists.txt

# 查找所有测试源文件
file(GLOB TEST_SOURCES "*_test.cpp" "*_test.cc" "test_*.cpp" "test_*.cc")

# 查找Google Test
find_package(PkgConfig QUIET)
if(PKG_CONFIG_FOUND)
    pkg_check_modules(GTEST gtest gmock)
endif()

# 如果pkg-config找不到gtest，尝试find_package
if(NOT GTEST_FOUND)
    find_package(GTest QUIET)
    if(GTest_FOUND)
        set(GTEST_LIBRARIES GTest::GTest GTest::Main)
        set(GMOCK_LIBRARIES GTest::GMock)
    endif()
endif()

if(TEST_SOURCES)
    # 创建测试可执行文件
    add_executable(unit_tests ${TEST_SOURCES})

    if(GTEST_LIBRARIES)
        # 链接Google Test库
        target_link_libraries(unit_tests 
            common
            ${GTEST_LIBRARIES}
            ${GMOCK_LIBRARIES}
        )
    else()
        # 手动查找并链接gtest
        find_package(Threads REQUIRED)
        target_link_libraries(unit_tests 
            common 
            gtest 
            gtest_main 
            pthread
        )
    endif()

    # 添加测试
    add_test(NAME unit_tests COMMAND unit_tests)
endif()

# 如果没有通过pkg-config找到gtest，则手动查找安装路径
if(NOT GTEST_FOUND)
    # 寻找gtest头文件
    find_path(GTEST_INCLUDE_DIRS gtest/gtest.h
        PATHS /usr/include /usr/local/include /opt/gtest/include)

    # 寻找gtest库文件
    find_library(GTEST_LIBRARY gtest
        PATHS /usr/lib /usr/local/lib /opt/gtest/lib)
    find_library(GTEST_MAIN_LIBRARY gtest_main
        PATHS /usr/lib /usr/local/lib /opt/gtest/lib)
    find_library(GMOCK_LIBRARY gmock
        PATHS /usr/lib /usr/local/lib /opt/gtest/lib)

    if(GTEST_LIBRARY AND GTEST_MAIN_LIBRARY AND GMOCK_LIBRARY AND GTEST_INCLUDE_DIRS)
        add_executable(unit_tests ${TEST_SOURCES})
        target_include_directories(unit_tests PRIVATE ${GTEST_INCLUDE_DIRS})
        target_link_libraries(unit_tests 
            common
            ${GTEST_LIBRARY}
            ${GTEST_MAIN_LIBRARY}
            ${GMOCK_LIBRARY}
            pthread  # gtest需要pthread
        )
        add_test(NAME unit_tests COMMAND unit_tests)
    endif()
endif()