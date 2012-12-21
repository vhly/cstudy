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

#include "urlsupport.h"

#include "bytestream.h"

#include "datastream.h"

#define HTTP_METHOD_GET 1
#define HTTP_METHOD_POST 2
#define HTTP_METHOD_PUT 3
#define HTTP_METHOD_DELETE 4
#define HTTP_METHOD_HEAD 5


typedef struct _HttpRequest {
    URL *url;
    int  method;
    HttpHeaders headers;
    ByteStream body;
} HttpRequest;

HttpRequest *HttpGet(char *url);

HttpRequest *HttpPost(char *url);

HttpRequest *HttpPut(char *url);

HttpRequest *HttpDelete(char *url);

HttpRequest *HttpHead(char *url);

void AppendHttpHeader(HttpRequest *req, HttpHeader *header);

void SetHttpHeader(HttpRequest *req, HttpHeader *header);

#endif
