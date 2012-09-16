#pragma once

#include "ri7graphics/Scene3D.h"

using namespace ri7;
using namespace graphics;

class GraficoEscenario : public Scene3D
{
private:
	void CargaModelo(std::string filename);

public:

	GraficoEscenario();
	~GraficoEscenario();

	void setPosition(float x,float y,float z);
	inline core::vector3df getPosition()
	{
		return this->getPosition();
	}
};