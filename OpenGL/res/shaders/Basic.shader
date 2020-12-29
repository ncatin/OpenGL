#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 u_MVP;
uniform mat4 u_Model;

out vec3 Normal;
out vec3 FragPos;

void main()
{
	gl_Position = u_MVP * vec4(position,1);
	FragPos = vec3(u_Model * vec4(position, 1.0f));
	Normal = normal;
	
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;


in vec3 Normal;
in vec3 FragPos;

uniform vec3 u_Color;
uniform sampler2D u_Texture;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
	

	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse + specular) * u_Color;
	color = vec4(result, 1.0f);
	//color = u_Color;
};