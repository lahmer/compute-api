cmake_minimum_required(VERSION 3.5)
project(ClioTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#***********************************************************************************************************************
#This part we add the header files directories for the libraries used in this project
#***********************************************************************************************************************
        #add libssh header directories
                INCLUDE_DIRECTORIES(/usr/include)
#***********************************************************************************************************************
#This part is didecated to add the directories of the libraries shared files
#***********************************************************************************************************************
                link_directories(/usr/lib)
                link_directories(/usr/local/lib)


set(SOURCE_FILES
         main.cpp common.h)


add_executable(compute ${SOURCE_FILES} )
TARGET_LINK_LIBRARIES(compute config++ boost_system boost_thread virt pthread crypto ssl)