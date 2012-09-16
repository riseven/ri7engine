#include "JugadorLocal.h"

JugadorLocal::JugadorLocal()
{

}

JugadorLocal::~JugadorLocal()
{

}

void JugadorLocal::Update()
{
	if(Engine::GetInput().isKeyDown(KEY_UP)==true)
	{
		this->SetAccel(1.0f);
	}
	else
	{
		if(Engine::GetInput().isKeyDown(KEY_DOWN)==true)
		{
			this->SetAccel(-1.0f);
		}
		else
		{
			this->SetAccel(0.0f);
		}
	}
	Jugador::Update();
}