//
//  httpheader.h
//  httpsupport
//
//  Created by vhly on 12-11-20.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#ifndef httpsupport_httpheader_h
#define httpsupport_httpheader_h

typedef struct _HttpHeader {
	char *headerName;
	char *headerValue;
	
	struct _HttpHeader *prev;
	struct _HttpHeader *next;
} HttpHeader, *HttpHeaders;

/**
 * Get HTTP header by header name<br/>
 * Get first header from headers
 * @param hName char* header name
 * @return HttpHeader header or NULL
 */
HttpHeader *GetHttpHeader(HttpHeaders headers, char *hName);

/**
 * Get HTTP header's value by header name
 * @param headers HttpHeaders http headers list
 * @param hName header name
 * @return char* header value or NULL
 */
char *GetHttpHeaderValue(HttpHeaders headers, char *hName);

/**
 * Create a http header
 *
 *
 *
 */
HttpHeader *CreateHttpHeader(char *hName, char *hValue);

void AppendHeader(HttpHeaders headers, HttpHeader *header);

char *Header2String(HttpHeader *header, char needCRLF);

#endif // httpsupport_httpheader_h

