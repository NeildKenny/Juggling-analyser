#include "stdAfx.h"
#include "CameraCapture.h"

CameraCapture::CameraCapture(void)
{
	captureObject.open(CV_CAP_ANY);

}


CameraCapture::~CameraCapture(void)
{
}
 cv::Mat CameraCapture::Capture(void){
	
	
	
	captureObject.read(camImage);
	
	return camImage;
	
}