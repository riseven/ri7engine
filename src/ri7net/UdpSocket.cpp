#include "UdpSocket.h"

#include "NetEventHandler.h"

namespace ri7 {
namespace net {

	void UdpSocket::Initialize()
	{
		enet_initialize();
	}

	void UdpSocket::Finalize()
	{
		enet_deinitialize();
	}

	UdpSocket::UdpSocket(void)
	{
		host = NULL;
		onConnected = NULL;
		onDisconnected = NULL;
		onReceiveData = NULL;

		localHost = "";
		localPort = 0;
		maxConnections = 0;

		remoteHost = "";
		remotePort = 0;
	}

	UdpSocket::~UdpSocket(void)
	{
		if ( host )
		{
			enet_host_destroy(host);
		}
		host = NULL;
		onConnected = NULL;
		onDisconnected = NULL;
		onReceiveData = NULL;
	}

	UdpSocket * UdpSocket::CreateClient(std::string remoteHost, int remotePort)
	{
		UdpSocket *socket = new UdpSocket();

		// Create ENetHost
		socket->host = enet_host_create(NULL, 1, 0, 0);
		if ( !socket->host )
		{
			throw 5; // TODO: Use ri7::core::Exception
		}

		// Connect
		ENetAddress address;
		enet_address_set_host(&address, remoteHost.c_str());
		address.port = remotePort;

		ENetPeer *peer = enet_host_connect(socket->host, &address, 2);
		if ( !peer )
		{
			throw 5; // TODO: Use ri7::core::Exception
		}

		return socket;
	}

	UdpSocket * UdpSocket::CreateServer(std::string localHost, int localPort, int maxConnections)
	{
		UdpSocket *socket = new UdpSocket();

		// Create ENetHost
		ENetAddress address;
		if ( localHost == "" )
		{
			address.host = ENET_HOST_ANY;
		}
		else
		{
			// TODO
			throw 5;
		}
		address.port = localPort;

		socket->host = enet_host_create(&address, maxConnections, 0, 0);
		if ( !socket->host )
		{
			throw 5; // TODO: Use ri7::core::Exception
		}

		return socket;
	}

	void UdpSocket::SetLocalHost(std::string localHost)
	{
		this->localHost = localHost;
	}

	void UdpSocket::SetLocalPort(int localPort)
	{
		this->localPort = localPort;
	}

	void UdpSocket::SetMaxConnections(int maxConnections)
	{
		this->maxConnections = maxConnections;
	}

	void UdpSocket::SetRemoteHost(std::string remoteHost)
	{
	    this->remoteHost = remoteHost;
	}

	void UdpSocket::SetRemotePort(int remotePort)
	{
	    this->remotePort = remotePort;
	}

	void UdpSocket::SetOnConnected(NetEventHandler *onConnectedEventHandler)
	{
	    onConnected = onConnectedEventHandler;
	}

	void UdpSocket::SetOnDisconnected(NetEventHandler *onDisconnectedEventHandler)
	{
		onDisconnected = onDisconnectedEventHandler;
	}

	void UdpSocket::SetOnReceiveData(NetEventHandler *onReceiveDataEventHandler)
	{
		onReceiveData = onReceiveDataEventHandler;
	}

	void UdpSocket::Connect()
	{
		// Create ENetHost
		host = enet_host_create(NULL, 1, 0, 0);
		if ( !host )
		{
			throw 5; // TODO: Use ri7::core::Exception
		}

		// Connect
		ENetAddress address;
		enet_address_set_host(&address, remoteHost.c_str());
		address.port = remotePort;

		ENetPeer * peer = enet_host_connect(host, &address, 2);
		if ( !peer )
		{
			throw 5; // TODO: Use ri7::core::Exception
		}
	}

	void UdpSocket::Disconnect(ENetPeer *peer)
	{
		// Disconnect socket
		enet_peer_disconnect( peer, 0 );
	}

	void UdpSocket::Start()
	{
		// Create ENetHost
		ENetAddress address;
		if ( localHost == "" )
		{
			address.host = ENET_HOST_ANY;
		}
		else
		{
			enet_address_set_host(&address, localHost.c_str());
		}
		address.port = localPort;
		host = enet_host_create(&address, maxConnections, 0, 0);
		if ( !host )
		{
			throw 5; // TODO: Use ri7::core::Exception
		}
	}

	void UdpSocket::SendPacket(ENetPeer *peer, unsigned char *bytes, unsigned int size)
	{
		// Create packet
		ENetPacket *packet = enet_packet_create(bytes, size, 0);

		// Send packet
		enet_peer_send(peer, 0, packet);

		// TODO: Host flush should be done in a different method
		enet_host_flush(host);
	}

	void UdpSocket::Stop()
	{
		// Nothing to do
	}

	void UdpSocket::Update()
	{
		ENetEvent eevent;

		while ( enet_host_service(host, &eevent, 0 ) > 0 )
		{
			if ( eevent.type == ENET_EVENT_TYPE_CONNECT )
			{
				if ( onConnected != NULL )
				{
					onConnected->HandleEvent(eevent);
				}
			}
			else if ( eevent.type == ENET_EVENT_TYPE_DISCONNECT )
			{
				if ( onDisconnected != NULL )
				{
					onDisconnected->HandleEvent(eevent);
				}
			}
			else if ( eevent.type == ENET_EVENT_TYPE_RECEIVE )
			{
				if ( onReceiveData != NULL )
				{
					onReceiveData->HandleEvent(eevent);
				}
			}
		}
	}

}}
