mkdir build
cd build
conan install .. -s build_type=Release
conan install .. -s build_type=Debug
cmake .. -G "Visual Studio 16 2019"
cmake --build . --config Release
cmake --build . --config Debug
