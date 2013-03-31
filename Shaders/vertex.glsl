
// Inputs from C++, these will be different
// for every vertex that this shader processes
attribute vec3 vertex;
attribute vec3 vertexNormal;

// Static inputs that are constant for all vertices
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform mat4 matrixModel;
uniform vec3 worldLightPos;
uniform vec3 ambientLight;

// Outputs to fragment shader
varying vec3 pos_world;
varying vec3 normal_camera;
varying vec3 eyedirection_camera;
varying vec3 lightdirection_camera;

// relates to texture mapping, page 379
attribute vec2 vTexCoord;
varying vec2 texCoord;


void main()
{
	// Calculate the Model-View-Projection matrix
	mat4 MVP = projMatrix * viewMatrix * matrixModel;

	// Convert from model space to clip space
	gl_Position = MVP * vec4(vertex, 1);

	// Convert from model space to world space
	pos_world = (matrixModel * vec4(vertex, 1)).xyz;

	// vector from vertex to camera, in camera space
	vec3 vpos_camera = (viewMatrix * matrixModel * vec4(vertex, 1)).xyz;
	eyedirection_camera = vec3(0, 0, 0) - vpos_camera;

	// vector from vertex to light in camera space
	vec3 lightpos_camera = (viewMatrix * vec4(worldLightPos, 1)).xyz;
	lightdirection_camera = normalize(lightpos_camera + eyedirection_camera);

	// normal of the vertex in camera space
	normal_camera = normalize((viewMatrix * matrixModel * vec4(vertexNormal, 0)).xyz);

	texCoord = vTexCoord;
}
