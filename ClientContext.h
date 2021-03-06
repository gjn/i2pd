#ifndef CLIENT_CONTEXT_H__
#define CLIENT_CONTEXT_H__

#include <mutex>
#include "Destination.h"
#include "HTTPProxy.h"
#include "SOCKS.h"
#include "I2PTunnel.h"
#include "SAM.h"
#include "BOB.h"
#include "AddressBook.h"
#include "I2PControl.h"

namespace i2p
{
namespace client
{
	class ClientContext
	{
		public:

			ClientContext ();
			~ClientContext ();

			void Start ();
			void Stop ();

			ClientDestination * GetSharedLocalDestination () const { return m_SharedLocalDestination; };
			ClientDestination * CreateNewLocalDestination (bool isPublic = false, i2p::data::SigningKeyType sigType = i2p::data::SIGNING_KEY_TYPE_DSA_SHA1,
			    const std::map<std::string, std::string> * params = nullptr); // transient
			ClientDestination * CreateNewLocalDestination (const i2p::data::PrivateKeys& keys, bool isPublic = true, 
				const std::map<std::string, std::string> * params = nullptr);
			void DeleteLocalDestination (ClientDestination * destination);
			ClientDestination * FindLocalDestination (const i2p::data::IdentHash& destination) const;		
			ClientDestination * LoadLocalDestination (const std::string& filename, bool isPublic);

			AddressBook& GetAddressBook () { return m_AddressBook; };
			
		private:

			std::mutex m_DestinationsMutex;
			std::map<i2p::data::IdentHash, ClientDestination *> m_Destinations;
			ClientDestination * m_SharedLocalDestination;	

			AddressBook m_AddressBook;

			i2p::proxy::HTTPProxy * m_HttpProxy;
			i2p::proxy::SOCKSProxy * m_SocksProxy;
			I2PClientTunnel * m_IrcTunnel;
			I2PServerTunnel * m_ServerTunnel;
			SAMBridge * m_SamBridge;
			BOBCommandChannel * m_BOBCommandChannel;
			I2PControlService * m_I2PControlService;

		public:
			// for HTTP
			const decltype(m_Destinations)& GetDestinations () const { return m_Destinations; };
	};
	
	extern ClientContext context;	
}		
}	

#endif
