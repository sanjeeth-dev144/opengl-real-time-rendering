#pragma once
#include<vector>
#include<GL/glew.h>
#include"renderer.h"



struct VertexBufferElement {
	unsigned int type;      // 🡄 GL_FLOAT / GL_UNSIGNED_INT / GL_UNSIGNED_BYTE
	unsigned int count;     // 🡄 (unsigned int)count
	unsigned char normalized;		// 🡄 false / false / true

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type)                                      //switch? Because each OpenGL type has a different size, so the function returns the correct byte size for the given type.
		{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}
		assert(false);
		return 0;
	}

};

class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_stride;							//m_stride 🡆stores the total number of bytes occupied by one vertex.
public:
	VertexBufferLayout():
		m_stride(0){}

	template<typename T>
	void push(unsigned int count) 
	{
		static_assert(false);	//static_assert(false) — condition is always false 🡆 always causes a compile error. float         🡆  GL_FLOAT
								//						to cheak these conditions are right							unsigned int   🡆  GL_UNSIGNED_INT
								//																					unsigned char  🡆  GL_UNSIGNED_BYTE
	}

	template<>
	void push<float>(unsigned int count) {
		m_Elements.push_back({ GL_FLOAT,(unsigned int)count,GL_FALSE });			// position, UVs, normals — already decimal 🡆 no conversion needed 🡆 false
		m_stride+=count*VertexBufferElement::GetSizeOfType(GL_FLOAT);
		//m_stride += sizeof(GLfloat);
		//			or
		//m_stride += sizeof(float);
		//m_stride += 4;

	}

	template<>
	void push<unsigned int>(unsigned int count) {
		m_Elements.push_back({ GL_UNSIGNED_INT,(unsigned int)count,GL_FALSE });	// raw whole numbers, IDs — you want the exact number 🡆 no conversion 🡆 false
		m_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
		//m_stride += sizeof(GLuint);
	}

	template<>
	void push<unsigned char>(unsigned int count) {
		m_Elements.push_back({ GL_UNSIGNED_BYTE,(unsigned int)count,GL_TRUE });	// colors stored as 0-255 — shader needs 0.0-1.0 🡆 convert 🡆 true
		m_stride+= count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
		 
		//m_stride += sizeof(GLbyte);
																				//		🡇
																				// CPU sends: 255
																				// normalized = false 🡆 shader gets : 255
																				// normalized = true  🡆 shader gets : 1.0
	}

	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_stride; }

};