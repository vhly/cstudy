//
//  httprequest.c
//  httpsupport
//
//  Created by vhly on 12-12-16.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#include "httprequest.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "urlsupport.h"

// Private functions

void InitDefaultHeader(HttpRequest *request)
{
    if (request != NULL) {
        if (request->url != NULL) {
            URL *uu = request->url;
            char dd[16];
            sprintf(dd, ":%d", uu->port);
            size_t slen = strlen(dd);
            slen += strlen(uu->domian);
            slen++;
            slen = slen * (sizeof(char));
            char *host = (char *)malloc(slen);
            memset(host, 0, slen);
            sprintf(host, "%s:%d", uu->domian, uu->port);
            HttpHeaders headers = CreateHttpHeader("Host", host);
        }
    }
}

// Public functions

HttpRequest *CreateEmptyRequest(char *url)
{
    HttpRequest *ret = NULL;
    if (url != NULL) {
        ret = (HttpRequest *)malloc(sizeof(HttpRequest));
        memset(ret, 0, sizeof(HttpRequest));
        URL *u = ParseURL(url);
        if (u != NULL) {
            ret->url = u;
            InitDefaultHeader(ret);
        }
    }
    return ret;
}

HttpRequest *HttpGet(char *url)
{
    HttpRequest *ret = NULL;
    if (url != NULL) {
        ret = CreateEmptyRequest(url);
        ret->method = HTTP_METHOD_GET;
    }
    return ret;
}

HttpRequest *HttpPost(char *url)
{
    HttpRequest *ret = NULL;
    if (url != NULL) {
        ret = CreateEmptyRequest(url);
        ret->method = HTTP_METHOD_POST;
    }
    return ret;
}

HttpRequest *HttpPut(char *url)
{
    HttpRequest *ret = NULL;
    if (url != NULL) {
        ret = CreateEmptyRequest(url);
        ret->method = HTTP_METHOD_PUT;
    }
    return ret;
}

HttpRequest *HttpDelete(char *url)
{
    HttpRequest *ret = NULL;
    if (url != NULL) {
        ret = CreateEmptyRequest(url);
        ret->method = HTTP_METHOD_DELETE;
    }
    return ret;
}

HttpRequest *HttpHead(char *url)
{
    HttpRequest *ret = NULL;
    if (url != NULL) {
        ret = CreateEmptyRequest(url);
        ret->method = HTTP_METHOD_HEAD;
    }
    return ret;
}

void AppendHttpHeader(HttpRequest *req, HttpHeader *header)
{
    if (req != NULL && header != NULL) {
        AppendHeader(req->headers, header);
    }
}

void SetHttpHeader(HttpRequest *req, HttpHeader *header)
{
    if (header != NULL) {
        
    }
}

