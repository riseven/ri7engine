#include "GraficoBola.h"
#include "GraficoEscenario.h"
#include "JugadorLocal.h"
#include "ri7graphics\Input.h"

int main(int argc, char **argv)
{
	//Iniciamos el Engine con una resolución de 640x480
	Engine::Start(640,480);
	Input &Controlador=Engine::GetInput();
	JugadorLocal Player1;

	GraficoBola Bola;
	
	GraficoEscenario Escenario;
	
	Engine::SetWindowCaption("Ri7Pong");
	Player1.SetX(100.0f);

	//Comprueba que el Engine grafico este activo
	while(Engine::run())
	{
		Player1.Update();
		cout << "Y= " << Player1.GetY() << endl;
		Engine::render();
	}

	//Finalizamos el Engine
	Engine::Stop();

	return 0;
}
