#--------------------------------------------------------------------------
# Lab1 project
#--------------------------------------------------------------------------

PROJECT(Lab1)
FIND_PACKAGE(Threads)
FILE(GLOB lab1_headers code/*.h)
FILE(GLOB lab1_sources code/*.cc)

SET(files_lab1 ${lab1_headers} ${lab1_sources})
SOURCE_GROUP("lab1" FILES ${files_lab1})

ADD_EXECUTABLE(Lab1 ${files_lab1})
TARGET_LINK_LIBRARIES( Lab1 ${CMAKE_THREAD_LIBS_INIT})