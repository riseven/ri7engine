#pragma once

#include "enet/enet.h"

namespace ri7 {
namespace net {

	class ConnectedProtocolEventHandler {
	public:
		virtual ~ConnectedProtocolEventHandler(){}
		virtual void HandleEvent()=0;
	};
}}
