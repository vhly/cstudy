//
//  socketclient.h
//  httpsupport
//
//  Created by vhly on 12-12-17.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#ifndef httpsupport_socketclient_h
#define httpsupport_socketclient_h

#include <netinet/in.h>


typedef struct _SocketRequest {
    char *hostName;
    char *ipAddress;
    int  port;
    struct hostent *host;
    struct sockaddr_in *socketAddr;
} SocketRequest;

/**
 * Connect socket target
 * @param request SocketRequest*
 * @return socket handle or -1 which has error
 */
int ConnectSocket(SocketRequest *request);

#endif
