//
//
//
//
//

#ifndef httpsupport_httpheader_h
#define httpsupport_httpheader_h

typedef struct _HttpHeader {
	char *headerName;
	char *headerValue;
	
	struct _HttpHeader *prev;
	struct _HttpHeader *next;
} HttpHeader, *HttpHeaders;

HttpHeader *CreateHttpHeader(char *hName, char *hValue);

void AppendHeader(HttpHeaders headers, HttpHeader *header);

#endif // httpsupport_httpheader_h

