
varying vec3 pos_world;
varying vec3 normal_camera;
varying vec3 eyedirection_camera;
varying vec3 lightdirection_camera;

uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform vec3 worldLightPos;
uniform vec3 ambientLight;
uniform mat4 matrixModel;

void main()
{
	vec3 lightcolor   = vec3(0.5, 0.4, 0.4);
	vec3 surfacecolor = vec3(0.1, 0.4, 0.2);
	float lightdistance = length(worldLightPos - pos_world);
	float lightpower  = 20.0f;
	vec3 normal = normalize(normal_camera);
	vec3 light  = normalize(lightdirection_camera);

	// if you want diffused lighting
	float costheta = max(0.0, clamp(dot(normal, -light), 0, 1));
	vec3 color = ambientLight + surfacecolor * lightcolor * lightpower * costheta / (lightdistance*lightdistance);

	// If you want more specular-like lighting...
	//vec3 eye = normalize(eyedirection_camera);
	//vec3 reflect = reflect(-light, normal);
	//float cosalpha = clamp(dot(eye, reflect), 0, 1);
	//vec3 color = ambientLight + surfacecolor * lightcolor * lightpower * cosalpha / (lightdistance*lightdistance);

	gl_FragColor = vec4(color, 1.0);
}
