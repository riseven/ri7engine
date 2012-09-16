#include "GraficoEscenario.h"


GraficoEscenario::GraficoEscenario()
{
	this->CargaModelo("../../media/escenario.b3d");
}

GraficoEscenario::~GraficoEscenario()
{

}

void GraficoEscenario::CargaModelo(std::string filename)
{
	this->LoadScene(filename);
}

void GraficoEscenario::setPosition(float x,float y,float z)
{
	Scene3D::setPosition(core::vector3df(x,y,z));
}

