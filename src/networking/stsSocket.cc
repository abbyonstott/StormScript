#include "../include/stormscript.h"

type sts::socketClass() {
	type t;
	stsvars family, address, port, success, sockval;

	t.name = "socket";

	// these are all defaults

	family.name = "family";
	family.type = 's';
	family.val = "AF_INET";

	address.name = "address";
	address.type = 's';
	address.val = "127.0.0.1";

	port.name = "port";
	port.type = 'i';
	port.val = "9999";

	success.name = "success";
	success.type = 'b';
	success.val = "false";

	sockval.name = "sockval";
	sockval.type = 'i';
	sockval.val = "-1";

	t.members.push_back(family);
	t.members.push_back(address);
	t.members.push_back(port);
	t.members.push_back(success);
	t.members.push_back(sockval);

	return t;
}







stsObject sts::createSocket(string strfamily, string hostname, uint16_t port, stsObject socketObject) {
	/*
	* Socket Object Guide:
	* socketObject.members[0]: Family (AF_INET or AF_INET6)
	* socketObject.members[1]: address (ip or hostname)
	* socketObject.members[2]: port
	* socketObject.members[3]: success (Always should be true if successful)
	* socketObject.members[4]: socket val: error or success state of socket
	*/

	socketObject.members[0].val = strfamily;
	socketObject.members[1].val = hostname;
	socketObject.members[2].val = std::to_string(port);
	socketObject.members[3].val = "true";


	// porting to winsock2 requires some changes
	#if (PLATFORM == 0)
	sa_family_t family;
	if (strfamily == "AF_INET") family = AF_INET;
	else if (strfamily == "AF_INET6") family = AF_INET6;
	#else
	int family;
	if (strfamily == "AF_INET") family = 2;
	else if (strfamily == "AF_INET6") family = 23;
	#endif

	int state = 0;

	addr.sin_family = family;
	addr.sin_addr.s_addr = inet_addr(hostname.c_str());
	addr.sin_port = htons(port);

	socketObject.members[4].val = std::to_string(socket(family, SOCK_STREAM, 0)); // socket declarations are the same between both platforms

	state = std::stoi(socketObject.members[4].val);

	if (std::stoi(socketObject.members[4].val) < 0)
		socketObject.members[3].val = "false"; // some sort of error occured

	return socketObject;
}


/*
* awaiting a connection and connecting work very similarly
* It would make sense to combine the commands needed to connect to client/server
* into only a socket.await or socket.connect method respectively
*/
stsObject sts::awaitSocket(stsObject socketObject, string msg, bool output) {
	int socketval = std::stoi(socketObject.members[4].val);
	int bindval;

	#if (PLATFORM == 0)
	int addrsizei = sizeof(addr); // integer form of addrsize
	socklen_t *addrsize = (socklen_t *)&addrsizei;
	bindval = bind(socketval, (struct sockaddr *)&addr, (socklen_t)sizeof(addr));
	#else
	int *addrsize = (int *)new unsigned long(sizeof(addr));
	bindval = bind(socketval, (struct sockaddr *)&addr, sizeof(addr));
	#endif

	int listenval = listen(socketval, 3);
	int acc = accept(socketval,(struct sockaddr *)&addr, addrsize);

	if (acc < 0 || listenval < 0 || bindval < 0)
		socketObject.members[3].val = "false";
	else {
		char buffer[1024] = {0};

		int r = read(acc, buffer, 1024);
		if (output == true)
			cout << buffer << "\n";

		send(acc, msg.c_str(), msg.size(), 0);
	}

	return socketObject;
}







stsObject sts::connectSocket(stsObject socketObject, string msg) {
	int socketval = std::stoi(socketObject.members[4].val);
	int addrsize = sizeof(addr);

	#if (PLATFORM == 0)
	sa_family_t family;

	if (socketObject.members[0].val == "AF_INET") family = AF_INET;
	else if (socketObject.members[0].val == "AF_INET6") family = AF_INET6;

	int pres = inet_pton(family, socketObject.members[1].val.c_str(), &addr.sin_addr);

	if (pres <= 0) {
		socketObject.members[3].val = "false";
		return socketObject;
	}
	#else
	int family;

	if (socketObject.members[0].val == "AF_INET") family = 2;
	else if (socketObject.members[0].val == "AF_INET6") family = 23;
	#endif

	int connects = connect(socketval, (struct sockaddr *)&addr, addrsize);

	if (connects < 0)
		socketObject.members[3].val = "false";
	else {
		send(socketval, msg.c_str(), msg.size(), 0);

		char buffer[1024] = {0};
		int val = read(socketval, buffer, 1024);
		cout << buffer << '\n';
	}

	return socketObject;
}
