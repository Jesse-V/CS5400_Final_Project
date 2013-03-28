#ifndef MODEL_HPP
#define MODEL_HPP

#include "Mesh.hpp"
#include "Camera.hpp"
#include "Triangle.struct"

class Model
{
	public:
		Model(const Mesh& mesh);
		void render(const Camera& camera);

	private:
		std::shared_ptr<Mesh> mesh;
		std::shared_ptr<Point> location;

	//eventually it'd be nice to support multiple meshes and paired matrix transformations
};

#endif
