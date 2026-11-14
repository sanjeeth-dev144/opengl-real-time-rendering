#pragma once
#include"renderer.h"

class Texture{
private:
	unsigned int m_rendererID;
	std::string m_filepath;
	unsigned char* m_localbuffer;		//unsigned char stores a small integer from 0 to 255, which is useful for storing a pixel's colour-channel values.

	int m_width, m_height, m_BPP;		// m_width  🡆Image width in pixels.
										// m_height 🡆Image height in pixels.
										// m_BPP    🡆Bytes Per Pixel.
public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot=0)const; //unsigned int slot = 0 🡆it is an optional parameter if u dont specify it will be zero which allows u to specify the slot that u want to bind the texture to 
	void Unbind()const;					 //                        in opengl u have various slots that we can bind the texture to. that exists is because we have the ability to bind more than one texture at once 


	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }

};