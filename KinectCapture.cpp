#include "stdAfx.h"
#include "KinectCapture.h"


KinectCapture::KinectCapture(void)
{
	//std::cout << "Constructor called " << std::endl;
}


KinectCapture::~KinectCapture(void)
{
	
	kinect_depth.stop();
	kinect_color.stop();
	kinect_device.close();
	openni::OpenNI::shutdown();


}


cv::vector <cv::Mat> KinectCapture::CaptureFromKinect(){
		cv::vector<cv::Mat> frames;
		cv::Mat _colorMat;
	
		cv::Mat _depthMat;
		colorCaptured, depthCaptured = false;
		

		
		while(!colorCaptured || !depthCaptured || depthTimestamp != colorTimestamp){
		
			kinect_status = openni::OpenNI::waitForAnyStream(kinect_streams, NUM_STREAMS, &currentStream, STREAM_TIMEOUT );
		
			if(kinect_status != openni::STATUS_OK){
				exit(1);
			}

			switch(currentStream){
			
				case COLOR_STREAM:
					_colorMat = KinectCaptureColor();
			
				
					break;
				case DEPTH_STREAM:
					_depthMat = KinectCaptureDepth();
				
						
					break;
				default:
					break;
			}

		}
		
		frames.push_back(_depthMat);
		frames.push_back(_colorMat);
		//std::cout << "out of loop" << std::endl;
		return frames;

}

cv::Mat KinectCapture::KinectCaptureColor(){
	cv::Mat colorMat, bufferMat;
	
	kinect_color.readFrame(&colorFrame);
	
	colorMat.create(colorFrame.getHeight(), colorFrame.getWidth(), CV_8UC3);
	bufferMat.create(colorFrame.getHeight(),colorFrame.getWidth(), CV_8UC3);
	bufferMat.data = (uchar*)colorFrame.getData();
	this->colorTimestamp = colorFrame.getTimestamp() >> 16;
	
	colorCaptured = true;
	
	
	colorMat = bufferMat;

	return colorMat;
}

cv::Mat KinectCapture::KinectCaptureDepth(){

	cv::Mat depthMat;
	kinect_depth.readFrame(&depthFrame);
	depthMat.create(depthFrame.getHeight(), depthFrame.getWidth(), CV_16UC1);
	depthMat.data = (uchar*)depthFrame.getData();
	this->depthTimestamp = depthFrame.getTimestamp() >> 16;
	depthCaptured = true;
	
	return depthMat;
}

