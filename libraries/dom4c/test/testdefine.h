//
//  testdefine.h
//  dom4c
//
//  Created by vhly on 12-11-21.
//  Copyright (c) 2012年 vhly. All rights reserved.
//

#ifndef dom4c_testdefine_h
#define dom4c_testdefine_h

#define testAssertEquals(ext, act, msg) if ( (ext) == (act) ){ printf("Equals\n"); } else { printf(msg); }

#define testAssertStringEquals(ext, act, msg) if ( strcmp((ext),(act)) == 0 ){ printf("Equals\n"); } else { printf(msg); }


#endif
