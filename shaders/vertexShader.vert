#version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;
    
    uniform float currentX;
    
    out vec3 ourColor;
    
    void main()
    {
       gl_Position = vec4((aPos.x + currentX), aPos.y, aPos.z, 1.0);
       ourColor = vec3(gl_Position.x, gl_Position.y, gl_Position.z);
    };