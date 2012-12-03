//
//  httpheader.h
//  httpsupport
//
//  Created by vhly on 12-11-20.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#ifndef httpsupport_httpheader_h
#define httpsupport_httpheader_h

#include "keypair.h"

typedef KeyPair HttpHeader, *HttpHeaders;

/**
 * Get HTTP header by header name<br/>
 * Get first header from headers
 * @param hName char* header name
 * @return HttpHeader header or NULL
 */
HttpHeader *GetHttpHeader(HttpHeaders headers, char *hName);

/**
 * Get HttpHeaders which named hName
 * @param headers HttpHeaders find list
 * @param hName   name key
 * @return Copy new headers list which name is hName all is new.
 */
HttpHeaders GetHttpHeaders(HttpHeaders headers, char *hName);

/**
 * Get HTTP header's value by header name
 * @param headers HttpHeaders http headers list
 * @param hName header name
 * @return char* header value or NULL
 */
char *GetHttpHeaderValue(HttpHeaders headers, char *hName);

/**
 * Create a http header
 * @param hName header's name
 * @param hValue header's value
 * @return HttpHeader Created http header
 */
HttpHeader *CreateHttpHeader(char *hName, char *hValue);

void AppendHeader(HttpHeaders headers, HttpHeader *header);

char *Header2String(HttpHeader *header, char needCRLF);

#endif // httpsupport_httpheader_h

