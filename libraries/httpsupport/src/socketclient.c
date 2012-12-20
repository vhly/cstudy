//
//  socketclient.c
//  httpsupport
//
//  Created by vhly on 12-12-17.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#include "socketclient.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>

/**
 * Check SocketRequest host and ip information<br/>
 * This function will update request host and socketAddr fields, and will update port field with htons() function.
 * So don't warry about this field, and must not reset by htons().
 * @param request SocketRequest*
 * @param state for result
 */
int CheckSocketRequest(SocketRequest *request)
{
    int ret = -1;
    if (request != NULL) {
        if (request->hostName == NULL && request->ipAddress == NULL) {
            // TODO show error
        } else {
            char *ipadd = request->ipAddress;
            if (request->hostName != NULL) {
                struct hostent *host = gethostbyname(request->hostName);
                request->host = host;
                if (ipadd == NULL) {
                    ipadd = (char *)malloc(32);
                    memset(ipadd, 0, 32 * (sizeof(char)));
                    inet_ntop(host->h_addrtype, host->h_addr, ipadd, 32);
                    request->ipAddress = ipadd;
                }
            }
            if (request->port > 0) {
                request->port = htons(request->port);
                if (request->socketAddr == NULL) {
                    request->socketAddr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
                }
                memset(request->socketAddr, 0, sizeof(struct sockaddr_in));
                request->socketAddr->sin_family = AF_INET;
                request->socketAddr->sin_port = request->port;
                request->socketAddr->sin_addr.s_addr = inet_addr(ipadd);
                ret = 0;
            }
        }
    }
    return ret;
}

int ConnectSocket(SocketRequest *request)
{
    int ret = -1;
    if (request != NULL) {
        ret = CheckSocketRequest(request);
        if (ret != -1) {
            // TODO Create a socket and connect it
            ret = socket(AF_INET, SOCK_STREAM, 0);
            if (ret != -1) {
                int ok = connect(ret, (struct sockaddr *)request->socketAddr, sizeof(struct sockaddr));
                if (ok == -1) {
                    ret = -1;
                }
            }
        }
    }
    return ret;
}

long SendDataToSocket(int sock, ByteStream stream)
{
    long ret = 0;
    if (sock != 0 && stream != NULL) {
        ByteArrayBlock *current = stream;
        size_t st;
        do{
            st = send(sock, current->buf, current->dataLength, 0);
            if (st == -1) {
                break;
            }
            ret += current->dataLength;
            current = current->next;
            if (current == NULL) {
                break;
            }
        }while (1);
    }
    return ret;
}

long ReceiveDataFromSocket(int sock, ByteStream buf)
{
    long ret = -1;
    if (sock != 0 && buf != NULL) {
        size_t dlen = 1024*(sizeof(char));
        char *data = (char *)malloc(dlen);
        size_t st = recv(sock, data, dlen, 0);
        if (st > 0) {
            AppendByteData(buf, data, 0, st);
            ret = st;
        }
    }
    return ret;
}
