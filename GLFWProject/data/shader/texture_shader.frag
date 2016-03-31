#version 330 core

in vec2 texcoord;

uniform sampler2D tex;

void main()
{
	gl_FragColor = texture(tex, texcoord);
}


