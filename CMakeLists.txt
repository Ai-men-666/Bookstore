cmake_minimum_required(VERSION 3.22)
project(mybookstore)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
add_executable(code ${SOURCES}
    main.cpp
        entrystack.hpp
        entrystack.cpp
        store.hpp
        scanner.h
        account_manager.hpp
        account_manager.cpp
        book.cpp
        book.h
        log.h
        account.cpp
        account.hpp
        book_manager.h
        bookManager.cpp
        finance.h
        finance.cpp
        finance.cpp
)
