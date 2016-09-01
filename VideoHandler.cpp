#include "stdAfx.h"
#include "VideoHandler.h"

 int H_MIN = 0;
 int H_MAX = 256;
 int S_MIN = 0;
 int S_MAX = 256;
 int V_MIN = 0;
 int V_MAX = 256;
 int erosion_element = 0;
 int dilation_element = 0;
 int erosion_size = 0; 
 int dilation_size = 0;
 int max_erosion = 20;
 int max_dilation = 20;
 const int max_element = 3;


VideoHandler::VideoHandler(void)
{

	getBase = false;
	feed = 0; 
	t_msec = 0;
	baseHeight =0;

}

VideoHandler::~VideoHandler(void){

}

void VideoHandler::trackBasePattern(){
	getBase  = true;

	//sets countdown timer
	double time  = clock();
	//10 seconds to start, 20 seconds on pattern testing
	baseCounter = time + 10000.0;
	captureTime = time + 30000.0;

	//Alerts timer has started
	std::cout << "\a" << std::endl;
}


void VideoHandler::setFeed(int _feed){
	feed = _feed;
	
}
int VideoHandler::getFeed(void){
	return feed;
}

void VideoHandler::ManageFeeds(){


	if(feed==1){
		Webcam();
	}
	if(feed==2){
		Kinect();
	}
	if(feed==3){
		File();
	}

}
std::vector<ThrowData> VideoHandler::getJugglingdata( void ){
	return jugglingDataObject.CompileData();
}

void VideoHandler::Webcam(){

	
	
	CameraCapture camCaptureObject;
	
	while(feed==1){
		std::vector<ThrowData> foobared = getJugglingdata();
		
		actual = camCaptureObject.Capture();
		cv::flip(actual, actual, 1);

		//threshold = binaryImageCapture(actual);
		threshold = binaryImageCapture(actual);

		cv::imshow("bin", threshold);
		t_msec = clock();
		trackObject.Detect( threshold, actual, balls, erosion_element, dilation_element, dilation_size, erosion_size, t_msec);


		for(size_t i = 0; i < balls.size(); i++){
					

			t_msec = clock();
			if(t_msec >= balls[i].getCatchTime()){
				projectileObject.BallInMotion(balls[i], baseHeight);
				
			}	
					
			if(getBase==true && t_msec >= baseCounter && t_msec >= balls[i].getCatchTime() && balls[i].getMaxHeight() > 0.0 ){

				baseHeights.push_back(balls[i].getMaxHeight());
						
			}

			if(getBase == true && t_msec >= captureTime){

				//Alerts user timer has stopped
				std::cout << "\a" << std::endl;
				baseHeight = siteswapObject.BaseHeight(baseHeights);
				baseHeights.clear();
				getBase = false;
			}
						
		}

		
		for(std::vector<IBallObserver*>::iterator it = mB_observers.begin(); it != mB_observers.end(); ++it)
		{
			(*it)->onBallsUpdated(balls);
		}
		//for(std::vector<IJugglingDataObserver*>::iterator it = mT_observers.begin(); it != mB_observers.end();++it){
		//	//(*it)->onJugglingDataUpdated(
		//}
		trackObject.drawCoordinates(balls, actual);
		//cv::imshow("filterbin", threshold);
		cv::imshow("Actual", actual);

		if(cv::waitKey(20)==27 ){
			cv::destroyAllWindows();
			feed=0;
			break;
		}
	}
}


