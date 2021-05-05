cmake_minimum_required(VERSION 3.19)
project(CryLevelConvert)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 17)

include_directories(3rdParty/pugixml-master/src)
include_directories(3rdParty/Zippy)
include_directories(3rdParty/Zippy/Zippy)
include_directories(3rdParty/Zippy/Zippy/miniz)
include_directories(Converters)
include_directories(Converters/CustomFormat)
include_directories(Converters/XML)
include_directories(Utils)

add_executable(CryLevelConvert
        3rdParty/pugixml-master/src/pugiconfig.hpp
        3rdParty/pugixml-master/src/pugixml.cpp
        3rdParty/pugixml-master/src/pugixml.hpp
        3rdParty/Zippy/Zippy/miniz/miniz.h
        3rdParty/Zippy/Zippy/ZipArchive.hpp
        3rdParty/Zippy/Zippy/ZipEntry.hpp
        3rdParty/Zippy/Zippy/ZipException.hpp
        3rdParty/Zippy/Zippy/ZipUtilities.hpp
        3rdParty/Zippy/Zippy.hpp
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

file(GLOB_RECURSE _source_list *.cpp* *.h* *.hpp*)
foreach(_source IN ITEMS ${_source_list})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "${CMAKE_SOURCE_DIR}" "" _group_path "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_group_path}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()
