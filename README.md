# CryLevelConvert [![Build status](https://ci.appveyor.com/api/projects/status/2x0bqxnnc9vugvuq?svg=true)](https://ci.appveyor.com/project/prophetl33t/crylevelconvert)
Tool for conversion of level.pak files from Cryengine game engine to format readable by Cryengine Sandbox.
CE 3 is supported (tested on 3.1 - 3.4.x), CE 5 support is in development.

## What is convertible?
mission_mission0.xml -> .lyr files containing level Flow Graph and dynamic entities  
mission_mission0.xml -> .tod file containing Time Of Day data  
moviedata.xml -> .lyr containing Track View info  
leveldata.xml -> .lay containing terrain layers info  
Other data is not available, but this may change in future  

### How to use this tool?
Just place .xml files from level.pak in folder of CLC and run it. 
Drag-and-drop for level.pak and .xml files is also available.  
It is recommended to place EntityArchetypes folder in working directory of CLC for better conversion.  

#### Libraries used:
XML parser:  
pugixml github.com/zeux/pugixml  
Interactions with .pak files:  
miniz-cpp github.com/tfussell/miniz-cpp  
