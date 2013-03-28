
#include "Scene.cpp"


Scene::Scene(const shared_ptr<Camera>& camera):
	camera(camera);
{}



void render()
{
	for_each (models.begin(), models.end(),
		[&](const std::shared_ptr<Model>& model)
		{
			model.render(camera, );
		});
}



void addModel(const std::shared_ptr<Model>& newModel)
{
	models.push_back(newModel);
}



std::shared_ptr<Camera> getCamera()
{
	return camera;
}

