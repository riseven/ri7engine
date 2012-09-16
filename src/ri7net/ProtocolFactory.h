#pragma once

namespace ri7 {
namespace net {

	class Protocol;

	class ProtocolFactory {
	public:
		virtual Protocol * Instantiate(void)=0;
	};

}};