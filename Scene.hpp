#ifndef SCENE_HPP
#define SCENE_HPP

#include "Camera.hpp"
#include "Model.hpp"
#include <memory>
#include <vector>

class Scene
{
	public:
		Scene(const shared_ptr<Camera>& camera);
		void render();
		void addModel(const std::shared_ptr<Model>& model);
		shared_ptr<Camera> getCamera();

	private:
		std::vector<std::shared_ptr<Model>> models;
		std::shared_ptr<Camera> camera;
};

#endif
