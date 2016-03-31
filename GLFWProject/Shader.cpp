#include "Shader.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>	


void Shader::dispose()
{
	glDeleteProgram(program);
}

void Shader::load(const std::string& vertexFilepath, const std::string& fragmentFilepath)
{
	// load & compile vertex shader
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	std::string vsSource = loadFile(vertexFilepath);
	const char* vsSourceArray = vsSource.c_str();
	glShaderSource(vs, 1, &vsSourceArray, NULL);
	glCompileShader(vs);

	GLint vertexShaderCompiled = 0;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &vertexShaderCompiled);
	if (vertexShaderCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vs, maxLength, &maxLength, &infoLog[0]);
		glDeleteShader(vs);
		std::cout << "Couldn't compile vertex shader \"" << vertexFilepath << "\"\nReason: " << infoLog.data() << std::endl;
		getchar();
		return;
	}

	// load & compile fragment shader
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fsSource = loadFile(fragmentFilepath);
	const char* fsSourceArray = fsSource.c_str();
	glShaderSource(fs, 1, &fsSourceArray, NULL);
	glCompileShader(fs);

	GLint fragmentShaderCompiled = 0;
	glGetShaderiv(fs, GL_COMPILE_STATUS, &fragmentShaderCompiled);
	if (fragmentShaderCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(fs, maxLength, &maxLength, &infoLog[0]);
		glDeleteShader(fs);
		std::cout << "Couldn't compile fragment shader \"" << fragmentFilepath << "\"\nReason: " << infoLog.data() << std::endl;
		getchar();
		return;
	}

	// create shader program
	GLuint program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	// check if linking was successful
	GLint linkStatus = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int *)&linkStatus);

	if (linkStatus == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
		glDeleteProgram(program);
		glDeleteShader(vs);
		glDeleteShader(fs);

		std::cout << "Couldn't link shader program \"" << fragmentFilepath.substr(0, fragmentFilepath.length() - 5) << "\"" << std::endl;
		getchar();
	}
	else
	{
		glDetachShader(program, vs);
		glDetachShader(program, fs);
		glDeleteShader(vs);
		glDeleteShader(fs);

		this->program = program;
	}
}


void Shader::loadFromMemory(const std::string& vertexShader, const std::string& fragmentShader)
{
	// load & compile vertex shader
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	const char* vsSourceArray = vertexShader.c_str();
	glShaderSource(vs, 1, &vsSourceArray, NULL);
	glCompileShader(vs);

	GLint vertexShaderCompiled = 0;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &vertexShaderCompiled);
	if (vertexShaderCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vs, maxLength, &maxLength, &infoLog[0]);
		glDeleteShader(vs);
		std::cout << "Couldn't compile vertex shader \"" << vertexShader << "\"\nReason: " << infoLog.data() << std::endl;
		getchar();
		return;
	}

	// load & compile fragment shader
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fsSourceArray = fragmentShader.c_str();
	glShaderSource(fs, 1, &fsSourceArray, NULL);
	glCompileShader(fs);

	GLint fragmentShaderCompiled = 0;
	glGetShaderiv(fs, GL_COMPILE_STATUS, &fragmentShaderCompiled);
	if (fragmentShaderCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(fs, maxLength, &maxLength, &infoLog[0]);
		glDeleteShader(fs);
		std::cout << "Couldn't compile fragment shader \"" << fragmentShader << "\"\nReason: " << infoLog.data() << std::endl;
		getchar();
		return;
	}

	// create shader program
	GLuint program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	// check if linking was successful
	GLint linkStatus = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int *)&linkStatus);

	if (linkStatus == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
		glDeleteProgram(program);
		glDeleteShader(vs);
		glDeleteShader(fs);

		std::cout << "Couldn't link shader program \"" << fragmentShader.substr(0, fragmentShader.length() - 5) << "\"" << std::endl;
		getchar();
	}
	else
	{
		glDetachShader(program, vs);
		glDetachShader(program, fs);
		glDeleteShader(vs);
		glDeleteShader(fs);

		this->program = program;
	}
}


int Shader::getUniform(std::string name)
{
	return glGetUniformLocation(program, name.c_str());
}


void Shader::bind()
{
	glUseProgram(program);
}


void Shader::unbind()
{
	glUseProgram(0);
}


std::string Shader::loadFile(const std::string& filepath)
{
	std::fstream file(filepath, std::ios::in);

	if (file.is_open())
	{
		std::stringstream buffer;
		buffer << file.rdbuf();
		std::string content = buffer.str();
		return content;
	}
	else
	{
		std::cout << "Failed to open file \"" << filepath << "\"" << std::endl;
		getchar();
		return std::string();
	}
}