void VideoHandler::Kinect(){
	std::cout << "In Kinect" << std::endl;
	cv::vector<cv::Mat> dataStream;

	cv::Mat trackedImage;
	KinectCapture *KinectCaptureObject = new KinectCapture();



	while(feed==2){
			
			
		dataStream=KinectCaptureObject->CaptureFromKinect();
			
		dataStream[0];
		
		
		if(!dataStream[COLOR_STREAM].empty()){

			t_msec = clock();
			cv::cvtColor(dataStream[COLOR_STREAM],dataStream[COLOR_STREAM], cv::COLOR_BGR2RGB);
			trackedImage=dataStream[COLOR_STREAM].clone();
			//dataStream[COLOR_STREAM];
			//cv::blur(trackedImage, trackedImage,cv::Size( 3, 3 ), cv::Point(-1,-1));
			
		//		cv::GaussianBlur(trackedImage,dataStream[COLOR_STREAM], cv::Size(7,7),1.5, 1.5, cv::BORDER_DEFAULT);
			//cv::imshow("filter", dataStream[COLOR_STREAM]);
			threshold = binaryImageCapture(dataStream[COLOR_STREAM]);
		
			cv::imshow("Bin", threshold);	
			trackObject.Detect(threshold, dataStream[COLOR_STREAM], balls,erosion_element,  dilation_element, dilation_size, erosion_size, t_msec);
			
			
		

		}if(!dataStream[DEPTH_STREAM].empty()){
	
		
		
				
			
		}else{
			std::cout << "Frames dropped" << std::endl;
		}

		if(!dataStream[DEPTH_STREAM].empty() && !dataStream[COLOR_STREAM].empty()){
			for(size_t i = 0; i < balls.size(); i++){
					
				balls[i].setZPos((int)dataStream[DEPTH_STREAM].at <unsigned short>((cv::Point(balls[i].getXPos(), balls[i].getYPos()))));

				t_msec = clock();
				if(t_msec >= balls[i].getCatchTime()){
					projectileObject.BallInMotion(balls[i], baseHeight);
					
				}	
					
				if(getBase==true && t_msec >= baseCounter && t_msec >= balls[i].getCatchTime() && balls[i].getMaxHeight() > 0.0 ){

					baseHeights.push_back(balls[i].getMaxHeight());
						
				}
				if(getBase == true && t_msec >= captureTime){

					baseHeight = siteswapObject.BaseHeight(baseHeights);
					baseHeights.clear();
					getBase = false;
				}
						

				jugglingDataObject.setSiteswapData(balls[i]);
				
			}

			trackObject.drawCoordinates(balls,trackedImage);

			cv::imshow("Depth", dataStream[DEPTH_STREAM]);
			
			cv::imshow("Colour", trackedImage);

		}
		
		for(std::vector<IBallObserver*>::iterator it = mB_observers.begin(); it != mB_observers.end(); ++it)
		{
			(*it)->onBallsUpdated(balls);
		}

		/*for(std::vector<IJugglingDataObserver>::iterator it = Tm_obervers.begin(); it != Tm_observers.end(); ++it)
		{
			(*it)->onJugglingDataUpdate();
		}*/
		


		if(cv::waitKey(20)==27 ){
			cv::destroyAllWindows();
			feed=0;
			break;
		}
	}
}

void VideoHandler::setFileUri(System::String^ _fileURI){
	MarshalString (_fileURI, fileURI);
	
}

void VideoHandler::File(void){
	FileCapture fileCaptureObject;
		
	while(feed==3){


		
		if(!fileCaptureObject.OpenFile(fileURI)) break;
			
			while(feed==3){
					
				if(!fileCaptureObject.Capture(actual)) break;
					
					int actual_height = actual.rows/2;
					int actual_width = actual.cols/2;
					cv::Mat temp = actual;

				//	rotate(actual, actual, 90);

					threshold = binaryImageCapture(actual);
					//cv::cvtColor(actual, actual, cv::COLOR_BGR2HSV);
			
					
					cv::imshow("filterbin", threshold);
					
					int t_msec = clock();
					trackObject.Detect(threshold, actual, balls, erosion_element, dilation_element, dilation_size, erosion_size, t_msec);
				
				//	trackObject.drawCoordinates(balls, actual);

					
					for(size_t i = 0; i < balls.size(); i++){
					

						t_msec = clock();
						if(t_msec >= balls[i].getCatchTime()){
							projectileObject.BallInMotion(balls[i], baseHeight);
				
						}	
					
						if(getBase==true && t_msec >= baseCounter && t_msec >= balls[i].getCatchTime() && balls[i].getMaxHeight() > 0.0 ){

							baseHeights.push_back(balls[i].getMaxHeight());
						
						}
						if(getBase == true && t_msec >= captureTime){

							//Alerts user timer has stopped
							std::cout << "\a" << std::endl;
							baseHeight = siteswapObject.BaseHeight(baseHeights);
							baseHeights.clear();
							getBase = false;
						}
						
					}

		
				for(std::vector<IBallObserver*>::iterator it = mB_observers.begin(); it != mB_observers.end(); ++it)
				{
					(*it)->onBallsUpdated(balls);
				}

				trackObject.drawCoordinates(balls, actual);
				cv::imshow("Actual", actual);
						
				if(cv::waitKey(10)== 27)
					break;
			}//end loop
			if(cv::waitKey(10)== 27)
				break;
		}
}
//void VideoHandler::rotate(cv::Mat& src, double angle, cv::Mat& dst)
//{
//    int len = std::max(src.cols, src.rows);
//    cv::Point2f pt(len/2., len/2.);
//    cv::Mat r = cv::getRotationMatrix2D(pt, angle, 1.0);
//
//    cv::warpAffine(src, dst, r, cv::Size(len, len));
//}

