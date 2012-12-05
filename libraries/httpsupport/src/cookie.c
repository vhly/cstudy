//
//  cookie.c
//  httpsupport
//
//  Created by vhly on 12-11-20.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#include "cookie.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "stringutil.h"

// Private funcations

Cookie *FindFirstCookie(CookieStore cookies)
{
    Cookie *head = cookies;
    while (head != NULL) {
        if (head->prevSub != NULL) {
            head = head->prevSub;
        }else{
            break;
        }
    }
    
    return head;
}

// Public functions
Cookie *CreateCookie(char *name, char *value) {
	Cookie *ret = NULL;
	if (name != NULL) {
		ret = (Cookie *) malloc(sizeof(Cookie));
		ret->name = name;
		ret->value = value;
		ret->path = NULL;
		ret->domain = NULL;
		ret->expireStr = NULL;
		ret->httpOnly = 0;
		ret->secure = 0;
		ret->maxAge = 0;
		ret->nextSub = NULL;
		ret->prevSub = NULL;
		ret->receivedTime = 0;
	}
	return ret;
}

char CookieIsExpired(Cookie *cookie) {
	char ret = COOKIE_EXPIRE_EXPIRED;
	if (cookie != NULL) {
		ret = COOKIE_EXPIRE_NO;
		time_t t1 = time(NULL);

		if (cookie->maxAge != 0 && cookie->receivedTime != 0) {
			// maxAge unit is second, so * 1000
			long maxTime = cookie->receivedTime + (cookie->maxAge * 1000);
			if (t1 > maxTime) {
				ret = COOKIE_EXPIRE_EXPIRED;
			}
		} else if (cookie->expireStr != NULL) {
			time_t t2 = ParseGMTTime(cookie->expireStr);
			if (t2 > 0) {
				if (t1 > t2) {
					ret = COOKIE_EXPIRE_EXPIRED;
				}
			}
		}
	}
	return ret;
}

char *CookieToString(Cookie *cookie, char includeInfo) {
	char *ret = NULL;
	if (cookie != NULL) {
		char *name = cookie->name;
		char *value = cookie->value;
		if (name != NULL) {
			int totalLen = 0;
			int nlen = strlen(name);
			int vlen = 0;

			if (value != NULL) {
				vlen = strlen(value);
			}

			totalLen = nlen + 1 + vlen + 1; // "name=value;"

			if (includeInfo) {
				char *str = cookie->path;
				int slen = 0;
				if (str != NULL) {
					slen = strlen(str);
					if (slen > 0) {
						totalLen = totalLen + 6 + slen + 1; // "name=value; path=<path>;"
					}
				}

				str = cookie->expireStr;
				if (str != NULL) {
					slen = strlen(cookie->expireStr);
					if (slen > 0) {
						totalLen = totalLen + 9 + slen + 1; // "name=value; expires=<exprieStr>;"
					}
				} else if (cookie->maxAge > 0) {
					char tmp[20];
					sprintf(tmp, "%d", cookie->maxAge);
					slen = strlen(tmp);
					if (slen > 0) {
						totalLen = totalLen + 8 + slen + 1; // "name=value; maxAge=<maxAge>;"
					}
				}

				str = cookie->domain;
				if (str != NULL) {
					slen = strlen(cookie->domain);
					if (slen > 0) {
						totalLen = totalLen + 8 + slen + 1; // "name=value; domain=<domain>;"
					}
				}

				if (cookie->secure) {
					totalLen = totalLen + 7 + 1; // "name=value; secure;"
				}
			}

			if (totalLen > 0) {
				ret = (char *) malloc((sizeof(char)) * totalLen + 1);

				memset(ret, 0, totalLen + 1);

				if (includeInfo) {
					// TODO process
					if (value != NULL) {
						sprintf(ret, "%s=%s;", name, value);
					} else {
						sprintf(ret, "%s=;", name);
					}
					int ddindex = strlen(ret);

					char *buf;

					char *str = cookie->path;
					if (str != NULL) {
						buf = ret + ddindex;
						sprintf(buf, " path=%s;", cookie->path);
					}

					ddindex = strlen(ret);

					buf = ret + ddindex;

					str = cookie->expireStr;
					if (str != NULL) {
						sprintf(buf, " expires=%s;", cookie->expireStr);
					} else if (cookie->maxAge > 0) {
						sprintf(buf, " maxAge=%d;", cookie->maxAge);
					}

					ddindex = strlen(ret);

					buf = ret + ddindex;

					str = cookie->domain;
					if (str != NULL) {
						sprintf(buf, " domain=%s;", cookie->domain);
					}

					ddindex = strlen(ret);

					buf = ret + ddindex;

					if (cookie->secure) {
						sprintf(buf, " secure;");
					}
				} else {
					if (value != NULL) {
						sprintf(ret, "%s=%s;", name, value);
					} else {
						sprintf(ret, "%s=;", name);
					}
				}
			}
		}
	}
	return ret;
}

