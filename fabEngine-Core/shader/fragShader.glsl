#version 330 core

in vec2 UV;
in vec3 fragPos;
in vec3 normal;

// Ouput data
out vec4 fragColor;

// Sampler
uniform sampler2D textureSampler;
uniform vec3 lightPos;
uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform float specularExponent;
uniform mat4 MVInvTrans;

void main()
{

	// Diffuse Shading
	// Direction of the light (from the fragment to the light)
	vec3 lightDir = lightPos - fragPos;
	
	vec3 kDiffuse = texture(textureSampler, UV).rgb;
	vec3 kSpecular = texture(textureSampler, UV).rgb;

	vec3 LDiffuse = diffuseColor * kDiffuse * max(dot(normalize(lightDir), normalize(normal)), 0.0);

	// Specular Shading
	// View Vector (from the fragment to the camera)
	vec3 viewDir = normalize(-fragPos);
	// halfway vector
	vec3 h = normalize(lightDir) + normalize(viewDir);
	vec3 LSpecular = specularColor * pow(max(dot(normalize(normal), normalize(h)), 0.0), specularExponent);

	vec3 Light = LDiffuse + LSpecular + ambientColor;

	// output = color of the texture at specific UV coordinates
	 //fragColor = texture(textureSampler, UV).rgb;
	 fragColor = vec4(Light, 1.0);
}