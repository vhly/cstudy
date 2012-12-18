//
//  httpheader.c
//  httpsupport
//
//  Created by vhly on 12-11-20.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#include "httpheader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stringutil.h"

// Private functions


// Public functions

HttpHeader *GetHttpHeader(HttpHeaders headers, char *hName)
{
    return GetKeyPair(headers, hName);
}

HttpHeaders GetHttpHeaders(HttpHeaders headers, char *hName)
{
    return GetKeyPairs(headers, hName);
}

char *GetHttpHeaderValue(HttpHeaders headers, char *hName)
{
    return GetKeyPairValue(headers, hName);
}

HttpHeader *CreateHttpHeader(char *hName, char *hValue)
{
    return CreateKeyPair(hName, hValue);
}

void AppendHeader(HttpHeaders headers, HttpHeader *header)
{
    AppendToPairs(headers, header);
}

char *Header2String(HttpHeader *header, char needCRLF)
{
    char *ret = NULL;
    if (header != NULL) {
        size_t nlen, vlen;  // name length and value len
        char* name = header->name;
        char* value = header->value;
        
        if (name != NULL && value != NULL) {
            nlen = strlen(name);
            vlen = strlen(value);
            if (nlen > 0 && vlen > 0) {
                size_t totalLength = nlen + 2 + vlen;
                ret = (char *)malloc(sizeof(char) * totalLength);
                if (needCRLF == 1) {
                    sprintf(ret, "%s: %s\n", name, value);
                }else{
                    sprintf(ret, "%s: %s", name, value);
                }
            }
        }
    }
    return ret;
}

HttpHeader *ParseHttpHeader(char *headerStr)
{
    HttpHeader *ret = NULL;
    if (headerStr != NULL) {
        size_t len = strlen(headerStr);
        if (len > 0) {
            char *value = strchr(headerStr, ':');
            
            long hlen = value - headerStr;
            
            char *name = Substring(headerStr, 0, hlen);
            
            if (name != NULL && value != NULL) {
                value = TrimString(value);
                name = TrimString(name);
                ret = CreateHttpHeader(name, value);
            }
        }
    }
    return ret;
}
