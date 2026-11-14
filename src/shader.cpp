#include"shader.h"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include"renderer.h"




Shader::Shader(const std::string& filepath)
	:m_filepath(filepath),m_rendererID(0)
{

    
    MyStruct source = pass(filepath);

    //std::cout << "Vertex: " << source.vertexSource << std::endl;
    //std::cout << "Fragment: " << source.fragmentSource << std::endl;
    m_rendererID = CreateShaders(source.vertexSource, source.fragmentSource);

    //std::cout << "Program ID: " << m_rendererID << std::endl;


}

Shader::~Shader() 
{
    GLCall(glDeleteProgram(m_rendererID));
}




 MyStruct Shader::pass(const std::string& filepath) {
    std::ifstream steam(filepath);

    enum class ShaderType {
        none = -1, vertex = 0, fragment = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::none;
    while (getline(steam, line)) {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::vertex;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::fragment;
        }
        else {
            if (type != ShaderType::none)
                ss[(int)type] << line << '\n';
        }

    }
    return { ss[0].str(),ss[1].str() };
}



 unsigned int Shader::CompileShaders(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    //unsigned int id = glCreateShader(GL_VERTEX_SHADER);

    const char* src = source.c_str();
    //          or
    //const char* src = &source[0];
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));
    //return id;

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {

        int lenght;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght));
        char* message = (char*)alloca(lenght * sizeof(char)); // u cant allocate like a normal stack.but because of that dont use heap u can use like this normal stack 🡆char* message = (char*)alloca(lenght * sizeof(char)); 
        GLCall(glGetShaderInfoLog(id, lenght, &lenght, message));
        std::cout << "failed to complie" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;


    }
    return id;

}
 unsigned int Shader::CreateShaders(const std::string& vertexShader, const std::string& fragmentShader) // we need to provide opengl our source code and want to opengl compile our program link these two shaders into a single program 
//and give some kind of unique identifier for that shader so we can bind a batch of shaders and use it.
{
    unsigned int program = glCreateProgram();  //this function returns a unsigned intrger
    unsigned int vs = CompileShaders(GL_VERTEX_SHADER, vertexShader);     //creat our true shaders objects
    unsigned int fs = CompileShaders(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;

}

 void Shader::Bind() const
 {
     GLCall(glUseProgram(m_rendererID));
 }

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));

}

void Shader::Setuniform1i(const std::string& name, int value)
{
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::Setuniform1f(const std::string& name, float value)
{
    GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::Setuniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}


void Shader::SetuniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name),1,GL_FALSE,&matrix[0][0]));
}


int Shader::GetUniformLocation(const std::string& name)
{
    if (m_uniorm_location_cache.find(name) != m_uniorm_location_cache.end())
        return m_uniorm_location_cache[name];

    GLCall(int location= glGetUniformLocation(m_rendererID, name.c_str()));
    if (location == -1)
        std::cout << "warning: uniform" << name << "not exist" << std::endl;

    return m_uniorm_location_cache[name]=location;
    return location;
}
