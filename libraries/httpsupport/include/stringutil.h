//
//  stringutil.h
//  httpsupport
//
//  Created by vhly on 12-12-3.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#ifndef httpsupport_stringutil_h
#define httpsupport_stringutil_h

#include <time.h>

/**
 * Parse GMT format time to time_t
 * @param gmtStr char* time: 
 * @return time_t
 */
time_t ParseGMTTime(char *gmtStr);

/**
 * Convert month simple name to int for struct tm tm_mon field [0 - 11]<br/>
 * This function is need private ?
 * @param monthName char* month simple name
 * @return int [0 - 11] 0 : Jan ...... 11 : Dec
 */
int ConvertMonthToInt(char *monthName);

#endif
