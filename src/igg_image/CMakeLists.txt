#################### Import the 'io_tools' library here ########################
find_library(io_tools libio_tools.so PATHS ${CMAKE_SOURCE_DIR}/lib)
if(NOT io_tools)
    message(FATAL_ERROR "libio_tools not found")
endif()
#################### Create a library 'image' below this line ##################
add_library(image image.cpp)

### add executable ####
add_executable(image_main main.cpp)

target_link_libraries(image_main
                        image  
                        ${io_tools})