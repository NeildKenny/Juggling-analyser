#include "KinectCapture.h"
#include "CameraCapture.h"
#include "FileCapture.h"
#include "Tracking.h"
#include "DatabaseHandler.h"
void showKinect(cv::vector<cv::Mat> dataStream ){
	
		
		dataStream[0];
		if(!dataStream[DEPTH_STREAM].empty()){
		cv::imshow("Depth", dataStream[DEPTH_STREAM]);
		}
		if(!dataStream[COLOR_STREAM].empty()){
		cv::imshow("Colour", dataStream[COLOR_STREAM]);
		}else{
		std::cout << "It aint workin!" << std::endl;
		}

		
}

void showCamera(cv::Mat camStream){
	cv::imshow("Webcam", camStream);

}


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
 int max_dilation =20;
 const int max_element = 3;



void createTrackBar(std::string trackBarName){

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
}



cv::Mat binaryImageCapture(cv::Mat actual){
	
		cv::Mat hsv;
		cv::Mat binImage;
		cv::GaussianBlur(actual, actual, cv::Size(9, 9), 1.5);
		cv::cvtColor(actual, hsv, cv::COLOR_BGR2HSV);
		cv::inRange(hsv, cv::Scalar(H_MIN, S_MIN, V_MIN), cv::Scalar(H_MAX, S_MAX, V_MAX), binImage);


		
	
		
		return binImage;
}

cv::Mat binaryImageCaptureTest(cv::Mat actual){
	
		cv::Mat hsv;
		cv::Mat binImage;
		cv::GaussianBlur(actual, actual, cv::Size(9, 9), 1.5);
		cv::cvtColor(actual, hsv, cv::COLOR_BGR2HSV);
		cv::inRange(hsv, cv::Scalar(51, 141, 57), cv::Scalar(103, 256, 256), binImage);


		
	//	cv::imshow("HSV", hsv);
	//	cv::imshow("threshold", binImage);
		//cv::imshow("Actual", actual);
		
		return binImage;
}
void cleanBinaryImage(cv::Mat &binaryImage){



}
void main(){

	/*
	1: webcam 
	2: kinect
	3: file
	
	*/
	int feed = 1;
	std::string fileURI1 = "C:/test1.avi";
	

	/*
		Display stream from camera 
	*/
	
		int t_msec;
		cv::Mat actual;
		cv::Mat hsv;
		cv::Mat threshold;
		createTrackBar("TrackBarMofo");
		Tracking trackObject;
		DatabaseHandler databaseHandlderObject;
		std::vector<Ball> balls; 
	if(feed==1){
		CameraCapture camCaptureObject;

		//std::vector<Ball> balls; 
		while(true){
			
			actual = camCaptureObject.Capture();
			
			cv::flip(actual, actual, 1);

			
			//threshold = binaryImageCapture(actual);
			threshold = binaryImageCapture(actual);
			
			
			cv::imshow("bin", threshold);
			t_msec = clock();
			trackObject.Detect( threshold, actual, balls,erosion_element,  dilation_element, dilation_size, erosion_size, t_msec);
			
			
			cv::imshow("filterbin", threshold);
			
			cv::imshow("Actual", actual);
	
			for(int j=0;j<balls.size();j++){
				std::cout << "Ball number: " << balls.at(j).getBallNum() << "  Position x: " << balls.at(j).getXPos() << " Postion y:  " << balls.at(j).getYPos() << std::endl;
			}

			if(cv::waitKey(1) >=0) break;
		}

	}

	/*
		Display Kinect depth and rgb
	*/
	if(feed==2){
		KinectCapture KinectCaptureObject;
		cv::vector<cv::Mat> dataStream;
		while(true){
			
			
			dataStream=KinectCaptureObject.CaptureFromKinect();
			
			dataStream[0];
			if(!dataStream[DEPTH_STREAM].empty()){
				cv::imshow("Depth", dataStream[DEPTH_STREAM]);
				
				if(!balls.empty()){
					for(int i = 0; i < balls.size(); i++){
					
						balls.at(i).setZPos((double)dataStream[DEPTH_STREAM].at<unsigned short>(balls[balls.size()].getXPos()+7, balls[balls.size()].getYPos()));
					}
					std::cout <<(double)dataStream[DEPTH_STREAM].at<unsigned short>(balls[balls.size()].getXPos()+7, balls[balls.size()].getYPos()) << std::endl;


				}
				
		
			}
			if(!dataStream[COLOR_STREAM].empty()){
				cv::cvtColor(dataStream[COLOR_STREAM],dataStream[COLOR_STREAM], cv::COLOR_BGR2RGB);

			
				threshold = binaryImageCapture(dataStream[COLOR_STREAM]);
				cv::imshow("Bin", threshold);
				t_msec = clock();
				trackObject.Detect(threshold, dataStream[COLOR_STREAM], balls,erosion_element,  dilation_element, dilation_size, erosion_size, t_msec);
			

			cv::imshow("Colour", dataStream[COLOR_STREAM]);
			}else{
			std::cout << "Frames dropped" << std::endl;
			}
			/*if(!balls.empty()&&!dataStream[DEPTH_STREAM].empty()&&!dataStream[COLOR_STREAM].empty()){
					std::cout << dataStream[DEPTH_STREAM].at<cv::Vec3b>(balls.at(0).getXPos(), balls.at(0).getYPos()) << std::endl;	
				}*/
			
			

			if(cv::waitKey(20)>= 0)
				break;
			
		}
	}


	/*
		Display from file
	*/
	bool close = true;
	if(feed==3){
		FileCapture fileCaptureObject;
		cv::Mat fooActual;
		cv::Mat threshold;
		cv::Mat hsv;
		Tracking trackObject;
		createTrackBar("TrackBarMofo");
		while(close = true){

		
		if(!fileCaptureObject.OpenFile(fileURI1)) break;
			
			while(true){
					
				if(!fileCaptureObject.Capture(fooActual)) break;
					
								
					threshold = binaryImageCapture(fooActual);
					cv::cvtColor(fooActual, hsv, cv::COLOR_BGR2HSV);
			
				
					cv::imshow("filterbin", threshold);
					
					int t_msec = clock();
					trackObject.Detect(threshold, fooActual, balls, erosion_element, dilation_element, dilation_size, erosion_size, t_msec);
					cv::imshow("Actual", fooActual);

					if(cv::waitKey(10)>= 0)
				break;

			}
		}
	}
}