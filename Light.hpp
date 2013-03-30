
#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "glm/glm.hpp"

class Light
{
	public:
		Light(glm::vec3 position, glm::vec3 color, double power):
			position(position), color(color), power(power), emitting(true)
		{}



		void setPosition(glm::vec3 newPos)
		{
			position = newPos;
		}

		void setColor(glm::vec3 newColor)
		{
			color = newColor;
		}

		void setPower(double power)
		{
			power = power;
		}

		// Turn the light on or off
		void setEmitting(bool emitting)
		{
			emitting = true;
		}



		// Accessors
		glm::vec3 getPosition() const
		{
			return position;
		}

		glm::vec3 getColor()    const
		{
			return color;
		}

		double getPower()    const
		{
			return power;
		}

		bool getEmitting() const
		{
			return emitting;
		}

	private:
		glm::vec3 position, color;
		double power;
		bool emitting;
};

#endif
