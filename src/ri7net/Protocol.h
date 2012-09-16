#pragma once

#ifndef NULL
#define NULL 0
#endif

namespace ri7 {
namespace net {

    class ConnectedProtocolEventHandler;
	class DisconnectedProtocolEventHandler;

    class Protocol {
    protected:
        ConnectedProtocolEventHandler *onConnected;
		DisconnectedProtocolEventHandler *onDisconnected;

    public:
        Protocol();

        void SetOnConnected(ConnectedProtocolEventHandler *onConnectedEventHandler);
		void SetOnDisconnected(DisconnectedProtocolEventHandler *onDisconnectedEventHandler);

        virtual void Connect()=0;
        virtual void Disconnect()=0;
        virtual bool Available()=0;
        virtual const unsigned char *GetBytes()=0;
        virtual unsigned int GetLength()=0;
        virtual void PopPacket()=0;
    };
}}
