import requests

def downloadStbImage():
    url = 'https://raw.githubusercontent.com/nothings/stb/master/stb_image.h'

    r = requests.get(url, allow_redirects=True)
    open('stb_image.h', 'wb').write(r.content)
    
if __name__ == '__main__':
    downloadStbImage()