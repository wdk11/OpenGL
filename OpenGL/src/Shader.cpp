#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "Renderer.h"
Shader::Shader(const std::string& filepath):
	m_FilePath(filepath),m_RendererID(0)
{
	ShaderProgramSource source = ParseShader(filepath);//��ȡ�ַ���
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
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));//������һ������
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));//����ͳһ����
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));//����ͳһ����
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));//����ͳһ����
}

int Shader::GetUniformLocation(const std::string& name)//�ᵼ��һ����һ��Ĵ������ȡ������ʵlocationһ�ξͺ���
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())//��������ϣ���name ���������ĩβ��Ҳ�������ݸı��˾�
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location != -1)//����-1�ͻ��γɶϵ㣬Ҳ����û�ҵ�u_Color
		std::cout << "Warning: uniform" << name << "'doesn't exist" << std::endl;
	m_UniformLocationCache[name] = location;//���ﻺ����location
	return location;
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType//����ȡֵ�ģ������һ��
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};



	std::string line;
	std::stringstream ss[2];//����ַ��������������ֲ�ͬ����ɫ��
	ShaderType type = ShaderType::NONE;//��ʼ���õģ�����һ��ö��class
	while (getline(stream, line))//һ��һ�еĶ�ȡ����
	{
		if (line.find("#shader") != std::string::npos)//������һ�����棬�ҵ���shader�ٿ������
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;//��int(type)
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
	//���ص���һ�����յ�Ĳ��ɱ����飬source�������Ǵ����srting���飬�ȼ���&source[0]
	//��̫��������ַ����Ѿ������������򣬶�����Ȼ�������ʵ�ʵ�charָ�룬����ָ�����õ��ڴ�
	//������δ��벻�������ã�����Ҫȷ�����Դ�ַ������������δ���ʱ��Ȼ���õġ�
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));//��̬����һ����Ϣchar,�������ڶ��ﴴ�������Լ���ʧ
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile" <<
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			<< std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}


	//return �����þ��Ǹ������Ǵ���ľ��
	return id;
}



unsigned int Shader::CreatShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();//unsigned int = GLuint
	unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);//������һ��������ɫ��
	unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);//�����ݲ�ͬ��vs��fs����һ��
	glAttachShader(program, fs);
	glLinkProgram(program);//���ӵ�һ�������
	glValidateProgram(program);//�ڸ�����ǰ OpenGL ״̬������¼�����а����Ŀ�ִ���ļ��Ƿ����ִ��

	glDeleteShader(vs);//ɾ����ɫ���������Ѿ�����gl����
	glDeleteShader(fs);//ɾ����ɫ���������Ѿ�����gl����

	return program;
}