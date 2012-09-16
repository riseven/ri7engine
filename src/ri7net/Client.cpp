#include "Client.h"

#include <iostream>

using std::string;

namespace ri7 {
namespace net {

	Client::Client()
	{
		socket = NULL;
		state = PRECONNECT;
		remoteHost = "";
		remotePort = 0;
	}

	Client::~Client()
	{
		// Client shouldn't be destroyed before it's is correctly finalized
		if (state != PRECONNECT && state != DISCONNECTED)
		{
			throw 5; // TODO: Use ri7::core::Exception
		}

		socket = NULL;
		state = DISCONNECTED;
	}

	void Client::SetRemoteHost(string remoteHost)
	{
		this->remoteHost = remoteHost;
	}

	void Client::SetRemotePort(int remotePort)
	{
		this->remotePort = remotePort;
	}

	void Client::SetProtocol(Protocol *protocol)
	{
	    this->protocol = protocol;
	}

	Client::State Client::GetState()
	{
		return state;
	}

	void Client::Connect()
	{
		std::cout << "Connect" << std::endl;
		if ( state != PRECONNECT )
		{
			throw 5; // TODO: Use ri7::core::Exception
		}

		// Configure socket
		socket = new UdpSocket();
		socket->SetRemoteHost(remoteHost);
		socket->SetRemotePort(remotePort);
		socket->SetOnConnected( new OnConnectedSocketEventHandler(this) );
		socket->SetOnDisconnected( new OnDisconnectedSocketEventHandler(this) );

		// Configure protocol
		protocol->SetOnConnected( new OnConnectedProtocolEventHandler(this) );
		protocol->SetOnDisconnected( new OnDisconnectedProtocolEventHandler(this) );

        // Start connecting process
        socket->Connect();
		state = CONNECTING;
	}

	void Client::Disconnect()
	{
		std::cout << "Disconnect" << std::endl;
		if ( state == DISCONNECTED || state == DISCONNECTING )
		{
			throw 5; // TODO: Use ri7::core::Exception
		}

		// Disconnect protocol
		protocol->Disconnect();
	}

    void Client::OnConnectedSocketEventHandler::HandleEvent(ENetEvent &eevent)
    {
		std::cout << "OnConnectedSocket" << std::endl;
		client->peer = eevent.peer;
        // Connect root protocol
        client->protocol->Connect();
    }

	void Client::OnDisconnectedSocketEventHandler::HandleEvent(ENetEvent &eevent)
	{
		std::cout << "OnDisconnectedSocket" << std::endl;
		// Disconnection process is finished
		client->state = DISCONNECTED;
		// TODO: Here an event shold be raised
	}

    void Client::OnConnectedProtocolEventHandler::HandleEvent()
    {
		std::cout << "OnConnectedProtocol" << std::endl;
		// Connection proccess is finished
        client->state = CONNECTED;
		// TODO: Here an event should be raised
    }

	void Client::OnDisconnectedProtocolEventHandler::HandleEvent()
	{
		std::cout << "OnDisconnectedProtocol" << std::endl;
		// Disconnect socket
		client->socket->Disconnect(client->peer);
	}

	void Client::Update()
	{
		// Check incoming events from socket
		socket->Update();

		if ( state == CONNECTED )
		{
			// Flush protocol (TODO: Flush, not only 1 packet)
			if ( protocol->Available() )
			{
				// TODO: const uchar * to uchar* ??, look ENet source
				socket->SendPacket(peer, (unsigned char *)protocol->GetBytes(), protocol->GetLength());
				protocol->PopPacket();
			}
		}
	}

	void Client::WaitConnect(int milliseconds)
	{
		if ( state != CONNECTING )
		{
			throw 5; // TODO: Use ri7::core::Exception
		}
	}

}}
