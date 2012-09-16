#pragma once


#include "irrlicht/irrlicht.h"
#include "Input.h"

#include <iostream>
#include <string>

#define GRAD_PI (180.0 / 3.14159)

using namespace irr;

using namespace std;
using namespace scene;
using namespace video;
using namespace gui;

namespace ri7 {
namespace graphics {

    class Engine
    {
    private:
        static bool engineStarted;
		static int lastFPS;
		static std::string windowCaption;
		static Input input;
    protected:

        static IrrlichtDevice *device;
        static IVideoDriver* driver;
        static ISceneManager* smgr ;
        static IGUIEnvironment* guienv;

    public:
        Engine(void);
        ~Engine(void);
        static bool Start();
		static bool Start(int w,int h,bool fullscreen=false);

		static Input &GetInput();
		
		static void SetWindowCaption(std::string caption)
		{
			windowCaption=caption;
		}
        static bool isStarted()
        {
            return engineStarted;
        }
        static bool run();
        static void render();
        static void Stop();

    };

}}
