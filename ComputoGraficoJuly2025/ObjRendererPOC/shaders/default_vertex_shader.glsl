#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view; //Camara
uniform mat4 projection;
uniform mat4 accumTrans;

out mat4 cameraOut;
out mat4 accumTransOut;
out mat4 modelOut;

void main()
{
    
    TexCoords = aTexCoords;

    FragPos = vec3(model * vec4(aPos, 1.0)); // Transform position to world space

       cameraOut = view;
       accumTransOut = accumTrans;
       modelOut = model;
   gl_Position = projection * view * model * accumTrans * vec4(aPos, 1.0);
}