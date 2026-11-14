#pragma once
class VertexBuffer {

private:
	unsigned int m_rendererID;  // opengl needs some kind of numeric id for every type of object we allocate to create like texture,shader,vertex buffer ect.. 
								// it is a unique id that is an integer that identify the sepcific buffer that sepcific object that we created
public:
	VertexBuffer(const  void* data, unsigned int size);
	~VertexBuffer();

	void Bind()const;
	void Unbind()const;

};