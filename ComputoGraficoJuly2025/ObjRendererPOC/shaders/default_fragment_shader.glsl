#version 460 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

in mat4 cameraOut;
in mat4 accumTransOut;
in mat4 modelOut;

// Material properties from the model
struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    sampler2D texture_emissive1;
    sampler2D texture_normal1;

    // You can add more texture types here if your models support them
    // sampler2D texture_normal1;
    // sampler2D texture_height1;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
uniform Material material;

// Light properties (example directional light)
struct Light {
    vec3 position;  // For point light or camera position for viewDir
    vec3 direction; // For directional light
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
//uniform Light light; // Example light
Light light;
uniform vec3 viewPos; // Camera position in world space

vec3 ambient(Light L, Material M)
{
   return L.ambient * M.ambient;
}

vec3 diffuse(Light L, Material M, vec3 Normal)
{
    vec4 materialDiffuse = texture(M.texture_diffuse1,TexCoords);
    return (max(0.0f, dot(normalize(L.position), normalize(Normal))) * L.diffuse * materialDiffuse.xyz);
}

vec3 specular(vec3 eye,vec3 vertexPos,Light L,Material M, vec3 Normal )
{
	vec3 view = normalize(eye) - normalize(vertexPos);
	vec3 RE = normalize(reflect((eye - L.position),Normal));
	vec3 specular = vec3(0.0f,0.0f,0.0f);
	if(dot(L.position,view) > 0.0)
	{
		specular = L.specular * M.specular * pow(max(0.0f,dot(view,RE)),M.shininess);
	}
	return specular;
}


void main()
{ 
    light.ambient = vec3(0.2, 0.2, 0.2);
    light.diffuse = vec3(1.0, 1.0, 1.0);
    light.specular = vec3(1.0, 1.0, 1.0);
    light.direction = vec3(1.0, 1.0, 1.0);
    light.position = vec3(0.0f,0.0f,1.0f);

    vec4 nPos =vec4(FragPos, 1.0);

    nPos = cameraOut * accumTransOut * vec4(FragPos, 1.0);

    vec3 norm = normalize(texture(material.texture_normal1, TexCoords).rgb);
   // vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.direction); 

    mat4 matForNormals = transpose(inverse(cameraOut * accumTransOut));
    norm = normalize(matForNormals * vec4(norm,1.0)).xyz;
    
    // Specular color from material's specular property AND specular texture
    // Si no hay texture_specular1, la textura por defecto de OpenGL es blanca (1,1,1)
    // por lo que si el modelo solo tiene color especular y no textura, igualmente funciona.

    vec3 viewDir = normalize(viewPos - FragPos); 
    vec3 reflectDir = reflect(-lightDir, norm);  

    vec3 emissiveTexture = texture(material.texture_emissive1, TexCoords).rgb;
    vec3 emissive = emissiveTexture * 0.5f;
        
    vec3 base = ambient(light,material) + diffuse(light,material,norm) + specular(viewPos,FragPos.xyz,light,material,norm);
    vec3 result = base + emissive;


    
    FragColor = vec4(result, 1.0);
}