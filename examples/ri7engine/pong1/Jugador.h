#pragma once

#include "GraficoPala.h"

class Jugador{
private:
	core::vector2df pos;
	float vel;
	float accel;
	GraficoPala *Grafico;
	void UpdateGrafico();

public:
	Jugador();
	~Jugador();
	void SetY(float y);
	void SetX(float x);
	void SetVel(float vel);
	void SetAccel(float accel);
	virtual void Update();
	inline float GetX()
	{
		return this->pos.X;
	}

	inline float GetY()
	{
		return this->pos.Y;
	}


};