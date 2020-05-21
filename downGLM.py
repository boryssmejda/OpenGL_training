import requests
from zipfile import ZipFile
import shutil
import os

file_name = "glm.zip"

def deleteGlmFolder():
    shutil.rmtree('glm', ignore_errors=False, onerror=None)
    

def deleteGlmZipFile():
    if os.path.exists(file_name):
        os.remove(file_name)
    else:
        print("The file does not exist")


def copyIntoInclude():
    src = "glm/glm"
    dst = "include/glm"
    if os.path.exists(dst) == False:
        shutil.copytree(src, dst)


def configureGLM():
    downloadGLM()
    unzipGLM()
    copyIntoInclude()
    deleteGlmZipFile()
    deleteGlmFolder()

def downloadGLM():
    url = 'https://github.com/g-truc/glm/releases/download/0.9.9.8/glm-0.9.9.8.zip'
    print("Download start!")
    r = requests.get(url, allow_redirects=True)
    open(file_name, 'wb').write(r.content)
    
    
def unzipGLM():
    with ZipFile(file_name, 'r') as zip:
        zip.extractall()
    
if __name__ == '__main__':
    configureGLM()