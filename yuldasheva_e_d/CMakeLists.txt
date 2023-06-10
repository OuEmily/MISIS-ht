cmake_minimum_required(VERSION 3.18)   

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

set(CMAKE_VERBOSE_MAKEFILE True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True) 


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin.dbg)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin.rel)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/bin.relwithdbg)

project(cpp2023_test)

find_package(doctest REQUIRED)
#find_package(Doxygen REQUIRED)
find_package( OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(prj.lab)
add_subdirectory(prj.test)
add_subdirectory(prj.cw)

install(TARGETS ssim_test RUNTIME
  DESTINATION bin
)



#target_include_directories(prj.cw/images PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

#install(FILES prj.cw/images/images.png prj.cw/images/images22.png DESTINATION data/image)
#file(COPY prj.cw/images/images.png prj.cw/images/images22.png DESTINATION ${CMAKE_CURRENT_DIR}/images)
#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/prj.cw/images/images.png ${CMAKE_CURRENT_SOURCE_DIR}/prj.cw/images/images22.png  DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/data/
  DESTINATION data
)

if(WIN32)
    set(OpenCV_RUNTIME_PATH "${OpenCV_DIR}/../../bin")
else()
    set(OpenCV_RUNTIME_PATH "${OpenCV_DIR}/../../lib")
endif()

install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
  DESTINATION bin
  FILES_MATCHING PATTERN "*zlib*"
)
install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
  DESTINATION bin
  FILES_MATCHING PATTERN "*tiff*"
)
install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
  DESTINATION bin
  FILES_MATCHING PATTERN "*opencv_videoio*"
)
install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
  DESTINATION bin
  FILES_MATCHING PATTERN "*opencv_imgproc*"
)
install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
  DESTINATION bin
  FILES_MATCHING PATTERN "*opencv_imgcodecs*"
)
install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
  DESTINATION bin
  FILES_MATCHING PATTERN "*opencv_highgui*"
)
install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
  DESTINATION bin
  FILES_MATCHING PATTERN "*opencv_core*"
)
install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
  DESTINATION bin
  FILES_MATCHING PATTERN "*libwebpdecoder*"
)
install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
  DESTINATION bin
  FILES_MATCHING PATTERN "*libsharpyuv*"
)
install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
  DESTINATION bin
  FILES_MATCHING PATTERN "*libpng*"
)
install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
  DESTINATION bin
  FILES_MATCHING PATTERN "*liblzma*"
)
install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
  DESTINATION bin
  FILES_MATCHING PATTERN "*jpeg*"
)
install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
  DESTINATION bin
  FILES_MATCHING PATTERN "*libwebp*"
)

find_package(Doxygen REQUIRED)



if(DOXYGEN_FOUND)
       set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/prj.cw/ssim/include/ssim/Doxyfile)
       set(DOXYGEN_CONFIGURED_INPUT ${DOXYGEN_IN})

       add_custom_target(doc ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIGURED_INPUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM
       )
endif()

if(DOXYGEN_FOUND)
       install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doxyden
               DESTINATION docs)
   endif()