char *CookieStreamToString(CookieStore cookies)
{
    char *ret = NULL;
    if (cookies != NULL) {
        Cookie *head = FindFirstCookie(cookies);
        
        int totalLen = 0;
        
        if (head != NULL) {
            Cookie *tmp = head;
            char *name;
            char *value;
            int nlen;
            int vlen;
            while (tmp != NULL) {
                nlen = 0;
                vlen = 0;
                name = tmp->name;
                value = tmp->value;
                if (name != NULL) {
                    nlen = strlen(name);
                }
                if (value != NULL) {
                    vlen = strlen(value);
                }
                totalLen = totalLen + nlen + 1 + vlen + 1;  // " name=value;"
                tmp = tmp->nextSub;
            }
            if (totalLen > 0 && totalLen < 1960) {
                int tt = (sizeof(char)) * totalLen + 1;
                ret = (char *)malloc(tt);
                memset(ret, 0, tt);
                
                tmp = head;
                char *buf = ret;
                int index = 0;
            
                while (tmp != NULL) {
                    nlen = 0;
                    vlen = 0;
                    
                    name = tmp->name;
                    value = tmp->value;
                    nlen = strlen(name);
                    if (value != NULL) {
                        vlen = strlen(value);
                        sprintf(buf, "%s=%s;", name, value); // TODO Check first key set.
                    } else {
                        sprintf(buf, "%s=;", name);
                    }
                    
                    tmp = tmp->nextSub;
                    
                    index = index + nlen + 1 + vlen + 1;
                    
                    buf = buf + index;
                }
                
            }
        }
    }
    return ret;
}

Cookie *ParseCookie(char *cookieStr) {
	// TODO Parse cookie string
	Cookie *ret = NULL;
	if (cookieStr != NULL) {
		int sindex = 0;
		int eindex = -1;

		int slen = strlen(cookieStr);

		int i;

		char ch;

		char *str;

		long cksize = sizeof(Cookie);

		ret = (Cookie *) malloc(cksize);

		memset(ret, 0, cksize);

		char *key = NULL;
		char *value = NULL;

		for (i = 0; i < slen; i++) {
			ch = *(cookieStr + i);
			if (ch == ' '){
				continue;
			}else if (ch == ';') {
				eindex = i;
				int dlen = eindex - sindex;

				str = (char *) malloc((sizeof(char)) * dlen + 1);

				memset(str, 0, (sizeof(char)) * dlen + 1);

				strncpy(str, (cookieStr + sindex), dlen);

				// TODO Process key and value.

				value = strchr(str, '=');

				if (value != NULL) {
					int blen = value - str;
					key = (char *) (malloc(sizeof(char) * blen + 1));
					memset(key, 0, sizeof(char) * blen + 1);
					strncpy(key, str, blen);
					value++; // skip '=' character.
					blen = value - str;
					if (blen == slen) {
						value = NULL;
					}
				} else {
					key = str;
				}

				key = TrimString(key);

//				printf("CKParser: key %s\n", key);

				if (value != NULL) {
					value = TrimString(value);
//					printf("CKParser: value %s\n", value);
				}

				int cmp = -1;

				if (strcasecmp("path", key) == 0) {
					ret->path = value;
				}else if (strcasecmp("expires", key) == 0) {
					ret->expireStr = value;
				}else if (strcasecmp("domain", key) == 0) {
					ret->domain = value;
				}else if (strcasecmp("secure", key) == 0) {
					ret->secure = 1;
				}else if (strcasecmp("maxAge", key) == 0) {
					int dd = 0;
					sscanf(value, "%d", &dd);
					ret->maxAge = dd;
				}else {
					ret->name = key;
					ret->value = value;
				}

				sindex = eindex;

				if (sindex < slen) {
					sindex++;
				}
			}
		}

		if (eindex == -1) {
			// TODO process only key=value style.
		}
	}
	return ret;
}

CookieStore RemoveExpiredCookies(CookieStore cookies)
{
    CookieStore ret = cookies;
    if (cookies != NULL) {
        Cookie *head = FindFirstCookie(cookies);
        
        Cookie *tmp = head;
        Cookie *prev, *next;
        while (tmp != NULL) {
            prev = NULL;
            next = NULL;
            char st = CookieIsExpired(tmp);
            if (st == COOKIE_EXPIRE_EXPIRED) {
                prev = tmp->prevSub;
                next = tmp->nextSub;
                if (prev != NULL) {
                    prev->nextSub = next;
                    
                }
                if (next != NULL) {
                    next->prevSub = prev;
                }
                
                if (prev != NULL) {
                    tmp = prev;
                    head = prev;
                } else if( next != NULL){
                    tmp = next;
                    head = next;
                } else {
                    tmp = NULL;
                    ret = NULL;
                    head = NULL;
                    break;
                }
            }else{
                head = tmp; // for save cookie link list ref;
                tmp = tmp->nextSub;
            }
        }
        
        if (head != NULL) {
            ret = FindFirstCookie(head);
        }
        
    }
    return ret;
}

