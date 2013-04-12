
#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "World/Scene.hpp"
#include <memory>

class Application
{
	public:
		const float TRANSLATION_SPEED = 0.015;
		const float ROTATION_SPEED = 1.1;
		const glm::vec3 LIGHT_VECTOR = glm::vec3(0.0f, 0.0f, -0.01f);

	public:
		Application();
		void render();
		void onKey(unsigned char key, int, int);
		void onSpecialKey(int key, int, int);

	private:
		Scene scene;
		std::shared_ptr<Light> light = std::make_shared<Light>();

	private:
		void addGround();
		void addMandelbrot();
		void addModels();
		void addLight();
		void addCamera();

		void sleep(int milliseconds);
};

#endif
