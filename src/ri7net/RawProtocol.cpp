#include "RawProtocol.h"

#include "ConnectedProtocolEventHandler.h"
#include "DisconnectedProtocolEventHandler.h"

namespace ri7 {
namespace net {

	Protocol * RawProtocol::RawProtocolFactory::Instantiate()
	{
		return new RawProtocol();
	}

    void RawProtocol::Connect()
    {
        // Nothing to do, automatically connects
        if ( onConnected != NULL )
        {
            onConnected->HandleEvent();
        }
    }

    void RawProtocol::Disconnect()
    {
        // Nothing to do, automatically disconnects
        if ( onDisconnected != NULL )
		{
			onDisconnected->HandleEvent();
		}
    }

    bool RawProtocol::Available()
    {
		return outPacketDeque.empty() == false ;
    }

	const unsigned char * RawProtocol::GetBytes()
	{
		return outPacketDeque.front().data();
	}

	unsigned int RawProtocol::GetLength()
	{
		return (unsigned int)(outPacketDeque.front().length());
	}

	void RawProtocol::PopPacket()
	{
		outPacketDeque.pop_front();
	}

	void RawProtocol::PutUnsignedChar(unsigned char c)
	{
		outWritingPacket.append(1, c);
	}

	void RawProtocol::SendPacket()
	{
		outPacketDeque.push_back( outWritingPacket );
		outWritingPacket.clear();
	}


}}
