mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH="C:\glew-2.1.0-win32\glew-2.1.0;C:\glfw-3.3.2.bin.WIN64\lib-vc2019;C:\dev\lib\cmake\glfw3" -DCMAKE_LIBRARY_PATH="C:\glew-2.1.0-win32\glew-2.1.0\lib\Release\x64;C:\glfw-3.3.2.bin.WIN64\lib-vc2019;C:\dev\lib"
cmake --build . --config Debug
cmake --build . --config Release	