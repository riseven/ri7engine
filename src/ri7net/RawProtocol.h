#pragma once

#include "Protocol.h"
#include "ProtocolFactory.h"

#include <string>
#include <deque>

namespace ri7 {
namespace net {

    class ConnectedProtocolEventHandler;

    // Protocolo bidireccional simétrico de envío de datos simples
    class RawProtocol : public Protocol {
		class RawProtocolFactory : ProtocolFactory {
		public:
			virtual Protocol * Instantiate();
		};

    private:
		std::deque< std::basic_string<unsigned char> > outPacketDeque;
		std::basic_string<unsigned char> outWritingPacket;

		std::deque< std::basic_string<unsigned char> > inPacketDeque;
		std::basic_string<unsigned char> inReceivingPacket;

    public:
        virtual void Connect();
        virtual void Disconnect();
        virtual bool Available();
        virtual const unsigned char *GetBytes();
        virtual unsigned int GetLength();
        virtual void PopPacket();

		void PutUnsignedChar(unsigned char c);
		void SendPacket();
    };
}}
