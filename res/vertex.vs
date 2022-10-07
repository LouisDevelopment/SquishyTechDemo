#version 410 core
layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 tex;

out vec4 ourColor;
out vec2 texCoord;

uniform vec3 color;
uniform float alpha;

uniform mat4 model;
uniform mat4 projection;

void main(){
    gl_Position = projection * model * vec4(pos, 0.0, 1.0);
    ourColor = vec4(color.x, color.y, color.z, alpha);
    
    texCoord = tex.xy;

}

