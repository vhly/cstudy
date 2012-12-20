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

#include "bytestream.h"


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

/**
 * Send byte stream to Socket<br/>
 * This funcation don't find stream header, it will read from current pointer address.
 * @param sock int socket handler
 * @param stream ByteStream byte array stream
 * @return long send data length
 */
long SendDataToSocket(int sock, ByteStream stream);

/**
 * Received from socket, and append to buf (ByteStream instance)
 * @param sock int socket handler
 * @param buf ByteStream which data store from socket
 * @return long receivde length
 */
long ReceiveDataFromSocket(int sock, ByteStream buf);

#endif
