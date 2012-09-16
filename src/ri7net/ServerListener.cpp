#include "ServerListener.h"

#include "ProtocolFactory.h"

#include <iostream>

using std::string;

namespace ri7 {
namespace net {

	ServerListener::ServerListener()
	{
		socket = NULL;
		state = PRESTART;
		localHost = "";
		localPort = 0;
		maxConnections = 64;
	}

	ServerListener::~ServerListener()
	{
		// ServerListenr shouldn't be destroyed before it's is correctly finalized
		if (state != PRESTART && state != STOPPED)
		{
			throw 5; // TODO: Use ri7::core::Exception
		}

		socket = NULL;
		state = STOPPED;
	}

	void ServerListener::SetProtocolFactory(ProtocolFactory *protocolFactory)
	{
		this->protocolFactory = protocolFactory;
	}

	void ServerListener::SetLocalHost(string localHost)
	{
		this->localHost = localHost;
	}

	void ServerListener::SetLocalPort(int localPort)
	{
		this->localPort = localPort;
	}

	void ServerListener::SetMaxConnections(int maxConnections)
	{
		this->maxConnections = maxConnections;
	}

	ServerListener::State ServerListener::GetState()
	{
		return state;
	}

	void ServerListener::Start()
	{
		std::cout << "Start" << std::endl;
		if ( state != PRESTART )
		{
			throw 5; // TODO: Use ri7::core::Exception
		}

		// Configure socket
		socket = new UdpSocket();
		socket->SetLocalHost(localHost);
		socket->SetLocalPort(localPort);
		socket->SetMaxConnections(maxConnections);
		socket->SetOnConnected(new OnConnectedSocketEventHandler(this) );
		socket->SetOnDisconnected(new OnDisconnectedSocketEventHandler(this) );
		socket->SetOnReceiveData(new OnReceiveDataSocketEventHandler(this) );
		
		// Start listening
		socket->Start();
	}

	void ServerListener::Stop()
	{
		std::cout << "Stop" << std::endl;
		if ( state == STOPPING || state == STOPPED )
		{
			throw 5; // TODO: Use ri7::core::Exception
		}

		// TODO: ¿Disconnect peers?

		socket->Stop();
		state = STOPPED;
	}

    void ServerListener::OnConnectedSocketEventHandler::HandleEvent(ENetEvent &eevent)
    {
		std::cout << "OnConnectedSocket" << std::endl;
		// Create ServerClient
		ServerClient *client = new ServerClient(
			listener->socket, 
			eevent.peer, 
			listener->protocolFactory->Instantiate());

		// Save ServerClient pointer in peer data
		eevent.data = (enet_uint32)client;
    }

	void ServerListener::OnDisconnectedSocketEventHandler::HandleEvent(ENetEvent &eevent)
	{
		std::cout << "OnDisconnectedSocket" << std::endl;
		// Disconnection process is finished
		//client->state = DISCONNECTED;
		// TODO: Here an event shold be raised
	}

	void ServerListener::OnReceiveDataSocketEventHandler::HandleEvent(ENetEvent &eevent)
	{
		std::cout << "OnReceiveDataSocketEventHandler" << std::endl;
	}

	void ServerListener::Update()
	{
		socket->Update();
	}

}}
