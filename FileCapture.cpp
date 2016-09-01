#include "stdAfx.h"
#include "FileCapture.h"


FileCapture::FileCapture(void)
{
	

}


FileCapture::~FileCapture(void)
{
}

bool FileCapture::OpenFile(std::string filePath){
	
		
	captureObject.open(filePath);
		if(!captureObject.isOpened()){
			std::cout << "failed to open" << std::endl;
			return false;
		}

	return true;
	

}

bool  FileCapture::Capture(cv::Mat &videoFrame){
	
			
	captureObject.read(videoFrame);
		
		
	if(videoFrame.empty()){
		std::cout << "frame empty" << std::endl;
		captureObject.release();
		return false;
	}
	
	
	return true;
}
