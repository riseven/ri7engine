#include "Object3D.h"


namespace ri7 {
namespace graphics {

Object3D::Object3D()
{
}


Object3D::~Object3D()
{

}


bool Object3D::LoadMesh(std::string filename)
{
	return true;
}

bool Object3D::LoadAnimatedMesh(std::string filename)
{
	if(!smgr)
		throw 5;

	Amesh = smgr->getMesh(filename.c_str());
	if (Amesh)
		Anode = smgr->addAnimatedMeshSceneNode( Amesh );

	if(!Anode)
		return false;

	Anode->addShadowVolumeSceneNode();
	//Anode->setDebugDataVisible(EDS_FULL);

	//Anode->setMaterialFlag(EMF_LIGHTING, false);
	//Anode->setFrameLoop(0,25);

	return true;

}

void Object3D::SetTexture(std::string texturefile,int material)
{
	Anode->getMaterial(material).setTexture(0,driver->getTexture(texturefile.c_str()));

}


}}

