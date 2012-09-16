#include "GraficoPala.h"

GraficoPala::GraficoPala()
{
	this->x=0.0f;
	this->y=0.0f;
	this->z=0.0f;
	this->CargaModelo("../../media/pala.b3d");
}

GraficoPala::~GraficoPala()
{

}

void GraficoPala::CargaModelo(std::string filename)
{
	this->LoadAnimatedMesh(filename);
}

void GraficoPala::setPosition(float x,float y,float z)
{
	this->x=x;
	this->y=y;
	this->z=z;

	Object3D::setPosition(core::vector3df(x,y,z));
}