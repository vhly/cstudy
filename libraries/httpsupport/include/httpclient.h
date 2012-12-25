//
//  httpclient.h
//  httpsupport
//
//  Created by vhly on 12-12-25.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#ifndef httpsupport_httpclient_h
#define httpsupport_httpclient_h

#include "bytestream.h"
#include "datastream.h"
#include "httprequest.h"
#include "httpresponse.h"


/**
 * Process request connect and get response
 * @param req HttpRequest*
 * @return HttpResponse*
 */
HttpResponse *ProcessHttpRequest(HttpRequest *req);

#endif
