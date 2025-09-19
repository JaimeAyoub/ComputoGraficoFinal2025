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

Light light;
uniform vec3 viewPos; 


vec3 ambient(Light L, Material M)
{
   return L.ambient * M.ambient;
}

vec3 diffuse(Light L, Material M, vec3 Normal)
{
    vec3 lightDir = normalize(-L.direction); // Directional light points in this direction
    vec3 materialDiffuse = M.diffuse * texture(M.texture_diffuse1, TexCoords).rgb;
    float diff = max(dot(normalize(Normal), lightDir), 0.0);
    return diff * L.diffuse * materialDiffuse;
}


vec3 specular(Light L, Material M, vec3 Normal, vec3 FragPos)
{
    vec3 lightDir = normalize(-L.direction);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normalize(Normal));
    
    vec3 materialSpecular =  texture(M.texture_specular1, TexCoords).rgb;
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0f);
    return spec * L.specular * materialSpecular;
}


void main()
{ 
    light.ambient = vec3(0.2, 0.2, 0.2);
    light.diffuse = vec3(1.0, 1.0, 1.0);
    light.specular = vec3(1.0, 1.0, 1.0);
    light.direction = vec3(1.0, 1.0, 1.0);
    light.position = vec3(0.0f,0.0f,1.0f);


  vec3 normalMap = texture(material.texture_normal1, TexCoords).xyz;

    
    vec3 lightDir = normalize(light.direction); 

    mat4 matForNormals = transpose(inverse(cameraOut * accumTransOut));
    normalMap = normalize(matForNormals * vec4(normalMap,1.0)).xyz;
    
    // Specular color from material's specular property AND specular texture
    // Si no hay texture_specular1, la textura por defecto de OpenGL es blanca (1,1,1)
    // por lo que si el modelo solo tiene color especular y no textura, igualmente funciona.

    vec3 viewDir = normalize(viewPos - FragPos); 
    vec3 reflectDir = reflect(-lightDir, normalMap);  

    vec3 emissiveTexture = texture(material.texture_emissive1, TexCoords).rgb;
    vec3 emissive = emissiveTexture * 0.5f;
   
    vec3 base = ambient(light,material) + diffuse(light,material,normalMap) + specular(light, material, normalMap, FragPos);
    vec3 result = base + emissive;


    
    FragColor = vec4(result, 1.0);
}