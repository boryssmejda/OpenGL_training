mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH="C:/GLEW/GLEW;C:/dev/lib/cmake/glfw3" -DCMAKE_LIBRARY_PATH="C:/GLEW/GLEW/lib/Release/x64;C:/dev/lib" .. -G "Visual Studio 16 2019" -A x64
cmake --build . --config Debug
cmake --build . --config Release	