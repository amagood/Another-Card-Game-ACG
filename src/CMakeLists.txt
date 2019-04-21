project(src)
include_directories(../lib)

add_library(ACGMain ACGMain.cpp Printer.cpp Reader.cpp AccountSystem.cpp Router.cpp )