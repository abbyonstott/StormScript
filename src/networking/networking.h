#pragma once
#ifndef NETWORKING_H_
#define NETWORKING_H_

#include "../stormscript.h"

#if (PLATFORM)
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

inline WSADATA data;
#else
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h> 
#endif // PLATFORM == 1

// socket stuff:
stsObject createSocket(string family, string hostname, uint16_t port, stsObject socketObject);
stsObject awaitSocket(stsObject socketObject, string msg, bool output);
stsObject connectSocket(stsObject socketObject, string msg);
inline struct sockaddr_in addr;

//functions that return "type" are treated as classes and should be declared inline in header files
inline type socketClass() {
	type t;
	stsvars family, address, port, success, sockval;

	t.name = "socket";

	// these are all defaults

	family.name = "family";
	family.type = STRING;
	family.val = "AF_INET";

	address.name = "address";
	address.type = STRING;
	address.val = "127.0.0.1";

	port.name = "port";
	port.type = INTEGER;
	port.val = "9999";

	success.name = "success";
	success.type = STS_BOOL;
	success.val = "false";

	sockval.name = "sockval";
	sockval.type = INTEGER;
	sockval.val = "-1";

	t.members.push_back(family);
	t.members.push_back(address);
	t.members.push_back(port);
	t.members.push_back(success);
	t.members.push_back(sockval);

	return t;
}

#endif // NETWORKING_H_