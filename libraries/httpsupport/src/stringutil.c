//
//  stringutil.c
//  httpsupport
//
//  Created by vhly on 12-12-3.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#include "stringutil.h"

#include <stdio.h>
#include <string.h>

time_t ParseGMTTime(char *gmtStr)
{
    time_t ret = 0;
    if (gmtStr != NULL) {
        char week[4];
        int day = 0;
        char month[4];
        int year = 0;
        int hour = 0;
        int minutes = 0;
        int seconds = 0;
        char zone[5];
        sscanf(gmtStr, "%s%d%s%d%d:%d:%d%s", week, &day, month, &year,&hour, &minutes, &seconds, zone);
        
        if (hour > 0) {
            hour--; // for struct tm hour field, [0 - 23]
        }
        
        if (year > 1900) {
            year -= 1900; // for struct tm year field, since 1900
        }
        
        
        struct tm timeData;
        timeData.tm_mday = day;
        timeData.tm_mon = ConvertMonthToInt(month);   // for struct tm month field, [0 - 11]
        timeData.tm_year = year;
        timeData.tm_hour = hour;
        timeData.tm_min = minutes;
        timeData.tm_sec = seconds;
        
        ret = mktime(&timeData);
    }
    return ret;
}

int ConvertMonthToInt(char *monthName)
{
    int ret = 0;
    if (monthName != NULL) {
        if (strcasecmp("Jan", monthName) == 0) {
            ret = 0;
        } else if (strcasecmp("Feb", monthName) == 0) {
            ret = 1;
        } else if (strcasecmp("Mar", monthName) == 0) {
            ret = 2;
        } else if (strcasecmp("Apr", monthName) == 0) {
            ret = 3;
        } else if (strcasecmp("May", monthName) == 0) {
            ret = 4;
        } else if (strcasecmp("Jun", monthName) == 0) {
            ret = 5;
        } else if (strcasecmp("Jul", monthName) == 0) {
            ret = 6;
        } else if (strcasecmp("Aug", monthName) == 0) {
            ret = 7;
        } else if (strcasecmp("Sep", monthName) == 0) {
            ret = 8;
        } else if (strcasecmp("Oct", monthName) == 0) {
            ret = 9;
        } else if (strcasecmp("Nov", monthName) == 0) {
            ret = 10;
        } else if (strcasecmp("Dec", monthName) == 0) {
            ret = 11;
        }
    }
    return ret;
}