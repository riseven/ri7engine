#pragma once

#include "UdpSocket.h"
#include "Protocol.h"
#include "ServerClient.h"
#include "NetEventHandler.h"
#include "ConnectedProtocolEventHandler.h"
#include "DisconnectedProtocolEventHandler.h"


#include <string>
#include <list>

namespace ri7 {
namespace net {

	class ProtocolFactory;

    class ServerListener
    {
	public:
		enum State { PRESTART, STARTED, STOPPING, STOPPED };

		// Evento que se dispara cuando el Socket UDP se conecta
		class OnConnectedSocketEventHandler : public NetEventHandler
		{
        private:
		    ServerListener *listener;
        public:
            OnConnectedSocketEventHandler(ServerListener *listener):listener(listener){}
            void HandleEvent(ENetEvent &eevent);
		};

		// Evento que se dispara cuando el Socket UDP se desconecta
		class OnDisconnectedSocketEventHandler : public NetEventHandler
		{
		private:
			ServerListener *listener;
		public:
			OnDisconnectedSocketEventHandler(ServerListener *listener):listener(listener){}
			void HandleEvent(ENetEvent &eevent);
		};

		// Evento que se dispara cuando el Socket UDP recibe datos
		class OnReceiveDataSocketEventHandler : public NetEventHandler
		{
		private:
			ServerListener *listener;
		public:
			OnReceiveDataSocketEventHandler(ServerListener *listener):listener(listener){}
			void HandleEvent(ENetEvent &eevent);
		};


    private:
        UdpSocket *socket;

		State state;
		ProtocolFactory *protocolFactory;
		std::string localHost;
		int localPort;
		int maxConnections;

		std::list<ServerClient *> clients; // TODO: Efficient slot management

    public:
        ServerListener();
        virtual ~ServerListener();

		void SetProtocolFactory(ProtocolFactory *protocolFactory);
		void SetLocalHost(std::string localHost);
		void SetLocalPort(int localPort);
		void SetMaxConnections(int maxConnections);
		//void SetProtocol(Protocol *protocol);

		State GetState();

		void Start();
		void Stop();
		void Update();
    };

}}
