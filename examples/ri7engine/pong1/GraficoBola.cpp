#include "GraficoBola.h"

GraficoBola::GraficoBola()
{
	this->x=0.0f;
	this->y=0.0f;
	this->z=0.0f;
	
	CargaModelo("../../media/bola.b3d");
}

GraficoBola::~GraficoBola()
{

}

void GraficoBola::CargaModelo(std::string filename)
{
	this->LoadAnimatedMesh(filename);
}

void GraficoBola::setPosition(float x,float y,float z)
{
	this->x=x;
	this->y=y;
	this->z=z;

	Object3D::setPosition(core::vector3df(x,y,z));
}
