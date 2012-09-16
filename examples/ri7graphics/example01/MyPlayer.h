#pragma once

//Necesario para utilizar la Libreria Ri7Graphics
#include "ri7graphics/Object3D.h"


//Espacio de Nombres de la Libreria
using namespace ri7;
using namespace graphics;


//Una clase que hereda de Object3D para realizar la demostración

class MyPlayer:public Object3D
{
public:
		MyPlayer()
		{
		}

		MyPlayer(std::string filename)
		{
			this->LoadAnimatedMesh(filename);
		}

		~MyPlayer()
		{
		}

			void Advance(float distance)
        {
            float x=this->getPosition().X;
            float y=this->getPosition().Y;
            float z=this->getPosition().Z;
            float orientation=this->getRotation().Y-180.0f;
    
			x+=sinf(orientation/(float)GRAD_PI)*distance;
            z+=cosf(orientation/(float)GRAD_PI)*distance;

            this->setPosition(core::vector3df(x,y,z));
        }
			void RotateY(float angles)
        {
            float rx=this->getRotation().X;
            float ry=this->getRotation().Y;
            float rz=this->getRotation().Z;

            ry+=angles;

            this->setRotation(core::vector3df(rx,ry,rz));

        }
};
