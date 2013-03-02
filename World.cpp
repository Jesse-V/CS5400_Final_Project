
const int ROTATION_SPEED = 1;
const float ZOOM = 0.7f;
GLfloat rotation[3] = {114, 0, 16}; //initial view



GLuint cameraAngle;


cameraAngle = glGetUniformLocation(program, "cameraAngle");