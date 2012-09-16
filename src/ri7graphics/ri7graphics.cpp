#include "ri7graphics.h"

namespace ri7 {
namespace graphics {

bool                Engine::engineStarted(false);
IrrlichtDevice *    Engine::device(NULL);
IVideoDriver*       Engine::driver(NULL);
ISceneManager*      Engine::smgr(NULL);
IGUIEnvironment*    Engine::guienv(NULL);
int					Engine::lastFPS(-1);
std::string			Engine::windowCaption("ri7Graphics ");
Input				Engine::input;

    Engine::Engine(void)
    {

    }

    Engine::~Engine(void)
    {

           if(engineStarted)
        {
            device->drop();
            device = NULL;
            driver = NULL;
            smgr = NULL;
            guienv = NULL;
            engineStarted=false;
        }
    }

    bool Engine::Start(void)
    {
        return Start(640,480,false);
    }

	bool Engine::Start(int w,int h,bool fullscreen)
	{

		device=createDevice( video::EDT_OPENGL ,core::dimension2d<s32>(w, h), 32,	fullscreen, true, false, 0);

        if(!device)
            return false;

		// /input=new Input();
		device->setEventReceiver(&input);

        device->setWindowCaption(L"Ri7Graphics Library");
        driver = device->getVideoDriver();
        smgr = device->getSceneManager();
        guienv = device->getGUIEnvironment();

        //TODO:Crear un Graphics::Camera
      //  smgr->addCameraSceneNode(0, core::vector3df(100,50,-100), core::vector3df(0,50,0));
		ICameraSceneNode *Camera=smgr->addCameraSceneNode(0, core::vector3df(0,150,0),core::vector3df(0,40,0));
		//Camera->setUpVector(core::vector3df(0,1,0));

	   // smgr->addCameraSceneNodeFPS();
        smgr->setShadowColor(video::SColor(150,0,0,0));
        smgr->addLightSceneNode(0,core::vector3df(0,100,0),video::SColorf(1.0f,1.0f,1.0f,0.0f),100);

        engineStarted=true;

        return engineStarted;
	}

    void Engine::Stop()
    {
         if(engineStarted)
        {
            device->closeDevice();
            smgr->clear();
            driver->drop();
            engineStarted=false;

        }

    }
	Input &Engine::GetInput()
	{
		return input;
	}

    bool Engine::run()
    {
        if(!engineStarted)
        {
            throw 5;
        }

        return(device->run());
	}

	void Engine::render()
	{
        if(!engineStarted)
        {
            throw 5;
        }
		driver->beginScene(true, true, SColor(255,100,101,140));
		smgr->drawAll();
		guienv->drawAll();
		driver->endScene();

		int fps = driver->getFPS();

		if (lastFPS != fps)
		{
			core::stringw str = windowCaption.c_str();
			str += " [";
			str += driver->getName();
			str += "] FPS:";
			str += fps;

			device->setWindowCaption(str.c_str());
			lastFPS = fps;
		}
	}

}
}
