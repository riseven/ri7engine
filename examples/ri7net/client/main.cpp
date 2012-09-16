
#include "ri7net/Client.h"
#include "ri7net/RawProtocol.h"

int main(int argc, char *argv[])
{
	ri7::net::UdpSocket::Initialize();

	ri7::net::RawProtocol *rawProtocol = new ri7::net::RawProtocol();

	ri7::net::Client client;
	client.SetRemoteHost("localhost");
	client.SetRemotePort(11000);
	client.SetProtocol( rawProtocol );
	client.Connect();

	while ( client.GetState() != ri7::net::Client::CONNECTED )
	{
		client.Update();
	}

	rawProtocol->PutUnsignedChar('a');
	rawProtocol->SendPacket();
	rawProtocol->PutUnsignedChar('b');
	rawProtocol->SendPacket();
	rawProtocol->PutUnsignedChar('c');

	//client.Disconnect();

	while ( client.GetState() != ri7::net::Client::DISCONNECTED )
	{
		client.Update();
	}

	ri7::net::UdpSocket::Finalize();

	system("pause");

	return 0;
}
