#version 330 core

in vec2 texcoord;

uniform sampler2D tex;
uniform vec4 color;

void main()
{
	gl_FragColor = color * texture(tex, texcoord);
}


