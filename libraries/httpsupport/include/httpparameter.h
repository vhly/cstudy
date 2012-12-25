//
//  httpparameter.h
//  httpsupport
//
//  Created by vhly on 12-12-22.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#ifndef httpsupport_httpparameter_h
#define httpsupport_httpparameter_h

#include "keypair.h"

typedef KeyPair HttpParameter, *HttpParameters;

void AppendParameter(HttpParameters parameters, HttpParameter *parameter);

void SetParameter(HttpParameters parameters, HttpParameter *parameter);

#endif
