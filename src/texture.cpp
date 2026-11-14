#include "texture.h"
#include"stb_image/stb_image.h"

Texture::Texture(const std::string& path):m_rendererID(0),m_filepath(path),m_height(0),m_width(0),m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);  
	//stbi_set_flip_vertically_on_load(1); 🡆it flip our texture vertically makes it upside down because opengl expect our texture pixel to start at the bottom left not the top left so the bottom left in opengl is 00
	//										 when we load images it stores it in a scan lines from the top of the image to the bottom of the image so we need to flip it on load 

	m_localbuffer = stbi_load(path.c_str(), &m_width, &m_height,&m_BPP,4); //desired channels 🡆RGBA 🡆4

	//              stbi_load() 🡆it will write the width and height BBP(bits per pixel) into those actully variables for us

	GLCall(glGenTextures(1, &m_rendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));


	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));  
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));             //explained 🡆day 7 🡆textures

	//These four lines tell OpenGL how to display the texture when it is rendered. They control two things: how pixels are selected and what happens at the texture's edges.



	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height,0,GL_RGBA, GL_UNSIGNED_BYTE, m_localbuffer));  //glTexImage2D() 🡆uploads the image data from CPU memory (RAM) to GPU memory (VRAM).
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

		if (m_localbuffer)
			stbi_image_free(m_localbuffer);  // we can free m_localbuffer 🡆in CPU memory without needing to load the image again for normal rendering.

}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1,&m_rendererID))
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));

}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

}
