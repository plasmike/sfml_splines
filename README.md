# Messing around with splines in SFML

## Catmull-Rom spline
## Controls:
- press Ctrl + S to save the spline as csv 
- press Ctrl + O to open a spline from a csv file
- Left click on a point to drag it around
- Left click on nothing to create a new point
- Right click on a point to delete it

## How to build:
(Replace "release" with "debug" for debug builds)
(Might have to add --build=missing to conan install)
### On mac:
1. conan install . -s build_type=Release
2. cmake --preset conan-release
3. cmake --build --preset conan-release

### On Windows:
1. conan install . -s build_type=Release
2. .\build\Release\generators\conanvcvars.ps1
3. cmake --preset conan-release
3. cmake --build --preset conan-release
