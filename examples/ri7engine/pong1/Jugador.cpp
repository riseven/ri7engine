#include "Jugador.h"

Jugador::Jugador()
{
	this->pos.X=0;
	this->pos.Y=0;
	this->vel=0;
	this->Grafico=new GraficoPala();
}

Jugador::~Jugador()
{

}

void Jugador::SetX(float x)
{
	this->pos.X=x;
	UpdateGrafico();
}

void Jugador::SetY(float y)
{
	this->pos.Y=y;
	if(this->pos.Y > 90.0f)
	{
		this->pos.Y = (2 * 90.0f) - pos.Y ;
		this->SetVel( -vel );
	}else if(this->pos.Y < -90.0f)
	{
		this->pos.Y = (2 * -90.0f) - pos.Y ;
		this->SetVel( -vel );
	}

	UpdateGrafico();
}

void Jugador::Update()
{
	this->SetVel( vel+accel );
	float a1 = 0.005f;
	float a2 = 0.1f; //0.1f;
	float b2 = 3.0f; //2.0f;
	float res = a1*fabs(vel) + a2*pow(fabs(vel), b2) ;
	this->SetVel( vel + (vel>0?-res:res) );
	this->SetY(pos.Y + vel);
}
void Jugador::UpdateGrafico()
{
	this->Grafico->setPosition(pos.Y,0,pos.X);
}

void Jugador::SetVel(float vel)
{
	this->vel=vel;
}

void Jugador::SetAccel(float accel)
{
	this->accel = accel;
}