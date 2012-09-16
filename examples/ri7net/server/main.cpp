
#include "ri7net/ServerListener.h"
#include "ri7net/RawProtocol.h"

int main(int argc, char *argv[])
{
	ri7::net::UdpSocket::Initialize();

	// Create a context to force server destroy before Finalize()
	{
		ri7::net::ServerListener server;
		server.SetLocalHost("");
		server.SetLocalPort(11000);
		server.SetMaxConnections(10);
		server.SetProtocolFactory( (ri7::net::ProtocolFactory *) new ri7::net::RawProtocol::RawProtocolFactory() );
		server.Start();

		while( true ){
			server.Update();
		}

		server.Stop();
		while ( server.GetState() != ri7::net::ServerListener::STOPPED )
		{
			server.Update();
		}
	}

	ri7::net::UdpSocket::Finalize();


	return 0;
}
