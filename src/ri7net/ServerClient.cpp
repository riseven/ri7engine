#include "ServerClient.h"

#include "Protocol.h"
#include "UdpSocket.h"

#include <iostream>

using std::string;

namespace ri7 {
namespace net {

	ServerClient::ServerClient(UdpSocket *socket, ENetPeer *peer, Protocol *protocol)
	{
		this->socket = socket;
		this->peer = peer;
		this->protocol = protocol;

		// Configure protocol
		protocol->SetOnConnected( new OnConnectedProtocolEventHandler(this) );
		protocol->SetOnDisconnected( new OnDisconnectedProtocolEventHandler(this) );

		// Connect protocol
		protocol->Connect();
		state = CONNECTING;
	}

	ServerClient::~ServerClient()
	{
		// ServerClient shouldn't be destroyed before it is correctly finalized
		if (state != DISCONNECTED)
		{
			throw 5; // TODO: Use ri7::core::Exception
		}

		socket = NULL;
		peer = NULL;
		state = DISCONNECTED;
	}

	ServerClient::State ServerClient::GetState()
	{
		return state;
	}

	void ServerClient::Disconnect()
	{
		std::cout << "Disconnect" << std::endl;
		if ( state == DISCONNECTED || state == DISCONNECTING )
		{
			throw 5; // TODO: Use ri7::core::Exception
		}

		// Disconnect protocol
		protocol->Disconnect();
	}
/*
    void Client::OnConnectedSocketEventHandler::HandleEvent(ENetEvent &eevent)
    {
		std::cout << "OnConnectedSocket" << std::endl;
		client->peer = eevent.peer;
        // Connect root protocol
        client->protocol->Connect();
    }
*/
/*
	void Client::OnDisconnectedSocketEventHandler::HandleEvent(ENetEvent &eevent)
	{
		std::cout << "OnDisconnectedSocket" << std::endl;
		// Disconnection process is finished
		client->state = DISCONNECTED;
		// TODO: Here an event shold be raised
	}
*/

    void ServerClient::OnConnectedProtocolEventHandler::HandleEvent()
    {
		std::cout << "OnConnectedProtocol" << std::endl;
		// Connection proccess is finished
        serverClient->state = CONNECTED;
		// TODO: Here an event should be raised
    }

	void ServerClient::OnDisconnectedProtocolEventHandler::HandleEvent()
	{
		std::cout << "OnDisconnectedProtocol" << std::endl;
		// Disconnect socket ¿?
		// client->socket->Disconnect(client->peer);
		// TODO: Here an event should be raised
	}

	void ServerClient::Update()
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

}}
