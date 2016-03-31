#version 330 core

layout(location = 0) in vec4 coord;

out vec2 texcoord;

uniform mat4 projection;

void main()
{
	gl_Position = projection * vec4(coord.xy, 0, 1);
	texcoord = coord.zw;
}


