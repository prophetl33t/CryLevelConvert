# CryLevelConvert

[![CMake](https://github.com/prophetl33t/CryLevelConvert/actions/workflows/cmake.yml/badge.svg?branch=master)](https://github.com/prophetl33t/CryLevelConvert/actions/workflows/cmake.yml)


Tool for conversion of level.pak files from Cryengine 3 game engine to format readable by Cryengine 3 Sandbox  

Download latest stable windows binary at
https://github.com/prophetl33t/CryLevelConvert/releases/download/latest/CryLevelConvert.exe

## What is convertible?
mission_mission0.xml -> .lyr files containing level Flow Graph and dynamic entities  
mission_mission0.xml -> .tod file containing Time Of Day data  
moviedata.xml -> .lyr containing Track View info  
leveldata.xml -> .lay containing terrain layers info  

### How to use this tool?
Just place .xml files in folder of CLC and run it. 
Drag-and-drop for level.pak and .xml files is also available.  
It is recommended to place EntityArchetypes folder in working directory of CLC for better conversion.

#### Compiling CLC

1)Clone repo and init submodules
```shell
git clone --recursive https://github.com/prophetl33t/CryLevelConvert.git
git submodule update --init --recursive
```

2)Create project file for your build system/IDE by using shell or cmake-gui.
  Run configure step two times for correct zlib static link params.
```shell
cmake -S <path-to-source> -B <path-to-build>
cmake -S <path-to-source> -B <path-to-build>
```

#### Libraries used:
XML parser:  
pugixml https://github.com/zeux/pugixml  
Interactions with .pak files:  
zipper https://github.com/sebastiandev/zipper
