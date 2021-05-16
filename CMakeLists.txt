cmake_minimum_required(VERSION 3.20)
project(CryLevelConvert)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS -pthread)

include_directories(3rdParty/pugixml/src)
include_directories(Converters)
include_directories(Converters/CustomFormat)
include_directories(Converters/XML)
include_directories(Utils)
include_directories(3rdParty/zipper)

add_executable(CryLevelConvert
        3rdParty/pugixml/src/pugiconfig.hpp
        3rdParty/pugixml/src/pugixml.cpp
        3rdParty/pugixml/src/pugixml.hpp
        Converters/CustomFormat/CustomFormatConverter.cpp
        Converters/CustomFormat/CustomFormatConverter.h
        Converters/CustomFormat/VegetationDumpConvert.cpp
        Converters/CustomFormat/VegetationDumpConvert.h
        Converters/XML/MissionConvert.cpp
        Converters/XML/MissionConvert.h
        Converters/XML/MovieDataConvert.cpp
        Converters/XML/MovieDataConvert.h
        Converters/XML/TerrainLayerInfoConvert.cpp
        Converters/XML/TerrainLayerInfoConvert.h
        Converters/XML/Converter.cpp
        Converters/XML/Converter.h
        Converters/XML/EntArchetypeObtainer.cpp
        Converters/XML/EntArchetypeObtainer.h
        Utils/CLCHeaders.h
        Utils/CryVersionDetect.cpp
        Utils/CryVersionDetect.h
        Utils/Util.cpp
        Utils/Util.h
        main.cpp)
				
option(USE_PAK_INTERACTION "Activate support of .pak files." ON)

if (USE_PAK_INTERACTION)
add_compile_definitions(USE_PAK_INTERACTION)
option(BUILD_TEST "Build the test program." OFF)
option(BUILD_SHARED_VERSION "Build the shared version of the library." OFF)
add_subdirectory(3rdParty/zipper)
target_link_libraries(CryLevelConvert staticZipper)
endif()

file(GLOB_RECURSE _source_list *.cpp* *.h* *.hpp*)
foreach(_source IN ITEMS ${_source_list})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "${CMAKE_SOURCE_DIR}" "" _group_path "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_group_path}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()