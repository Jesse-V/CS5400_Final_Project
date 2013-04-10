
varying vec3 pos_world;
varying vec3 normal_camera;
varying vec3 eyedirection_camera;
varying vec3 lightdirection_camera;

// Static inputs that are constant for all vertices
uniform vec3 worldLightPos;
uniform vec3 ambientLight;

// relates to texture mapping
//varying vec2 texCoord;
//uniform sampler2D texture;

varying vec3 vFractalColor;


float specularLighting(inout vec3 normal, inout vec3 light)
{
	vec3 eye = normalize(eyedirection_camera);
	vec3 reflect = reflect(-light, normal);
	return clamp(dot(eye, reflect), 0, 1);
}



float diffusedLighting(inout vec3 normal, inout vec3 light)
{
	return max(0.0, clamp(dot(normal, -light), 0, 1));
}



void main()
{
	vec3 lightColor   = vec3(1, 0, 0); //vec3(0.5, 0.4, 0.4); //todo: get this in from the Light obj
	vec3 surfaceColor = vec3(1, 1, 1);
	float lightDistance = length(worldLightPos - pos_world);
	float lightPower  = 0.03f; //todo: get this in from the Light obj
	vec3 normal = normalize(normal_camera);
	vec3 light  = normalize(lightdirection_camera);

	//float theta = diffusedLighting(normal, light); //choice of lighting
	float theta = specularLighting(normal, light);

	vec3 lighting = lightColor * lightPower * theta / (lightDistance * lightDistance);
	vec3 color = vFractalColor + ambientLight + surfaceColor * lighting;

	//vec4 texColor = texture2D(texture, texCoord);
	//texColor += vec4(0.7, 0.7, 0.7, 0); //increase blending with light

	gl_FragColor = vec4(color, 1.0);// * texColor;
}
