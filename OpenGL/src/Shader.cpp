#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "Renderer.h"
Shader::Shader(const std::string& filepath):
	m_FilePath(filepath),m_RendererID(0)
{
	ShaderProgramSource source = ParseShader(filepath);//读取字符串
	m_RendererID = CreatShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));//传入了一个矩阵
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));//设置统一变量
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));//设置统一变量
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));//设置统一变量
}

int Shader::GetUniformLocation(const std::string& name)//会导致一遍又一遍的从这里获取，但其实location一次就好了
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())//如果这个哈希表的name 不等于这个末尾，也就是数据改变了就
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location != -1)//等于-1就会形成断点，也就是没找到u_Color
		std::cout << "Warning: uniform" << name << "'doesn't exist" << std::endl;
	m_UniformLocationCache[name] = location;//这里缓存了location
	return location;
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType//用来取值的，好理解一点
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};



	std::string line;
	std::stringstream ss[2];//这个字符串流来保存两种不同的着色器
	ShaderType type = ShaderType::NONE;//初始化用的，这是一个枚举class
	while (getline(stream, line))//一行一行的读取数据
	{
		if (line.find("#shader") != std::string::npos)//这是在一行里面，找到了shader再看后面的
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;//用int(type)
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[int(type)] << line << "\n";
		}
	}
	return { ss[0].str(), ss[1].str() };
}




 unsigned int Shader::CompileShader(const std::string& source, unsigned int type)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	//返回的是一个无终点的不可变数组，source就是我们传入的srting数组，等价于&source[0]
	//不太懂，如果字符串已经超出了作用域，而你仍然持有这个实际的char指针，它会指向无用的内存
	//并且这段代码不会起作用，所以要确保你的源字符串在你编译这段代码时仍然可用的。
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));//动态分配一个消息char,并且是在堆里创建，会自己消失
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile" <<
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			<< std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}


	//return 的作用就是告诉我们错误的句柄
	return id;
}



unsigned int Shader::CreatShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();//unsigned int = GLuint
	unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);//创建了一个顶点着色器
	unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);//有两份不同的vs和fs绑在一起
	glAttachShader(program, fs);
	glLinkProgram(program);//链接到一起的作用
	glValidateProgram(program);//在给定当前 OpenGL 状态的情况下检查其中包含的可执行文件是否可以执行

	glDeleteShader(vs);//删除着色器，现在已经绑定在gl里了
	glDeleteShader(fs);//删除着色器，现在已经绑定在gl里了

	return program;
}