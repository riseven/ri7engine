#include "Protocol.h"

#include "ConnectedProtocolEventHandler.h"
#include "DisconnectedProtocolEventHandler.h"

namespace ri7 {
namespace net {

    Protocol::Protocol()
    {
        onConnected = NULL;
		onDisconnected = NULL;
    }

    void Protocol::SetOnConnected(ConnectedProtocolEventHandler *onConnectedEventHandler)
    {
        onConnected = onConnectedEventHandler;
    }

	void Protocol::SetOnDisconnected(DisconnectedProtocolEventHandler *onDisconnectedEventHandler)
	{
		onDisconnected = onDisconnectedEventHandler;
	}

}}
