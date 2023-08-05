#type vertex
	#version 430 core

	layout(location = 0) in vec3 a_Position;
	layout(location = 1) in vec2 a_TexCoord;
	layout(location = 2) in int a_TexIndex;

	layout(location = 0) out vec4 v_Position;
	layout(location = 1) out vec2 v_TexCoord;
	layout(location = 2) out int v_TexIndex;

	uniform mat4 u_ViewProjectionMatrix;
	uniform mat4 u_ModelMatrix;

	void main()
	{
		gl_Position = u_ViewProjectionMatrix * u_ModelMatrix * vec4(a_Position, 1.0);

		v_Position = gl_Position;
		v_TexCoord = a_TexCoord;
		v_TexIndex = a_TexIndex;
	}

#type fragment
	#version 430 core

	layout(location = 0) in vec4 v_Position;
	layout(location = 1) in vec2 v_TexCoord;
	layout(location = 2) in int v_TexIndex;
	
	uniform sampler2D u_Textures[32]; 
	uniform vec4 u_Color;

	void main()
	{
		color = texture(u_Textures[v_TexIndex], v_TexCoord) * u_Color; //v_Position;
	}