cmake_minimum_required(VERSION 3.2)

add_executable(test_version_gtest test_version_gtest.cpp)

# включаем 14 стандарт для наших целей
set_target_properties(test_version_gtest PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

# подключим инклуды из основного каталога проекта
target_include_directories(test_version_gtest
    PRIVATE "${PROJECT_SOURCE_DIR}/src"
)

target_include_directories(test_version_gtest
    PRIVATE ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(test_version_gtest
    ${GTEST_BOTH_LIBRARIES}
    Threads::Threads
    helloworld
)

# максимально строгие настройки компилятора
if (MSVC)
    target_compile_options(test_version_gtest PRIVATE
        /W4
    )
else ()
    target_compile_options(test_version_gtest PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

add_test(test_version_gtest test_version_gtest)
