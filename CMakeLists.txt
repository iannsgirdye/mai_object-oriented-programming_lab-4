cmake_minimum_required(VERSION 3.14)
project(FiguresProject VERSION 1.0.0 LANGUAGES CXX)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Найти Google Test
find_package(GTest REQUIRED)

# Создание исполняемого файла для основной программы
add_executable(main main.cpp)

# Установка путей к заголовочным файлам
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Установка свойств компиляции
target_compile_features(main PRIVATE cxx_std_20)

# Создание исполняемого файла для тестов
add_executable(tests tests.cpp)

# Установка путей к заголовочным файлам для тестов
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Линковка с Google Test
target_link_libraries(tests PRIVATE GTest::gtest GTest::gtest_main)

# Установка свойств компиляции для тестов
target_compile_features(tests PRIVATE cxx_std_20)

# Включить тестирование
enable_testing()

# Добавить тесты
add_test(NAME AllTests COMMAND tests)
