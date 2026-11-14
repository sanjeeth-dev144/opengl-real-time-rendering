#include"renderer.h"
#include<iostream>



#define assert(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    assert(GLLogCall(#x,__FILE__,__LINE__))


 void GLClearError() {
    while (glGetError() != GL_NO_ERROR);

}
 bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[open gl]" << error << " : " << function << " : " << file << " : " << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::Draw(const VertexArray& va, const indexBuffer& ib, const Shader& shader)const 
{
	 shader.Bind();


	 va.Bind();
	 ib.Bind();
	 GLCall(glDrawElements(GL_TRIANGLES,ib.GetCount(), GL_UNSIGNED_INT, nullptr));  // any index buffer has to be made up unsigned int

}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}