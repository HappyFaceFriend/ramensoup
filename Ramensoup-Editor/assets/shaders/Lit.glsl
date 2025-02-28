#type vertex
#version 430 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;

layout(location = 0) out vec4 v_Position;
layout(location = 1) out vec3 v_Normal;
layout(location = 2) out vec2 v_TexCoord;
layout(location = 3) out vec3 v_Illumination;

uniform mat4 u_ViewProjectionMatrix;
uniform mat4 u_ModelMatrix;

struct LightSource
{
	vec3 Position;
	vec3 Color;
	vec3 Attenuation; // a, b, c
};
uniform LightSource u_LightSources[8];
uniform int u_LightCount;
uniform vec3 u_AmbientLight;

struct PhongMaterialParams
{
	float Ka, Kd, Ks; // Coeifficients of ambient, diffuse, specular
	float Shineness;
};
uniform PhongMaterialParams u_MaterialParams;
uniform vec3 u_CameraPosition;

void main()
{
	gl_Position = u_ViewProjectionMatrix * u_ModelMatrix * vec4(a_Position, 1.0);
	v_Position = gl_Position;
	v_Normal = normalize(a_Normal);
	v_TexCoord = a_TexCoord;

	v_Illumination = vec3(0);
	// Phong shading
	for(int i = 0; i < u_LightCount; i++)
	{
		vec3 position = vec3(u_ModelMatrix * vec4(a_Position, 1.0));
		vec3 L = normalize(u_LightSources[i].Position - position);
		vec3 V = normalize(u_CameraPosition - position);
		vec3 N = v_Normal;
		vec3 R = normalize(2 * dot(L, N) * N - L); // Reflection vector

		float D = length(u_LightSources[i].Position - position);
		float attenuation = u_LightSources[i].Attenuation.x + u_LightSources[i].Attenuation.y * D
							+ u_LightSources[i].Attenuation.z *  D * D;
		attenuation = max(attenuation, 0.001f);

		vec3 specular = pow(max(dot(R, V), 0.0f), u_MaterialParams.Shineness) * u_LightSources[i].Color / attenuation;
		vec3 diffuse = max(dot(L, N), 0.0f) * u_LightSources[i].Color / attenuation;

		// v_Illumination = u_AmbientLight;
		v_Illumination += u_MaterialParams.Ka * u_AmbientLight + u_MaterialParams.Kd * diffuse + u_MaterialParams.Ks * specular;
	}
}

#type fragment
#version 430 core

layout(location = 0) in vec4 v_Position;
layout(location = 1) in vec3 v_Normal;
layout(location = 2) in vec2 v_TexCoord;
layout(location = 3) in vec3 v_Illumination;

layout(location = 0) out vec4 color;

uniform sampler2D u_DiffuseTexture;

void main()
{
	//vec4 texColor = texture(u_DiffuseTexture, v_TexCoord);
	color = vec4(v_Illumination, 1);
	//color = vec4(v_Normal, 1.0);
}