/*
Author: Neil Kenny 

The prupose of this class is to open a stream with the kinect to allow us to take data

*/
#pragma once

#include <OpenNI.h>
#include <iostream>
#include <vector>
#include <string>

#define DEPTH_STREAM 0
#define COLOR_STREAM 1

#define NUM_STREAMS 2

class OpenKinect
{
	/**
	Sets registration on device
	*/
	void RegisterCameras(void);
	/**
	Links the program with the kinect and initialises the streams
	@return returns bool as to whether or not the device has opened
	
	*/
	bool InitialiseKinect(void);

	/**
	Creates Stream for colour
	@return returns bool if initialized

	*/
	bool InitialisecolorStream(void);
	/**
	Creates Stream for colour
	@return returns bool if initialized

	*/
	bool InitialiseDepthStream(void);
	/**
	Creates error message
	@param [in] error message
	@return returns bool if initialized

	*/
	bool ErrorMessage(std::string errorMessage);
public:

	/**
	Default Constructor
	Initialises the kinect
	Setsregistration mode
	Set streams
	*/
	OpenKinect(void);

	/**
	Default destructor
	Closes kinect
	*/
	~OpenKinect(void);
	
	/**
	URI for kinect
	*/
	const char* deviceURI;
	/**
	Device Status
	*/
	openni::Status kinect_status;
	/**
	Device Objects
	*/
	openni::Device kinect_device;
	/**
	Streams
	*/
	openni::VideoStream kinect_depth, kinect_color, **kinect_streams;
	
};

