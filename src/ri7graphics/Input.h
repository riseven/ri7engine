#pragma once

#include "irrlicht/irrlicht.h"

using namespace irr;

#define NUMBER_OF_KEYS KEY_KEY_CODES_COUNT
#define NUMBER_OF_MOUSE_BUTTONS 3

enum buttonState {
	BS_UP ,
	BS_DOWN
};

enum mouseButton {
	MB_LEFT,
	MB_MIDDLE,
	MB_RIGHT
};

struct mouseInformation {
	u32 x, y, lx, ly, cx, cy;
	f32 wheelPos, lwheelPos;
};

//class CIrrEventReceiver : public IEventReceiver

namespace ri7 {
	namespace graphics {

		class Input :public IEventReceiver
		{
		public:
			Input();
			~Input();

			bool isKeyDown(EKEY_CODE key);
			bool isKeyUp(EKEY_CODE key);

			bool isMouseButtonDown(mouseButton mb);
			bool isMouseButtonUp(mouseButton mb);

			u32 getMouseX();
			u32 getMouseY();
			u32 getLastMouseX();
			u32 getLastMouseY();
			u32 getDeltaMouseX();
			u32 getDeltaMouseY();
			u32 getClickedMouseX();
			u32 getClickedMouseY();

			f32 getMouseWheelPosition();
			f32 getLastMouseWheelPosition();
			f32 getDeltaMouseWheelPosition();

			//bool OnEvent(SEvent event);
			virtual bool OnEvent(const SEvent& event);
		protected:
			buttonState Keys[NUMBER_OF_KEYS];
			buttonState Mouse[NUMBER_OF_MOUSE_BUTTONS];
			mouseInformation MouseData;

		};
	}
}