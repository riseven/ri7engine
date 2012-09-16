#pragma once

#include "NetEventHandler.h"
#include "ConnectedProtocolEventHandler.h"
#include "DisconnectedProtocolEventHandler.h"

#include "enet/enet.h"


namespace ri7 {
namespace net {

	class UdpSocket;
	class Protocol;

	class ServerClient {
		public:
		enum State { CONNECTING, CONNECTED, DISCONNECTING, DISCONNECTED };

		// Evento que se dispara cuando el Socket UDP se desconecta
		class OnDisconnectedSocketEventHandler : public NetEventHandler
		{
		private:
			ServerClient *serverClient;
		public:
			OnDisconnectedSocketEventHandler(ServerClient *serverClient):serverClient(serverClient){}
			void HandleEvent(ENetEvent &eevent);
		};

		
		// Evento que se dispara cuando el protocolo 0 del cliente se conecta
		class OnConnectedProtocolEventHandler : public ConnectedProtocolEventHandler
		{
        private:
		    ServerClient *serverClient;
        public:
            OnConnectedProtocolEventHandler(ServerClient *serverClient):serverClient(serverClient){}
            void HandleEvent();
		};

		// Evento que se dispara cuando el protocolo 0 del cliente se desconecta
		class OnDisconnectedProtocolEventHandler : public DisconnectedProtocolEventHandler
		{
		private:
			ServerClient *serverClient;
		public:
			OnDisconnectedProtocolEventHandler(ServerClient *serverClient):serverClient(serverClient){}
			void HandleEvent();
		};
		

    private:
        UdpSocket *socket;
		ENetPeer *peer;
        Protocol *protocol;
		State state;

    public:
        ServerClient(UdpSocket *socket, ENetPeer *peer, Protocol *protocol);
        virtual ~ServerClient();

		State GetState();

		void Disconnect();
		void Update();
	};
}}
