#pragma once

#include "enet/enet.h"

namespace ri7 {
namespace net {

	class DisconnectedProtocolEventHandler {
	public:
		virtual ~DisconnectedProtocolEventHandler(){}
		virtual void HandleEvent()=0;
	};
}}
