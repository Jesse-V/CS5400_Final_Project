
#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "glm/glm.hpp"

class Light
{
	public:
		Light(glm::vec3 position, glm::vec3 color, double power);

		void setPosition(glm::vec3 newPos);
		void setColor(glm::vec3 newColor);
		void setPower(double power);
		void setEmitting(bool emitting);

		glm::vec3 getPosition() const;
		glm::vec3 getColor()    const;
		double getPower()    const;
		bool getEmitting() const;

	private:
		glm::vec3 position, color;
		double power;
		bool emitting;
};

#endif
