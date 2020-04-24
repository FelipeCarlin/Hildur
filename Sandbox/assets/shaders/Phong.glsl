#type vertex
#version 140 core
#extension GL_ARB_explicit_attrib_location : require

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec3 a_Normal;

uniform mat4 u_ViewProjectionMat;
uniform mat4 u_ModelMat;

out vec3 v_Pos;
out vec2 v_TexCoord;
out vec3 v_Normal;

out vec3 v_ViewPos;


void main()
{
	//Variables for fragment shader
	v_Pos = vec4(u_ModelMat * vec4(a_Pos, 1.0)).xyz;
	v_TexCoord = a_TexCoord;
	v_Normal = mat3(u_ModelMat) * a_Normal;

	//vertex shader
	gl_Position = u_ViewProjectionMat * u_ModelMat * vec4(a_Pos, 1.0);

}


#type fragment
#version 140 core
#extension GL_ARB_explicit_attrib_location : require

//Output
layout(location = 0) out vec4 color;


//Material
uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;

//Uniforms
//uniform sampler2D albedoMap;
//uniform sampler2D normalMap;
//uniform sampler2D roughnessMap;
//uniform sampler2D aoMap;
//uniform sampler2D metallicMap;
//uniform sampler2D emissionMap;


//Variables from vertex shader
in vec3 v_Pos;
in vec2 v_TexCoord;
in vec3 v_Normal;

uniform vec3 u_ViewPos;
uniform vec3 u_LightPos;
uniform vec3 u_LightColor;


void main()
{
	//Ambient light
	vec3 ambLight = ambient;

	//Diffuse light
	vec3 PosToLightDirVec = normalize(u_LightPos - v_Pos);
	//vec3 diffuseCol = vec3(1.0f, 1.0f, 1.0f);
	float diffuseValue = clamp(dot(PosToLightDirVec, v_Normal), 0, 1);
	vec3 diffuseFinal = diffuse * diffuseValue * u_LightColor;

	//Specular light
	vec3 lightToPosDirVec = normalize(v_Pos - u_LightPos);
	vec3 refectDirDirVec = normalize(reflect(lightToPosDirVec, normalize(v_Normal)));
	vec3 posToViewVecDirVec = normalize(u_ViewPos - v_Pos);
	float specularConstant = pow(max(dot(posToViewVecDirVec, refectDirDirVec), 0), 35);
	vec3 specularFinal = specular * specularConstant;

	//Output
//	color = mix(texture(diffuseTex, v_TexCoord), texture(specularTex, v_TexCoord), 1.0)
//		* (vec4(ambLight, 1.0f) + vec4(diffuseFinal, 1.0f) + vec4(specularFinal, 1.0f));

	color = vec4(ambLight, 1.0f) + vec4(diffuseFinal, 1.0f) + vec4(specularFinal, 1.0f);
}