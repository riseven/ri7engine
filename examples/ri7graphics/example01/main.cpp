#include "MyPlayer.h"
#include "ri7graphics/Scene3D.h"

int main(int argc, char **argv)
{
	//Iniciamos el Engine con una resolución de 640x480
    Engine::Start(640,480);

	//Creamos nuestros objetos MyPlayer pasandole por referencia el Modelo 3D a cargar

	MyPlayer Raptor("../../media/raptor.b3d");
	MyPlayer Raptor2("../../media/raptor.b3d");

    //En este caso utilizamos la clase Scene3D de la libreria
	Scene3D Suelo;

	//Cargamos la Escena 3D para el suelo
    Suelo.LoadScene("../../media/testmap.dmf");

	//Colocamos al Raptor en la posición 0,-5,0 y -50,-5,100

    Raptor.setPosition(core::vector3df(0.0f,-5.0f,0));
	Raptor2.setPosition(core::vector3df(-50.0f,-5.0f,100.0f));

	//Colocamos la rotacion del raptor a 0º en todos los ejes
	Raptor.setRotation(core::vector3df(0,0,0));
	Raptor2.setRotation(core::vector3df(0,0,0));

	Raptor2.SetTexture("../../media/body2.bmp");
	Raptor2.SetTexture("../../media/head2.bmp",1);

	//Comprueba que el Engine grafico este activo
     while(Engine::run())
    {
		//Pequeña funcion para Rotar 0,2º el Raptor
        Raptor.RotateY(0.2f);
		Raptor2.RotateY(0.3f);
		//Pequeña función para hacer avanzar al Raptor segun su angulo
        Raptor.Advance(0.5f);
		Raptor2.Advance(0.4f);
		//Renderizamos pa pantalla y voila!
        Engine::render();
    }

	//Finalizamos el Engine
	Engine::Stop();

    return 0;
}
