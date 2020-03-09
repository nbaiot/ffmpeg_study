cmake_minimum_required(VERSION 3.12)

project(ffmpeg_study)

set(CMAKE_CXX_STANDARD 17)

set(THIRD_PARTY_INSTALL_PATH /opt/third_party/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR})
set(THIRD_PARTY_INDEPENDENT_INSTALL FALSE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(cmake/generic.cmake)

# log
include(cmake/external/gflags.cmake)
include(cmake/external/glog.cmake)

# boost
include(cmake/external/boost.cmake)

# ffmpg
include(cmake/external/jpeg.cmake)
include(cmake/external/libyuv.cmake)
include(cmake/external/x264.cmake)
include(cmake/external/x265.cmake)
include(cmake/external/vpx.cmake)
include(cmake/external/lame.cmake)
include(cmake/external/png.cmake)
include(cmake/external/fdk-aac.cmake)
include(cmake/external/opus.cmake)
include(cmake/external/freetype.cmake)
include(cmake/external/ffmpeg.cmake)


include_directories(${CMAKE_CURRENT_LIST_DIR})

if (UNIX)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wl,-Bsymbolic")
endif ()

aux_source_directory(sdk SDK_SRCS)

add_executable(ffmpeg_study main.cpp ${SDK_SRCS})


add_dependencies(ffmpeg_study glog)

set(LOG_LIBS glog gflags)
# TODO: recompile ffmpeg static link these libs
set(FFMPEG_DEP_LIBS freetype png opus lame fdk-aac x264 x265 vpx
                    -lasound  -ldl -lnuma -lva -lvdpau -lva-drm -lva-x11 -lX11 -llzma -lz -lm -lbz2)

target_link_libraries(ffmpeg_study
        ${LOG_LIBS} ${FFMPEG_LIBS} ${FFMPEG_DEP_LIBS}
        pthread)