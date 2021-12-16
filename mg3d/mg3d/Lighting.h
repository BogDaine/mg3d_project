#pragma once
#include "Maths.h"

struct Material
{
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float shininess;

	Material& operator = (const Material& val)
	{
		Material aux;

		ambient = val.ambient;
		diffuse = val.diffuse;
		specular = val.specular;
		shininess = val.shininess;

		aux.ambient = val.ambient;
		aux.diffuse = val.diffuse;
		aux.specular = val.specular;
		aux.shininess = val.shininess;

		return aux;
	}
};

struct Light
{
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	Light& operator = (const Light& val)
	{
		Light aux;
		position = val.position;
		ambient = val.ambient;
		diffuse = val.diffuse;
		specular = val.specular;

		aux.position = position;
		aux.ambient = ambient;
		aux.diffuse = diffuse;
		aux.specular = specular;

		return aux;
	}
};

namespace materials_nsp {
	const Material GOLD{ glm::vec3(0.24725f, 0.1995f, 0.0745f),
							glm::vec3(0.75164f, 0.60648f, 0.22648f),
							glm::vec3(0.628281f, 0.555802f, 0.366065f), 0.6f * 128 };

	const Material RUBY{ glm::vec3(0.1745f, 0.01175f, 0.01175f),
							glm::vec3(0.61424f, 0.04136f, 0.04136f),
							glm::vec3(0.727811f, 0.626959f, 0.626959f), 0.4f * 128 };

	const Material PEARL{ glm::vec3(0.25f, 0.20725f, 0.20725f),
							glm::vec3(1.0f, 0.829f, 0.829f),
							glm::vec3(0.296648f, 0.296648f, 0.296648f), 0.088f * 128 };

	const Material CHROME{ glm::vec3(0.25f, 0.25f, 0.25f),
							glm::vec3(0.4f, 0.4f, 0.4f),
							glm::vec3(0.774597f, 0.774597f, 0.774597f), 0.6f * 128 };

	const Material QUARTZ{ glm::vec3(0.25f, 0.25f, 0.25f),
							glm::vec3(1.0f, 1.0f, 1.0f),
							glm::vec3(0.9f, 0.9f, 0.774597f), 0.6f * 128 };

}

namespace lights
{
	const Light WHITE{ glm::vec3(1.0f, 1.0f, 1.0f),
						glm::vec3(0.3f, 0.3f, 0.3f),
						glm::vec3(1.0f, 1.0f, 1.0f),
						glm::vec3(1.0f, 1.0f, 1.0f) };

	const Light GREENISH{ glm::vec3(1.0f, 1.0f, 1.0f),
					glm::vec3(0.3f, 0.5f, 0.3f),
					glm::vec3(0.5f, 1.0f, 0.5f),
					glm::vec3(0.5f, 1.0f, 0.5f) };
}