#include "stdAfx.h"
#include "OpenKinect.h"


OpenKinect::OpenKinect(void)
{
	InitialiseKinect();
	
	
	/*
	Registration mode; this is so that the videos streams the same x,y coordinates 
	as the cameras are several centemeters apart if you were to forgo doing this you 
	will get an offset result
	From openni documentation(http://www.openni.org/openni-programmers-guide/):
	
	"IMAGE_REGISTRATION_DEPTH_TO_IMAGE – The depth image is transformed to have 
	the same apparent vantage point as the RGB image."
	*/
	kinect_device.setImageRegistrationMode(openni::IMAGE_REGISTRATION_DEPTH_TO_COLOR);
	
	if(!kinect_depth.isValid() && !kinect_color.isValid()){
		 
		ErrorMessage("No valid streams exist");
		
	}

	this->kinect_streams = new openni::VideoStream*[NUM_STREAMS];
	kinect_streams[DEPTH_STREAM] = &kinect_depth;
	kinect_streams[COLOR_STREAM] = &kinect_color; 

	std::cout << "end of openKinectConstructor" << std::endl;
}


OpenKinect::~OpenKinect(void)
{

	

}




bool OpenKinect::InitialiseKinect(void){
		
	kinect_status = openni::STATUS_OK;
	
	deviceURI = openni::ANY_DEVICE;

	kinect_status = openni::OpenNI::initialize();



	kinect_status = kinect_device.open(deviceURI); 

	if(kinect_status != openni::STATUS_OK){
		return ErrorMessage("Failed to open kinect:");
		
	}

	InitialiseDepthStream();
	InitialisecolorStream();

	
	return true;

}



bool OpenKinect::InitialisecolorStream(void){
	kinect_status = kinect_color.create(kinect_device, openni::SENSOR_COLOR);

		
	if(kinect_status == openni::STATUS_OK){
		
		kinect_status = kinect_color.start();
		if(kinect_status != openni::STATUS_OK){
		
			return ErrorMessage("Failed to Open color stream 1: ");
		}
	} else {
			
		return ErrorMessage("Failed to open color stream 2: ");
	}
	return true;
}



bool OpenKinect::InitialiseDepthStream(void){
	kinect_status = kinect_depth.create(kinect_device, openni::SENSOR_DEPTH);
		

	if(kinect_status == openni::STATUS_OK){
	
		kinect_status = kinect_depth.start();
		
		
		
		if(kinect_status != openni::STATUS_OK){
			return ErrorMessage("Failed to open Depth stream 1: ");
		}
	} else {
		return ErrorMessage("Failed to open depth stream 2:");
	}
	
	return true;
}


void OpenKinect::RegisterCameras(void){
	kinect_device.setImageRegistrationMode(openni::IMAGE_REGISTRATION_DEPTH_TO_COLOR);
}

bool OpenKinect::ErrorMessage(std::string errorMessage){
		std::cout << errorMessage << std::cout << openni::OpenNI::getExtendedError() << std::endl;
		openni::OpenNI::shutdown();
		Sleep(1000);
		return false;
}