
varying vec3 pos_world;
varying vec3 normal_camera;
varying vec3 eyedirection_camera;
varying vec3 lightdirection_camera;

// Static inputs that are constant for all vertices. Todo: are these even used?
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform mat4 matrixModel;
uniform vec3 worldLightPos;
uniform vec3 ambientLight;

// relates to texture mapping
varying vec2 texCoord;
uniform sampler2D texture;


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
	vec3 lightColor   = vec3(0.5, 0.4, 0.4);
	vec3 surfaceColor = vec3(0.1, 0.4, 0.2);
	float lightDistance = length(worldLightPos - pos_world);
	float lightPower  = 20.0f;
	vec3 normal = normalize(normal_camera);
	vec3 light  = normalize(lightdirection_camera);

	//float theta = diffusedLighting(normal, light);
	float theta = specularLighting(normal, light);

	vec3 lighting = lightColor * lightPower * theta / (lightDistance * lightDistance);
	vec3 color = ambientLight + surfaceColor * lighting;

	gl_FragColor = vec4(color, 1.0) * texture2D(texture, texCoord);
}
