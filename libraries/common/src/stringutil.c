//
//  stringutil.c
//  httpsupport
//
//  Created by vhly on 12-12-3.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#include "stringutil.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

time_t ParseGMTTime(char *gmtStr) {
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
		sscanf(gmtStr, "%s%d%s%d%d:%d:%d%s", week, &day, month, &year, &hour,
				&minutes, &seconds, zone);

		if (hour > 0) {
			hour--; // for struct tm hour field, [0 - 23]
		}

		if (year > 1900) {
			year -= 1900; // for struct tm year field, since 1900
		}

		struct tm timeData;
		timeData.tm_mday = day;
		timeData.tm_mon = ConvertMonthToInt(month); // for struct tm month field, [0 - 11]
		timeData.tm_year = year;
		timeData.tm_hour = hour;
		timeData.tm_min = minutes;
		timeData.tm_sec = seconds;

		ret = mktime(&timeData);
	}
	return ret;
}

int ConvertMonthToInt(char *monthName) {
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

char *TrimString(char *str) {
	char *ret = str;
	if (str != NULL) {
		char foundHead = -1;
		char foundLast = -1;
		size_t slen = strlen(str);

		int i;

		char ch;

		for (i = 0; i < slen; i++) {
			ch = *(str + i);
			if (ch != '\t' && ch != '\n' && ch != '\r' && ch != '\f'
					&& ch != ' ') {
				foundHead = i;
				break;
			}
		}

		for (i = slen - 1; i >= 0; i--) {
			ch = *(str + i);
			if (ch != '\t' && ch != '\n' && ch != '\r' && ch != '\f'
					&& ch != ' ') {
				foundLast = i;
				break;
			}
		}

		if (foundHead == -1 && foundLast == -1){
			// can not found normal characters, so return empty string.
			ret = "";
		} else if(foundHead == foundLast){
			// TODO process only one char str
			int ssl = sizeof(char) + 1;
			ret = (char *)malloc(ssl);
			memset(ret, 0, ssl);
			strncpy(ret, (str + foundHead), 1);
		} else if(foundHead == 0 && foundLast == slen - 1){
			ret = str;   // don't need trim, so return orig
		}else{
			int num = foundLast - foundHead + 1;
			if(num > 0){
				int ssl = sizeof(char) * num + 1;
				ret = (char *)(malloc(ssl));
			    memset(ret, 0, ssl);
				strncpy(ret, (str + foundHead), num);
			}
		}
	}
	return ret;
}

char *Substring(char *str, int offset, size_t len)
{
    char *ret = NULL;
    if (str != NULL) {
        size_t slen = strlen(str);
        if (offset >= 0 && len <= slen && len >= 0 && len + offset <= slen) {
            if (offset == 0 && len == slen) {
                ret = str;
            } else {
                int ssd = len * (sizeof(char)) + 1;
                ret = (char *)malloc(ssd);
                memset(ret, 0, ssd);
                
                char *from = str + offset;
                
                strncpy(ret, from, len);
            }
        } // else is error parameter return NULL
    }
    return ret;
}

char *URLEncoding(char *str, int encodingType)
{
    char *ret = NULL;
    if (str != NULL) {
        
    }
    return ret;
}
