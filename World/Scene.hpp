
#ifndef SCENE_HPP
#define SCENE_HPP

#include "Camera.hpp"
#include "Light.hpp"
#include "ShaderLoader/Program.hpp"
#include "Modeling/RenderableObject.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>


class Scene
{
	public:
		void init();
		void loadCubeModel(const glm::mat4& modelmatrix = glm::translate(glm::mat4(), glm::vec3(0.0, -0.1, 0.0)));
		void setCamera(const std::shared_ptr<Camera>& camera);
		void clear();
		void addLight(const std::shared_ptr<Light>& light);
		void setAmbientLight(const glm::vec3& rgb); // (0,0,0) is total darkness, (1.0,1,0,1,0) is total light
		void render();

		std::shared_ptr<Camera> getCamera();
		std::shared_ptr<cs5400::Program> getProgram();

	private:
		std::shared_ptr<cs5400::Program> program;
		std::vector<RenderableObject> objects;
		std::shared_ptr<Camera> camera;
		std::vector<std::shared_ptr<Light>> lights;
		glm::vec3 ambientLight;

		GLuint vertexAttrib, vertexNormalAttrib, modelMatrixUniform, viewMatrixUniform, projMatrixUniform, lightPosUniform, ambientLightUniform;
};


#endif
