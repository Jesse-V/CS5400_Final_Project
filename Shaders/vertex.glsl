
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
//attribute vec2 vTexCoord;
//varying vec2 texCoord;

varying vec3 vFractalColor;


vec3 getColorAt(vec2 pt)
{
	/*
	float ptYSq = pt.y * pt.y;
	float xOff = pt.x - 0.25;
	float q = Math.pow(xOff, 2) + ptYSq;
	if (q * (q + xOff) < ptYSq / 4)
		return vec3(0, 0, 0); //reutrhttp://en.wikipedia.org/wiki/Mandelbrot_fractal#Optimizations
	*/

	int MAX_ITERATIONS = 256;
	float COLORING = 1;

	float x = 0, xSq = 0, y = 0, ySq = 0;
	int iterations;
	for (iterations = 0; iterations < MAX_ITERATIONS && (xSq + ySq <= 144); iterations++)
	{
		y = 2 * x * y + pt.y;
		x = xSq - ySq + pt.x;
		xSq = x * x;
		ySq = y * y;
	}

	if (iterations == MAX_ITERATIONS)
		return vec3(0, 0, 0);
	else
	{
		float mu = iterations - log(log(xSq + ySq)) / log(2f);
		float sinVal = sin(mu / COLORING) / 2 + 0.5f;
		float cosVal = cos(mu / COLORING) / 2 + 0.5f;
		return vec3(cosVal, cosVal, sinVal);
	}
}


void colorFractal()
{
	float modelX = sqrt(vertex.x * vertex.x + vertex.y * vertex.y);
	float modelY = vertex.z;

	float fractalX = modelX * 12.0f - 1.2f;
	float fractalY = modelY * 2.8f - 1.5f;

	vFractalColor = getColorAt(vec2(fractalX, fractalY));
}



vec4 projectVertex()
{
	mat4 MVP = projMatrix * viewMatrix * matrixModel; //Calculate the Model-View-Projection matrix
	return MVP * vec4(vertex, 1); // Convert from model space to clip space
}



void communicateCamera()
{
	// vector from vertex to camera, in camera space
	vec3 vpos_camera = (viewMatrix * matrixModel * vec4(vertex, 1)).xyz;
	eyedirection_camera = vec3(0, 0, 0) - vpos_camera;

	// vector from vertex to light in camera space
	vec3 lightpos_camera = (viewMatrix * vec4(worldLightPos, 1)).xyz;
	lightdirection_camera = normalize(lightpos_camera + eyedirection_camera);

	// normal of the vertex in camera space
	normal_camera = normalize((viewMatrix * matrixModel * vec4(vertexNormal, 0)).xyz);
}



void main()
{
	gl_Position = projectVertex();
	pos_world = (matrixModel * vec4(vertex, 1)).xyz; //Convert from model space to world space
	communicateCamera();

	colorFractal();

	//texCoord = vTexCoord;
}
