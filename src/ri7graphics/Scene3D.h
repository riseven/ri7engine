#pragma once

#include "ri7graphics.h"

namespace ri7 {
namespace graphics {

	 class Scene3D:protected Engine
    {
    protected:
        IAnimatedMesh* Amesh;
        ISceneNode	*Anode;

    public:
        Scene3D(void);
       ~Scene3D(void);

        bool LoadScene(std::string filename);

        inline void setPosition(core::vector3df pos)
        {
            this->Anode->setPosition(pos);
        }
        inline core::vector3df getPosition()
        {
            return this->Anode->getPosition();
        }

        inline void setRotation(core::vector3df rot)
        {
            this->Anode->setRotation(rot);
        }

        inline core::vector3df getRotation()
        {
           return this->Anode->getRotation();
        }


    };

}}

