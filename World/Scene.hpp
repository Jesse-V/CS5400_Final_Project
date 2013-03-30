
#ifndef SCENE_HPP
#define SCENE_HPP

#include "Light.hpp"
#include "ShaderLoader/Program.hpp"
#include "Modeling/RenderedObject.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>


class Scene
{
	public:
		void init();
		void loadCubeModel(glm::mat4 modelmatrix = glm::translate(glm::mat4(), glm::vec3(0.0, -0.1, 0.0)));
		void clear();
		void addLight(const Light &);
		void setAmbientLight(glm::vec3 rgb); // (0,0,0) is total darkness, (1.0,1,0,1,0) is total light
		void render(const glm::vec3& eyePosition, const glm::vec3& lookDirection, const glm::vec3& upVector, const glm::mat4& projMatrix);
		std::shared_ptr<cs5400::Program> getProgram();

	private:
		std::shared_ptr<cs5400::Program> program;
		std::vector<RenderedObject> objects;
		std::vector<Light> lights;
		glm::vec3 ambientLight;

		GLuint vertexAttrib, vertexNormalAttrib, modelMatrixUniform, viewMatrixUniform, projMatrixUniform, lightPosUniform, ambientLightUniform;
};


#endif
