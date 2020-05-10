import os
import subprocess
import platform
import downStbImage


downStbImage.downloadStbImage()

if platform.system() == "Windows" :
    # define the name of the directory to be created
    buildDir = "build"

    try:
        os.mkdir(buildDir)
    except OSError:
        print("Creation of the directory --> %s failed" % buildDir)
    else:
        print("%s create successfully" % buildDir)

    os.chdir(buildDir)

# ------------------------------------ Libraries -----------------------------------------------

# -------------------------------------- GLEW --------------------------------------------------
    glew_prefix_path = "C:/GLEW/GLEW"
    glew_library_path = "C:/GLEW/GLEW/lib/Release/x64"
# ----------------------------------------------------------------------------------------------

# --------------------------------------- GLFW -------------------------------------------------
    glfw_prefix_path = "C:/dev/lib/cmake/glfw3"
    glfw_library_path = "C:/dev/lib"
# ----------------------------------------------------------------------------------------------


    cmake_prefix_path = ('\"%s;%s\"' % (glew_prefix_path, glfw_prefix_path))
    cmake_prefix_path = 'CMAKE_PREFIX_PATH=%s' % cmake_prefix_path

    cmake_library_path = '\"%s;%s\"' % (glew_library_path, glfw_library_path)
    cmake_library_path = 'CMAKE_LIBRARY_PATH=%s' % cmake_library_path

    cmake_command = 'cmake -D%s -D%s .. -G "Visual Studio 16 2019" -A x64' % (cmake_prefix_path, cmake_library_path)
    subprocess.run(cmake_command)

elif platform.system() == "Linux" or platform.system() == "Darwin":

    # define the name of the directory to be created
    buildDebug = "build_debug"
    buildRelease = "build_release"

    try:
        os.mkdir(buildDebug)
        os.mkdir(buildRelease)
    except OSError:
        print("Creation of the directories failed")
    else:
        print("Folders created successfully!")

    os.chdir(buildDebug)
    cmake_command = 'cmake .. -DCMAKE_BUILD_TYPE=DEBUG'
    subprocess.run(["cmake", "-D", "CMAKE_BUILD_TYPE=DEBUG", ".."])
    subprocess.run("make")
    subprocess.run("./ExampleOpenGL")

    os.chdir('../%s' % buildRelease)
    cmake_command = ["cmake", "-D", "CMAKE_BUILD_TYPE=RELEASE", ".."]
    subprocess.run(cmake_command)
    subprocess.run("make")
    subprocess.run("./ExampleOpenGL")



