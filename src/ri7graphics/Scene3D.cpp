#include "Scene3D.h"


namespace ri7 {
namespace graphics {

	Scene3D::Scene3D(void)
	{
	}
	Scene3D::~Scene3D(void)
	{
	}

	bool Scene3D::LoadScene(std::string filename)
	{
		if(!smgr)
			throw 5;

		Amesh = smgr->getMesh(filename.c_str());
		if (Amesh)
			Anode = smgr->addOctTreeSceneNode(Amesh->getMesh(0), 0, -1, 128);

		if(!Anode)
			return false;
	
		Anode->setMaterialFlag(EMF_LIGHTING, true);
		
		return true;

	}


}}
