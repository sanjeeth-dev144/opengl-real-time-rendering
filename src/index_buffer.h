#pragma once
class indexBuffer {

private:
	unsigned int m_rendererID;  // opengl needs some kind of numeric id for every type of object we allocate to create like texture,shader,vertex buffer ect.. 
								// it is a unique id that is an integer that identify the sepcific buffer that sepcific object that we created
	unsigned int m_count;		
public:
	indexBuffer(const unsigned int* data, unsigned int size);  // if u write size it is always should be in bytes if not leave a command
																// count means element count
	~indexBuffer();

	void Bind()const;
	void Unbind()const ;

	inline unsigned int GetCount() const { return m_count; }

};