void VideoHandler::rotate(cv::Mat &src, cv::Mat &dst, int angle)
{   
   if(src.data != dst.data){
       src.copyTo(dst);
   }

   angle = ((angle / 90) % 4) * 90;

   //0 : flip vertical; 1 flip horizontal
   bool const flip_horizontal_or_vertical = angle > 0 ? 1 : 0;
   int const number = std::abs(angle / 90);          

   for(int i = 0; i != number; ++i){
       cv::transpose(dst, dst);
       cv::flip(dst, dst, flip_horizontal_or_vertical);
   }
}
void VideoHandler::addBallObserver( IBallObserver* observer )
{
	removeBallObserver( observer );
	mB_observers.push_back( observer );
}

void VideoHandler::removeBallObserver( IBallObserver* observer )
{
	mB_observers.erase( std::remove( mB_observers.begin(), mB_observers.end(), observer ), mB_observers.end() );
}

void VideoHandler::addThrowObserver( IJugglingDataObserver* observer)
{
	removeThrowObserver( observer );
	mT_observers.push_back( observer );
}

void VideoHandler::removeThrowObserver( IJugglingDataObserver* observer)
{
	mT_observers.erase( std::remove( mT_observers.begin(), mT_observers.end(), observer ), mT_observers.end() );
}

void VideoHandler::createTrackBar(std::string trackBarName){

	cv::namedWindow(trackBarName, 0);

	cv::createTrackbar("Hue min", trackBarName, &H_MIN, H_MAX);
	cv::createTrackbar("Hue max", trackBarName, &H_MAX, H_MAX);
	cv::createTrackbar("Sat min", trackBarName, &S_MIN, S_MAX);
	cv::createTrackbar("Sat max", trackBarName, &S_MAX, S_MAX);
	cv::createTrackbar("Val min", trackBarName, &V_MIN, V_MAX);
	cv::createTrackbar("Val max", trackBarName, &V_MAX, V_MAX);

	cv::createTrackbar("Erosion type", trackBarName, &erosion_element, max_element);
	cv::createTrackbar("Erosion size", trackBarName, &erosion_size, max_erosion);

	cv::createTrackbar("Dilation type", trackBarName, &dilation_element, max_element);
	cv::createTrackbar("Dilation size", trackBarName, &dilation_size, max_dilation);
	cv::resizeWindow(trackBarName, 640, 480);
}


cv::Mat VideoHandler::binaryImageCapture(cv::Mat actual){
	cv::Mat hsv;
	cv::Mat binImage;

	//cv::cvtColor(actual, hsv, CV_RGB2HLS);
	cv::cvtColor(actual, hsv, CV_BGR2HSV);
	cv::imshow("hsv", hsv);
	cv::inRange(hsv, cv::Scalar(H_MIN, S_MIN, V_MIN), cv::Scalar(H_MAX, S_MAX, V_MAX), binImage);

		
	return binImage;
}

/**
Testing function for constant values
*/

cv::Mat VideoHandler::binaryImageCaptureConst(cv::Mat actual){
	cv::Mat hsv;
	cv::Mat binImage;

	cv::cvtColor(actual, hsv, CV_BGR2YCrCb);
	cv::inRange(hsv, cv::Scalar(24, 115, 102), cv::Scalar(48, S_MAX, V_MAX), binImage);

		
	return binImage;
}

/*
Converts from System[String^] string to standard [std::string] string 

Taken from: http://msdn.microsoft.com/en-us/library/1b4az623.aspx
*/

void VideoHandler::MarshalString ( System::String^ s, std::string& os )
{
using namespace System::Runtime::InteropServices;
const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
os = chars;

}
