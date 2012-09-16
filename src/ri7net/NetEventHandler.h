#pragma once

#include "enet/enet.h"

namespace ri7 {
namespace net {

	class NetEventHandler {
	public:
		virtual ~NetEventHandler(){}
		virtual void HandleEvent(ENetEvent &eevent)=0;
	};
}}
