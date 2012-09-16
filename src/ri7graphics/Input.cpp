#include "Input.h"

#include <iostream>
using namespace std;

namespace ri7 {
	namespace graphics {

Input::Input()
{
	for (u32 i=0; i<NUMBER_OF_KEYS; i++)
		Keys[i] = BS_UP;

	Mouse[MB_LEFT] = Mouse[MB_MIDDLE] = Mouse[MB_RIGHT] = BS_UP;

	MouseData.x = MouseData.y = MouseData.lx = MouseData.ly = MouseData.cx = MouseData.cy = 0;
	MouseData.wheelPos = MouseData.lwheelPos = 0;
}

Input::~Input() { }

bool Input::isKeyDown(EKEY_CODE key)
{
	if (Keys[key] == BS_DOWN)
		return true;
	return false;
}

bool Input::isKeyUp(EKEY_CODE key)
{
	if (Keys[key] == BS_UP)
		return true;
	return false;
}

bool Input::isMouseButtonDown(mouseButton mb)
{
	if (Mouse[mb] == BS_DOWN)
		return true;
	return false;
}

bool Input::isMouseButtonUp(mouseButton mb)
{
	if (Mouse[mb] == BS_UP)
		return true;
	return false;
}

u32 Input::getMouseX() { return MouseData.x; }
u32 Input::getMouseY() { return MouseData.y; }
u32 Input::getLastMouseX() { return MouseData.lx; }
u32 Input::getLastMouseY() { return MouseData.ly; }

u32 Input::getDeltaMouseX()
{
	s32 a = MouseData.x - MouseData.lx;
	return (u32)(a < 0 ? -a : a);
}

u32 Input::getDeltaMouseY()
{
	s32 a = MouseData.y - MouseData.ly;
	return (u32)(a < 0 ? -a : a);
}

u32 Input::getClickedMouseX() { return MouseData.cx; }
u32 Input::getClickedMouseY() { return MouseData.cy; }

f32 Input::getMouseWheelPosition() { return MouseData.wheelPos; }
f32 Input::getLastMouseWheelPosition() { return MouseData.lwheelPos; }

f32 Input::getDeltaMouseWheelPosition()
{
	f32 a = MouseData.wheelPos - MouseData.lwheelPos;
	return (f32)(a < 0 ? -a : a);
}

bool Input::OnEvent(const SEvent& event)
{
	switch (event.EventType) 
	{

	case EET_KEY_INPUT_EVENT:
		{
			if (event.KeyInput.PressedDown)
				Keys[event.KeyInput.Key] = BS_DOWN;
			else
				Keys[event.KeyInput.Key] = BS_UP;

			break;
		}

	case EET_MOUSE_INPUT_EVENT:
		{
			switch (event.MouseInput.Event)
			{
			case EMIE_MOUSE_MOVED:
				{
					MouseData.lx = MouseData.x;
					MouseData.ly = MouseData.y;
					MouseData.x = event.MouseInput.X;
					MouseData.y = event.MouseInput.Y;
				
					break;
				}

			case EMIE_MOUSE_WHEEL:
				{
					MouseData.lwheelPos = MouseData.wheelPos;
					MouseData.wheelPos += event.MouseInput.Wheel;

					break;
				}

			case EMIE_LMOUSE_PRESSED_DOWN:
				{
					Mouse[MB_LEFT] = BS_DOWN;
					MouseData.cx = event.MouseInput.X;
					MouseData.cy = event.MouseInput.Y;

					break;
				}

			case EMIE_LMOUSE_LEFT_UP:
				{
					Mouse[MB_LEFT] = BS_UP;

					break;
				}

			case EMIE_MMOUSE_PRESSED_DOWN:
				{
					Mouse[MB_MIDDLE] = BS_DOWN;
					MouseData.cx = event.MouseInput.X;
					MouseData.cy = event.MouseInput.Y;

					break;
				}

			case EMIE_MMOUSE_LEFT_UP:
				{
					Mouse[MB_MIDDLE] = BS_UP;

					break;
				}

			case EMIE_RMOUSE_PRESSED_DOWN:
				{
					Mouse[MB_RIGHT] = BS_DOWN;
					MouseData.cx = event.MouseInput.X;
					MouseData.cy = event.MouseInput.Y;
				
					break;
				}

			case EMIE_RMOUSE_LEFT_UP:
				{
					Mouse[MB_RIGHT] = BS_UP;

					break;
				}
			}
		}
		break;
	}
	return false;
}

}
}
