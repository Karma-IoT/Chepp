project (Chepp)
cmake_minimum_required(VERSION 3.1)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/dependencies)

add_compile_options(-std=c++17)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/ecode)

add_executable(chepp ${SRC_DIR}/chepp/main.cpp
                     ${SRC_DIR}/utils.cpp)
target_link_libraries(chepp -lstdc++fs)

#add_executable(new ${SRC_DIR}/commands/new/main.cpp
#                   ${SRC_DIR}/utils.cpp)
#target_link_libraries(new -lstdc++fs ecode)

add_executable(init ${SRC_DIR}/commands/init/main.cpp
                   ${SRC_DIR}/utils.cpp)
target_link_libraries(init -lstdc++fs)

add_executable(pro ${SRC_DIR}/commands/new/types/pro.cpp
                   ${SRC_DIR}/utils.cpp)
target_link_libraries(pro -lstdc++fs ecode)

add_executable(src ${SRC_DIR}/commands/new/types/src.cpp
                   ${SRC_DIR}/utils.cpp
                   ${SRC_DIR}/chest.cpp)
target_link_libraries(src -lstdc++fs ecode)


install(TARGETS chepp DESTINATION $ENV{CHEST_SYSROOT}/bin)
install(TARGETS new DESTINATION $ENV{CHEST_SYSROOT}/bin/.chest/commands)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/etc/templates DESTINATION $ENV{CHEST_SYSROOT}/etc/chest)
install(TARGETS pro DESTINATION $ENV{CHEST_SYSROOT}/bin/.chest/commands/new_types)
install(TARGETS src DESTINATION $ENV{CHEST_SYSROOT}/bin/.chest/commands/new_types)

install(TARGETS init DESTINATION $ENV{CHEST_SYSROOT}/bin/.chest/commands)

