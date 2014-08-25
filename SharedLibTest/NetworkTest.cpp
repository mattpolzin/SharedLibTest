//
//  NetworkTest.cpp
//  SharedLibTest
//
//  Created by Mathew Polzin on 8/11/14.
//  Copyright (c) 2014 Mathew Polzin. All rights reserved.
//

#include "NetworkTest.h"

size_t NetworkTest_write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	NetworkTestDelegate *delegate = (NetworkTestDelegate*)userdata;
	delegate->dataAvailable(ptr, size, nmemb);
	return size * nmemb;
}


NetworkTest::NetworkTest(NetworkTestDelegate *delegate) {
	this->delegate = delegate;
	this->curl = curl_easy_init();
	if (!this->curl) {
		throw 1;
	}
}

void NetworkTest::poll() {
	CURLcode res;
	curl_easy_setopt(this->curl, CURLOPT_URL, "http://www.vadio.com/api/player_settings");
    curl_easy_setopt(this->curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(this->curl, CURLOPT_ENCODING, "gzip");
	curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, this->delegate);
	curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, &NetworkTest_write_callback);
	res = curl_easy_perform(this->curl);
	if (res != CURLE_OK) {
		fprintf(stderr, "curl failed: %s\n",
				curl_easy_strerror(res));
	}
}

NetworkTest::~NetworkTest() {
	curl_easy_cleanup(this->curl);
}
