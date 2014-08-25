//
//  NetworkTest.h
//  SharedLibTest
//
//  Created by Mathew Polzin on 8/11/14.
//  Copyright (c) 2014 Mathew Polzin. All rights reserved.
//

#ifndef __SharedLibTest__NetworkTest__
#define __SharedLibTest__NetworkTest__

#include <iostream>
#include <curl/curl.h>
#include "NetworkTestDelegate.h"


class NetworkTest {
private:
	NetworkTestDelegate *delegate;
	CURL *curl;
	
public:
	NetworkTest(NetworkTestDelegate *delegate);
	~NetworkTest();
	void poll();
};

#endif /* defined(__SharedLibTest__NetworkTest__) */
