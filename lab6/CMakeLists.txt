cmake_minimum_required(VERSION 3.10)
project(lab6)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем флаги компиляции для AddressSanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer -g")

# Флаг для компиляции с предупреждением об использовании неинициализированных переменных
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

# Указываем директорию с заголовочными файлами
include_directories(include)

# Добавляем все файлы реализации в проект
set(SOURCES
    src/Npc.cpp
    src/Dragon.cpp
    src/Bull.cpp
    src/Toad.cpp
    src/BattleVisitor.cpp
    src/LoggingVisitor.cpp
    src/NPCFactory.cpp
    src/NPCLoader.cpp
    src/NPCSaver.cpp
)

# Создаём исполняемый файл main
add_executable(main src/main.cpp ${SOURCES})



# Подключаем GoogleTest через FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)

# Устанавливаем флаги для GoogleTest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Включаем поддержку тестов
enable_testing()

# Создаём исполняемый файл для тестов
add_executable(tests tests/tests.cpp ${SOURCES})  # Добавляем исходные файлы из src
target_link_libraries(tests gtest_main)

# Линкуем AddressSanitizer к тестам
set_target_properties(tests PROPERTIES COMPILE_FLAGS "-fsanitize=address -fno-omit-frame-pointer -g")
set_target_properties(tests PROPERTIES LINK_FLAGS "-fsanitize=address")

# Добавляем тесты
add_test(NAME MyProjectTests COMMAND tests)