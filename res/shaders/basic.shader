
#shader vertex
#version 330 core
layout(location=0) in vec4 position;
layout(location=1) in vec2 texcoor;

out vec2 v_texcoor;

uniform mat4 u_MVP;					//mat4 🡆a data type representing a 4×4 matrix (16 numbers).

void main()
{

gl_Position=u_MVP*position;
v_texcoor=texcoor;
}

#shader fragment

#version 330 core
layout(location=0) out vec4 colour;

in vec2 v_texcoor;


//uniform vec4 u_colour;
uniform sampler2D u_texture;

void main()
{
vec4 texColour=texture(u_texture,v_texcoor);
colour=texColour;	
};

//vec4(0.2,0.3,0.8,1.0);