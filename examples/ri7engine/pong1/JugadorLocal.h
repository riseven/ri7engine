#pragma once
#include "Jugador.h"

class JugadorLocal  : public Jugador
{
public:
	JugadorLocal();
	~JugadorLocal();

	virtual void Update();
};