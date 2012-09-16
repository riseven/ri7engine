#pragma once

#include "UdpSocket.h"
#include "Protocol.h"
#include "NetEventHandler.h"
#include "ConnectedProtocolEventHandler.h"
#include "DisconnectedProtocolEventHandler.h"

#include <string>

namespace ri7 {
namespace net {

    class Client
    {
	public:
		enum State { PRECONNECT, CONNECTING, CONNECTED, DISCONNECTING, DISCONNECTED };

		// Evento que se dispara cuando el Socket UDP se conecta
		class OnConnectedSocketEventHandler : public NetEventHandler
		{
        private:
		    Client *client;
        public:
            OnConnectedSocketEventHandler(Client *client):client(client){}
            void HandleEvent(ENetEvent &eevent);
		};

		// Evento que se dispara cuando el Socket UDP se desconecta
		class OnDisconnectedSocketEventHandler : public NetEventHandler
		{
		private:
			Client *client;
		public:
			OnDisconnectedSocketEventHandler(Client *client):client(client){}
			void HandleEvent(ENetEvent &eevent);
		};

		// Evento que se dispara cuando el protocolo 0 del cliente se conecta
		class OnConnectedProtocolEventHandler : public ConnectedProtocolEventHandler
		{
        private:
		    Client *client;
        public:
            OnConnectedProtocolEventHandler(Client *client):client(client){}
            void HandleEvent();
		};

		// Evento que se dispara cuando el protocolo 0 del cliente se desconecta
		class OnDisconnectedProtocolEventHandler : public DisconnectedProtocolEventHandler
		{
		private:
			Client *client;
		public:
			OnDisconnectedProtocolEventHandler(Client *client):client(client){}
			void HandleEvent();
		};

    private:
        UdpSocket *socket;
		ENetPeer *peer;
        Protocol *protocol;
		State state;

		std::string remoteHost;
		int remotePort;

    public:
        Client();
        virtual ~Client();

		void SetRemoteHost(std::string remoteHost);
		void SetRemotePort(int remotePort);
		void SetProtocol(Protocol *protocol);

		State GetState();

		void Connect();
		void Disconnect();
		void Update();


		void WaitConnect(int milliseconds);
    };

}}
