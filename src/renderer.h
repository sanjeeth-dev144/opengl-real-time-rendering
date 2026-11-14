#pragma once
#include<GL/glew.h>
#include "index_buffer.h"
#include "vertex_array.h"
#include"shader.h"
#define assert(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    assert(GLLogCall(#x,__FILE__,__LINE__))


void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
public:
    void Clear()const;
    void Draw(const VertexArray& va,const indexBuffer& ib,const Shader& shader)const;    
};