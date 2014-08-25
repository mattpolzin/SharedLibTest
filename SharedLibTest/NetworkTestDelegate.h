//
//  NetworkTestDelegate.h
//  SharedLibTest
//
//  Created by Mathew Polzin on 8/14/14.
//  Copyright (c) 2014 Mathew Polzin. All rights reserved.
//

#ifndef SharedLibTest_NetworkTestDelegate_h
#define SharedLibTest_NetworkTestDelegate_h

class NetworkTestDelegate {
	
public:
	/**
	 * Called each time more data is available from a test poll.
	 * May be called with 0 bytes if no data is returned by a poll.
	 */
	virtual void dataAvailable(char *ptr, size_t size, size_t num) = 0;
};

#endif
