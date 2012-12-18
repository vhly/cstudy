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

HttpRequest *CreateEmptyRequest(char *url)
{
    HttpRequest *ret = NULL;
    if (url != NULL) {
        ret = (HttpRequest *)malloc(sizeof(HttpRequest));
        memset(ret, 0, sizeof(HttpRequest));
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