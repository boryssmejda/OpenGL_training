mkdir build
cd build
conan install .. -s build_type=Debug
cmake .. -DCMAKE_BUILD_TYPE=DEBUG
cmake --build . --config Debug
./ExampleOpenGL
