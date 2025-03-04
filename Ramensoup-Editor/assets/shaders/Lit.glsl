#type vertex
#version 430 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;

layout(location = 0) out vec4 v_Position;
layout(location = 1) out vec3 v_Normal;
layout(location = 2) out vec2 v_TexCoord;
layout(location = 3) out vec3 v_WorldPosition;

uniform mat4 u_ViewProjectionMatrix;
uniform mat4 u_ModelMatrix;


void main()
{
	gl_Position = u_ViewProjectionMatrix * u_ModelMatrix * vec4(a_Position, 1.0);
	v_Position = gl_Position;
	v_TexCoord = a_TexCoord;
	v_Normal = vec3(transpose(inverse(u_ModelMatrix)) * normalize(vec4(a_Normal, 0)));
	v_WorldPosition = vec3(u_ModelMatrix * vec4(a_Position, 1.0));
}

#type fragment
#version 430 core

layout(location = 0) in vec4 v_Position;
layout(location = 1) in vec3 v_Normal;
layout(location = 2) in vec2 v_TexCoord;
layout(location = 3) in vec3 v_WorldPosition;

layout(location = 0) out vec4 color;

uniform sampler2D u_DiffuseTexture;

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
	vec4 texColor = texture(u_DiffuseTexture, v_TexCoord);

	// Phong shading
	vec3 illumination = u_MaterialParams.Ka * u_AmbientLight;
	for(int i = 0; i < u_LightCount; i++)
	{
		vec3 L = normalize(u_LightSources[i].Position - v_WorldPosition);
		vec3 V = normalize(u_CameraPosition - v_WorldPosition);
		vec3 N = v_Normal;
		vec3 R = normalize(2 * dot(L, N) * N - L); // Reflection vector

		float D = length(u_LightSources[i].Position - v_WorldPosition);
		float attenuation = u_LightSources[i].Attenuation.x + u_LightSources[i].Attenuation.y * D
							+ u_LightSources[i].Attenuation.z *  D * D;
		attenuation = max(attenuation, 0.001f);

		vec3 specular = pow(max(dot(R, V), 0.0f), u_MaterialParams.Shineness) * u_LightSources[i].Color / attenuation;
		vec3 diffuse = max(dot(L, N), 0.0f) * u_LightSources[i].Color / attenuation;

		illumination += u_MaterialParams.Kd * diffuse + u_MaterialParams.Ks * specular;
	}
	
	color = texColor * vec4(illumination, 1);
}