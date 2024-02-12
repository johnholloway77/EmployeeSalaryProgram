cmake_minimum_required(VERSION 3.5)

project(Assign2 LANGUAGES C)

find_package(Curses REQUIRED)

add_executable(Assign2 main.c
    headers.h
    models/employee.h
    models/employeeSalary.h
    services/fileLoader.h
    services/fileLoader.c
    services/lookup.h
    services/lookup.c
    services/salary.h
    services/salary.c
    services/close.h
    services/close.c
    services/validFileName.c
    services/validFileName.h
)
target_link_libraries(Assign2 PRIVATE ${CURSES_LIBRARIES} m)

include(GNUInstallDirs)
install(TARGETS Assign2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
