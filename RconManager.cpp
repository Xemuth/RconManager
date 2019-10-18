#include "RconManager.h"
using namespace Upp;

Upp::String hexitize(Upp::String input,const char* const digits = "0123456789ABCDEF")
{
    String output;

    for (unsigned char gap = 0, beg = input[gap]; gap < input.GetCount(); beg = input[++gap])
        output << digits[beg >> 4] << digits[beg & 15];

    return output;
}


RconManager::RconManager(String _host, int _port, String _password ,String _serviceName,int _TBR){
		hostName=_host;
		port =_port;
		RconPassword=_password;
		socket.Timeout(3000);
		
				
		ServiceName=_serviceName;

		TBR = _TBR;
		if(hostName.GetCount()>0 && port > 0 && RconPassword.GetCount() >0)
			isRdy =true;
}
	
void RconManager::SendCommand(String commandValue){
	socket.Connect(hostName, port);
	socket.WaitConnect();
	socket.Put(RCON_Command(RconPassword,SERVERDATA_AUTH));
	Sleep(TBR);
	socket.Put(RCON_Command(commandValue, SERVERDATA_EXECCOMMAND));
	Sleep(TBR);
	
	socket.Close();
}

bool RconManager::TestConnexion(){
	socket.Connect(hostName, port);
	return socket.WaitConnect();
}

bool RconManager::TestLoggin(){
	socket.Connect(hostName, port);
	socket.WaitConnect();
	socket.Put(RCON_Command(RconPassword,SERVERDATA_AUTH));
	Sleep(TBR);
	return (hexitize(socket.Get(socket.Get())).Find("FFFFFFF")==-1)? true:false;
}

Vector<unsigned char>& RconManager::populateVector(Vector<unsigned char> &myRequest, int value){
	unsigned char array[4]; // Nombre maximal de chiffres + 1
	
	array[0] = (value >> 24) & 0xFF;
	array[1] = (value >> 16) & 0xFF;
	array[2] = (value >> 8) & 0xFF;
	array[3] = value & 0xFF;
   	
   	myRequest.Add(array[3]);
   	myRequest.Add(array[2]);
   	myRequest.Add(array[1]);
   	myRequest.Add(array[0]);

	return myRequest;
}


String RconManager::RCON_Command(String Command, int ServerData)
{
	Vector<unsigned char> myRequest;
  	populateVector(myRequest,(Command.GetCount() + 10));
  	populateVector(myRequest,requestID);
  	populateVector(myRequest,ServerData);
	for (int X = 0; X < Command.GetCount(); X++)
	{
		myRequest.Add(static_cast<unsigned char>(Command[X]));
	}
	myRequest.Add(0);
	myRequest.Add(0);
	String data="";
	for(unsigned char &e : myRequest){
		data <<  e;
	}
	requestID++;
	return data;
}