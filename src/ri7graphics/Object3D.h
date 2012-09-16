#pragma once

#include "ri7graphics.h"

namespace ri7 {
namespace graphics {

   class Object3D:protected Engine
    {
    protected:
        IAnimatedMesh* Amesh;
        IAnimatedMeshSceneNode* Anode;

        IMesh *mesh;
        ISceneNode	*node;

    public:
        Object3D(void);
       ~Object3D(void);

        bool LoadMesh(std::string filename);
        bool LoadAnimatedMesh(std::string filename);
		void SetTexture(std::string texturefile,int material = 0);

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
