cmake_minimum_required(VERSION 3.15)
project(3lab)
enable_language(CXX)
add_definitions(-DSFML_STATIC)
add_executable(main main.cpp)
target_include_directories(main PUBLIC include)
target_link_directories(main PUBLIC lib)
target_link_libraries(main
flac
freetype
ogg
gdi32
openal32
opengl32
sfml-audio-s
sfml-graphics-s
sfml-network-s
sfml-system-s
sfml-window-s
vorbis
vorbisenc
vorbisfile
winmm
)