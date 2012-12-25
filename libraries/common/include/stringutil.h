//
//  stringutil.h
//  httpsupport
//
//  Created by vhly on 12-12-3.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#ifndef httpsupport_stringutil_h
#define httpsupport_stringutil_h

#define URL_ENCODING_UTF8 0
#define URL_ENCODING_GBK 1
#define URL_ENCODING_GB2312 2


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

/**
 * Trim a string<br/>
 * Remove head and last white space and crlf and tabs
 * @param str char*, content to trim
 * @return char* new str or orig
 */
char *TrimString(char *str);

/**
 * Get a substring from offset with length of str<br/>
 * If offset = 0 and len is Whole string length, return orig str point<br/>
 * Please not set parameters for all.
 * @param str char*, orig string
 * @param offset int, start index from 0 to other
 * @param len  length for substring
 * @return char*, New string or NULL for error parameters
 */
char *Substring(char *str, int offset, size_t len);

/**
 * Convert str to url encoding
 * @param str char*
 * @param encodingType int encoding type
 * @return str encoded or null
 */
char *URLEncoding(char *str, int encodingType);

#endif
