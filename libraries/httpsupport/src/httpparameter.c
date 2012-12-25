//
//  httpparameter.c
//  httpsupport
//
//  Created by vhly on 12-12-22.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#include "httpparameter.h"

#include <stdio.h>

void AppendParameter(HttpParameters parameters, HttpParameter *parameter)
{
    if (parameters != NULL && parameter != NULL) {
        AppendToPairs(parameters, parameter);
    }
}

void SetParameter(HttpParameters parameters, HttpParameter *parameter)
{
    if (parameters != NULL && parameter != NULL) {
        SetToPairs(parameters, parameter);
    }
}
