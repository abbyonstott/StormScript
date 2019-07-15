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
    Socket Object Guide:
    socketObject.members[0]: Family (AF_INET or AF_INET6)
    socketObject.members[1]: address (ip or hostname)
    socketObject.members[2]: port
    socketObject.members[3]: success (Always should be true if successful)
    socketObject.members[4]: socket val: error or success state of socket
    */

    socketObject.members[0].val = strfamily;
    socketObject.members[1].val = hostname;
    socketObject.members[2].val = std::to_string(port);
    socketObject.members[3].val = "true";

    sa_family_t family;
    int state = 0;

    if (strfamily == "AF_INET") family = AF_INET;
    else if (strfamily == "AF_INET6") family = AF_INET6;

    addr.sin_family = family;
    addr.sin_addr.s_addr = inet_addr(hostname.c_str());
    addr.sin_port = htons(port);

    socketObject.members[4].val = std::to_string(socket(family, SOCK_STREAM, 0));

    state = std::stoi(socketObject.members[4].val);

    if (std::stoi(socketObject.members[4].val) < 0 || 
        bind(state, (struct sockaddr *)&addr, (socklen_t)sizeof(addr)) < 0 || 
        listen(state, 3) < 0) 
    {
        socketObject.members[3].val = "false"; // some sort of error occured
    }

    return socketObject;
}