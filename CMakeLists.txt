# Wymagana minimalna wersja CMake
cmake_minimum_required(VERSION 3.10)

# Nazwa projektu
project(B01_Project VERSION 1.0 LANGUAGES CXX)

# Ustawienie standardu C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ścieżki do katalogów
include_directories(include)

# Zbieranie wszystkich plików źródłowych (*.cpp) z folderu source/
file(GLOB SOURCES "source/*.cpp")

# Tworzenie pliku wykonywalnego
add_executable(B01_app ${SOURCES})

# Ustawienie folderu na wyjściowy binarny plik w katalogu build
set_target_properties(B01_app PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Dodatkowe opcje kompilacji (ostrzeżenia i błędy)
if(MSVC)
    target_compile_options(B01_app PRIVATE /W4)
else()
    target_compile_options(B01_app PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# Informacja o zakończeniu konfiguracji
message(STATUS "Konfiguracja CMake zakończona dla projektu B01")
