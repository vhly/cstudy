//
//  httpresponse.h
//  httpsupport
//
//  Created by vhly on 12-12-16.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#ifndef httpsupport_httpresponse_h
#define httpsupport_httpresponse_h

#include "httpheader.h"

#include "bytestream.h"

typedef struct _HttpResponse{
    int stateCode;
    char *stateMessage;
    HttpHeaders headers;
    ByteStream body;
} HttpResponse;

#endif
