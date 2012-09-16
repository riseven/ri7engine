#pragma once

#include "ri7graphics/Object3D.h"

using namespace ri7;
using namespace graphics;

class GraficoPala: public Object3D
{
private:

	float x,y,z;
	void CargaModelo(std::string filename);

public:

	GraficoPala();
	~GraficoPala();


	void setPosition(float x,float y,float z);
	inline core::vector3df getPosition()
	{
		return this->getPosition();
	}
	
	inline float getX()
	{
		return this->x;
	}

	inline float getY()
	{
		return this->y;
	}

	inline float getZ()
	{
		return this->z;
	}
};