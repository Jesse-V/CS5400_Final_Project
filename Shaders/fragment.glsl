
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
	vec3 lightColor   = vec3(0.5, 0.4, 0.4);
	vec3 surfaceColor = vec3(0.1, 0.4, 0.2);
	float lightDistance = length(worldLightPos - pos_world);
	float lightPower  = 20.0f;
	vec3 normal = normalize(normal_camera);
	vec3 light  = normalize(lightdirection_camera);

	// if you want diffused lighting
	//float costheta = max(0.0, clamp(dot(normal, -light), 0, 1));
	//vec3 color = ambientLight + surfaceColor * lightColor * lightPower * costheta / (lightDistance*lightDistance);

	// If you want more specular-like lighting...
	vec3 eye = normalize(eyedirection_camera);
	vec3 reflect = reflect(-light, normal);
	float cosalpha = clamp(dot(eye, reflect), 0, 1);
	vec3 color = ambientLight + surfaceColor * lightColor * lightPower * cosalpha / (lightDistance*lightDistance);

	gl_FragColor = vec4(color, 1.0);
}
