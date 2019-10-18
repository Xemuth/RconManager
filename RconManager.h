#ifndef _RconManager_RconManager_h_
#define _RconManager_RconManager_h_
#include <Core/Core.h>

using namespace Upp;

class RconManager{
	private:
		const int SERVERDATA_AUTH = 3;
		const int SERVERDATA_EXECCOMMAND = 2;
		TcpSocket socket;
		
		String hostName;
		int port =25575; //Default Rcon Port
		String RconPassword;
				
		String ServiceName;

		int TBR = 500; //Time between request in ms
		int requestID= 0;
		bool isRdy=false; //boolean that's used to know if sendCommand will work or not
		
		Vector<unsigned char>& populateVector(Vector<unsigned char> &myRequest, int value);	
		String RCON_Command(String Command, int ServerData);
	public:
	
		RconManager(String _host, int _port, String _password ,String _serviceName,int _TBR =500);
		bool TestConnexion();
		bool TestLoggin();
		void SendCommand(String commandValue);
	
	
	
	
};

#endif
