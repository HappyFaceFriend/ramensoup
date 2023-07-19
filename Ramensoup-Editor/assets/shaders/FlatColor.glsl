#type vertex
	#version 430 core

	layout(location = 0) in vec3 a_Position;

	layout(location = 0) out vec4 v_Position;

	//uniform mat4 u_ViewProjectionMat;
	//uniform mat4 u_ModelMat;

	void main()
	{
		gl_Position = vec4(a_Position, 1.0);
		v_Position = gl_Position;
	}

#type fragment
	#version 430 core

	layout(location = 0) in vec4 v_Position;

	layout(location = 0) out vec4 color;
	
	uniform vec4 u_Color;

	void main()
	{
		color = u_Color; //v_Position;
	}