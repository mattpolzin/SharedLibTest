#!/bin/bash

############################################################
# Compile script written by Mathew Polzin (matt@vadio.com).
# Based on curl for iOS compilation tips at
# http://seiryu.home.comcast.net/~seiryu/libcurl-ios.html
############################################################



CURL_LOCATION="~/staging/curl/curl-7.37.1/"
IOS_MIN_VERSION="4.3"
DEVICE_ARCHS=("armv7" "armv7s")
DEVICE_SDK="/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS7.1.sdk"
SIMULATOR_ARCHS=("i386")
SIMULATOR_SDK="/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator7.1.sdk"
BUILD_FLAGS=""

# IF you want to 'make install', the following variable determines where the library
# is installed.
INSTALL_LOC=""


##############################
# General setup
##############################
export IPHONEOS_DEPLOYMENT_TARGET=$IOS_MIN_VERSION
export CC="/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang"

eval cd "$CURL_LOCATION"
if [ ! -e lib_builds ]
then
	mkdir lib_builds
else
	rm ./lib_builds/*
fi

# curl_compile takes one argument: the architecture to compile for.
function curl_compile {
	./configure --disable-shared --enable-static --host="$1-apple-darwin" --prefix="$INSTALL_LOC" $BUILD_FLAGS
	make -j `sysctl -n hw.logicalcpu_max`

	cp lib/.libs/libcurl.a "lib_builds/libcurl-$1.a"
}


##############################
# Device compilation
##############################
for ii in "${DEVICE_ARCHS[@]}"
do
	:
	export CFLAGS="-arch $ii -pipe -Os -gdwarf-2 -isysroot $DEVICE_SDK"
	export LDFLAGS="-arch $ii -isysroot $DEVICE_SDK"

	curl_compile $ii
done


##############################
# Simulator compilation
##############################
for ii in "${SIMULATOR_ARCHS[@]}"
do
	:
	export CFLAGS="-arch $ii -pipe -Os -gdwarf-2 -isysroot $SIMULATOR_SDK"
	export CPPFLAGS="-D__IPHONE_OS_VERSION_MIN_REQUIRED=${IPHONEOS_DEPLOYMENT_TARGET%%.*}0000"
	export LDFLAGS="-arch $ii -isysroot $SIMULATOR_SDK"

	curl_compile $ii
done


##############################
# General cleanup
##############################
make clean


##############################
# Library combination
##############################
cd lib_builds
lipo -create -output libcurl.a libcurl*
