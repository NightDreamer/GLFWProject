#pragma once
#include <string>
#include "glad.h"

class Shader
{
public:
	Shader() {};
	~Shader() {};

	void load(const std::string& vertexFilepath, const std::string& fragmentFilepath);
	void loadFromMemory(const std::string& vertexShader, const std::string& fragmentShader);
	void dispose();

	void bind();
	void unbind();

	int getUniform(std::string);

	GLuint getProgram() { return program; };

private:
	std::string loadFile(const std::string& filepath);

public:
	GLuint program;
};

