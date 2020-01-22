cmake_minimum_required(VERSION 3.2)

add_executable(test_ip_filter   test_ip_filter.cpp
                                ${PROJECT_SOURCE_DIR}/src/Parser.cpp
                                ${PROJECT_SOURCE_DIR}/src/IpAddr.cpp)

# включаем 14 стандарт для наших целей
set_target_properties(test_ip_filter PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

# подключим инклуды из основного каталога проекта
target_include_directories(test_ip_filter
    PRIVATE "${PROJECT_SOURCE_DIR}/src"
)

target_include_directories(test_ip_filter
    PRIVATE ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(test_ip_filter
    ${GTEST_BOTH_LIBRARIES}
    Threads::Threads
)

# максимально строгие настройки компилятора
if (MSVC)
    target_compile_options(test_ip_filter PRIVATE
        /W4
    )
else ()
    target_compile_options(test_ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

add_test(test_ip_filter test_ip_filter)
