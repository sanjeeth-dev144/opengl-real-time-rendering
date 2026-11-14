#include"vertex_array.h"
#include"renderer.h"
#include"vertex_buffer_layout.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_rendererID));
	//GLCall(glBindVertexArray(vao));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteBuffers(1, &m_rendererID));

}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0;i < elements.size();i++) 
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset)) 	//element.count🡆Number of components, such as 2 for x and y 🡆push<float>(2)
							//GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

			offset += element.count*VertexBufferElement::GetSizeOfType(element.type);

	}

}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_rendererID))
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0))

}
