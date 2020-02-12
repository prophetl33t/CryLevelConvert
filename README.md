# CryLevelConvert
Tool for conversion of level.pak files from Cryengine 3 game engine to format readable by Cryengine 3 Sandbox

## What is convertible?
mission_mission0.xml -> .lyr files containing level Flow Graph and dynamic entities
mission_mission0.xml -> .tod file containing Time Of Day data
moviedata.xml -> .lyr containing Track View info
leveldata.xml -> .lay containing terrain layers info

Other data is not available through this tool, but it may change in future

### How to use this tool?
Just place .xml files in folder of CLC and run it. 
Drag-and-drop for level.pak and .xml files is also available.
It is recommended to place EntityArchetypes folder in folder of CLC for better conversion.

#### Libraries used:
XML parser:
pugixml github.com/zeux/pugixml
Interactions with .pak files:
miniz-cpp github.com/tfussell/miniz-cpp



