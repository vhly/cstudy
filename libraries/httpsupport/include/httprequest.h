//
//  httprequest.h
//  httpsupport
//
//  Created by vhly on 12-12-16.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#ifndef httpsupport_httprequest_h
#define httpsupport_httprequest_h

#include "httpheader.h"

#define HTTP_METHOD_GET 1
#define HTTP_METHOD_POST 2
#define HTTP_METHOD_PUT 3
#define HTTP_METHOD_DELETE 4
#define HTTP_METHOD_HEAD 5


typedef struct _HttpRequest {
    char *url;
    int  method;
    HttpHeaders headers;
    
} *HttpRequest;

#endif
