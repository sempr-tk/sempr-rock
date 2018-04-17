rock_library(sempr
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp)

rock_executable(sempr_bin Main.cpp
    DEPS sempr)

