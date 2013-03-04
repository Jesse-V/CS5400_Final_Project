#version 150

uniform vec3 cameraAngle; //camera rotation
in vec4 vertPosition; //location of point from Main.cpp
out vec4 fragmentColor; 

mat4 cameraView()
{
	vec3 angles = radians(cameraAngle);
	vec3 c = cos(angles);
	vec3 s = sin(angles);

	mat4 rx = mat4(
		1.0,	0.0,	0.0,	0.0,
		0.0,	c.x,	-s.x,	0.0,
		0.0,	s.x,	c.x,	0.0,
		0.0,	0.0,	0.0,	1.0
		);

	mat4 ry = mat4(
		c.y,	0.0,	s.y,	0.0,
		0.0,	1.0,	0.0,	0.0,
		-s.y,	0.0,	c.y,	0.0,
		0.0,	0.0,	0.0,	1.0
		);

	mat4 rz = mat4(
		c.z,	-s.z,	0.0,	0.0,
		s.z,	c.z,	0.0,	0.0,
		0.0,	0.0,	1.0,	0.0,
		0.0,	0.0,	0.0,	1.0
		);

	return rx * ry * rz;
}


vec4 getColor()
{
	return vec4(0, 0, 0, 1);
}


void main()
{
	gl_Position = cameraView() * vertPosition;
	fragmentColor = getColor();
}

//http://stackoverflow.com/questions/8632550/how-does-the-default-glsl-shaders-look-like-for-version-330
