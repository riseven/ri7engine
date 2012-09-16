#pragma once

#include "Protocol.h"

#include "enet/enet.h"
#include <string>

namespace ri7 {
namespace net {

	class NetEventHandler;

	class UdpSocket
	{
	private:
        // Pre Conenct Data
        std::string localHost;
		int localPort;
		int maxConnections;

		std::string remoteHost;
        int remotePort;

        // Post Connect Data
		ENetHost *host;

		NetEventHandler *onConnected;
		NetEventHandler *onDisconnected;
		NetEventHandler *onReceiveData;

	public:
		static void Initialize();
		static void Finalize();

		static UdpSocket * CreateClient(std::string remoteHost, int remotePort);
		static UdpSocket * CreateServer(std::string localHost, int localPort, int maxConnections);

		void SetLocalHost(std::string localHost);
		void SetLocalPort(int localPort);
		void SetMaxConnections(int maxConnections);
        void SetRemoteHost(std::string remoteHost);
        void SetRemotePort(int remotePort);

        void SetOnConnected(NetEventHandler *onConnectedEventHandler);
		void SetOnDisconnected(NetEventHandler *onDisconnectedEventHandler);
		void SetOnReceiveData(NetEventHandler *onReceiveDataEventHandler);

        void Connect();
		void Disconnect(ENetPeer *peer);
		void Start();
		void Stop();
		void SendPacket(ENetPeer *peer, unsigned char *bytes, unsigned int size);
		void Update();

		UdpSocket(void);
		~UdpSocket(void);
	};

}}
