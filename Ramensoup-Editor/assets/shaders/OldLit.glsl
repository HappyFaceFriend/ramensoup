#type vertex
#version 430 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;

layout(location = 0) out vec4 v_Position;
layout(location = 1) out vec3 v_Normal;
layout(location = 2) out vec2 v_TexCoord;



uniform mat4 u_ViewProjectionMatrix;
uniform mat4 u_ModelMatrix;

void main()
{
	gl_Position = u_ViewProjectionMatrix * u_ModelMatrix * vec4(a_Position, 1.0);
	v_Position = gl_Position;
	v_Normal = a_Normal;
	v_TexCoord = a_TexCoord;
}

#type fragment
#version 430 core

layout(location = 0) in vec4 v_Position;
layout(location = 1) in vec3 v_Normal;
layout(location = 2) in vec2 v_TexCoord;

layout(location = 0) out vec4 color;

uniform sampler2D u_DiffuseTexture;

void main()
{
	color = texture(u_DiffuseTexture, v_TexCoord); //v_Position;
	//color = vec4(v_Normal, 1.0);
}