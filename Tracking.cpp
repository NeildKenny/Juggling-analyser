
#include "stdAfx.h"
#include "Tracking.h"


Tracking::Tracking(void)
{
}


Tracking::~Tracking(void)
{
}


std::string Tracking::intToString(int number){


	std::stringstream ss;
	ss << number;
	return ss.str();
}

void Tracking::drawCoordinates(std::vector<Ball> balls, cv::Mat &frame){
	for(int i = 0; i < balls.size(); i++){
		
		
		cv::circle(frame, cv::Point(balls[i].getXPos(), balls[i].getYPos()), 10, cv::Scalar(255, 0, 0));
		
		cv::putText(frame,"Ball pos: " + intToString(balls[i].getXPos()) + ", " + intToString(balls[i].getYPos()) + ", " + intToString(balls[i].getZPos()), cv::Point(balls[i].getXPos()+ 20, balls[i].getYPos()), 1, 1, cv::Scalar(255, 0, 0));
		cv::putText(frame, "Ball Number: " + intToString(balls[i].getBallNum()), cv::Point(balls[i].getXPos() + 20, balls[i].getYPos() + 20), 1, 1, cv::Scalar(0, 0, 255));
		

	}
}

void Tracking::DrawPath(std::vector<Ball> balls, cv::Mat &frame){
	for(int i = 0; i<balls.size(); i++){

		
		
		if(balls[i].getLastX()>=0 && balls[i].getLastX()>=0 && balls[i].getXPos()>=0 && balls[i].getYPos()>=0){

				  cv::line(frame, cvPoint(balls[i].getLastX(), balls[i].getLastX() ), 
					  cvPoint(balls[i].getXPos(), balls[i].getYPos()), cvScalar(0,0,255), 4);

		 }
	}
}


void Tracking::Detect(cv::Mat &binFrame, cv::Mat &cameraFrame, std::vector<Ball> &balls,  int _ero, int _dila, int ero_size, int dila_size, int t_msec){
	
	std::vector<Ball> newPositions; 
	//std::cout << "In Tracking" << std::endl;
	
	if(_dila > 0){
		binFrame = dilation(binFrame, _dila, dila_size);
	}

	if(_ero > 0){
		binFrame = erosion(binFrame, _ero, ero_size);
	}
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	/*
	Find contours(outline)  in a binary image, modifiying the image while finding these contours
	Conoturs detected contours in a vector of vector of points
	Hierarchy the hierachy in which the contours are represented
	CV_RETR_CCOMP the style in which they are returned
	CV_CHAIN_APPROX_SIMPLE retreieves end points of contours
	
	*/
	cv::findContours(binFrame, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	cv::imshow("contours", binFrame);
	bool objectFound = false;

	if(hierarchy.size() > 0){
		int numberOfObjects = hierarchy.size();
	
		if(numberOfObjects < MAX_OBJECTS){
			for(int i = 0; i >= 0; i = hierarchy[i][0]){
				//Contours are turned into moments
				cv::Moments moment = moments((cv::Mat)contours[i]);
				
				double area = moment.m00;
				//area of moments is checked against min and max areas allowed for objects this is to help against noise
				if(area > MIN_OBJECT_AREA && area < MAX_OBJECT_AREA  ){//
					Ball ballObject; 
					//if makes new balls
					ballObject.setXPos(moment.m10/area);
					ballObject.setYPos(moment.m01/area);
					ballObject.setTime(t_msec);
					ballObject.setPoints();
					//std::cout << ballObject.getXPos() << std::endl;
					//std::cout << ballObject.getYPos() << std::endl;
					//std::cout << area << std::endl;
					newPositions.push_back(ballObject);
					
					objectFound = true; 
				} else{
					objectFound = false;
				}
			}
			
			if(objectFound == true){

			
				int elemPos;
				if(balls.size() !=0){

					//more posisitons than balls 
					if(balls.size() <= newPositions.size() ){
					//	std::cout << "Ball(s) on screen updating positions" << std::endl;
						for(int i = 0; i < balls.size(); i++){
						
								int tempX  = balls[i].getXPos();
								int tempY = balls[i].getYPos();
							
								elemPos = Track(newPositions, tempX, tempY);

					
								std::cout << elemPos << std::endl;
								balls[i].setXPos(newPositions[elemPos].getXPos());
								balls[i].setYPos(newPositions[elemPos].getYPos());
								balls[i].setTime(t_msec);
								balls[i].setPoints();
								//std::cout << "position size old: " << newPositions.size() << std::endl;
								newPositions.erase(newPositions.begin()+elemPos);
								//std::cout << "position size new: " << newPositions.size() << std::endl;
					
						}	// extra ball added 
					} else if(balls.size() > newPositions.size()){
				
						std::vector<Ball> tempBall;
						for(int i = 0; i < newPositions.size(); i++){
							int tempX  = newPositions[i].getXPos();
							int tempY = newPositions[i].getYPos();
							elemPos = Track(balls, tempX, tempY);
						
							balls[elemPos].setXPos(tempX);
							balls[elemPos].setYPos(tempY);
							balls[elemPos].setTime(t_msec);
							balls[elemPos].setPoints();

							tempBall.push_back(balls[elemPos]);
						}
						newPositions.clear();
						balls = tempBall;
						tempBall.clear();
					}
				}

				/*
				if newPositions is not equal to 0 after going through the above loop add a new ball to the vector
				*/
				
				if(newPositions.size()!=0){
					for( int i = 0; i < newPositions.size(); i++ ){
						
						newPositions[i].setBallNum(balls.size()+1);
						newPositions[i].setTime(t_msec);
						newPositions[i].setPoints();
						balls.push_back(newPositions[i]);
					//	std::cout << "New  ball created: " << balls.size() << std::endl;
					
							
					}
				
				}
			
				newPositions.clear();
		
				//drawCoordinates(balls, cameraFrame);

				
			}
		}
	}else{
		putText(cameraFrame, "ADJUST FILTER", cv::Point(0, 50), 1, 2, cv::Scalar(0, 0, 255), 3);

		balls.clear();
	//	std::cout << "balls cleared" << std::endl;
	}
	

	
}

int Tracking::Track(std::vector<Ball> positions, int x, int y){
	double distTemp= 9999999.0;
	double dist;
	int j = 0;

	//std::cout << "Checking dist" << std::endl;
	for(int i = 0; i < positions.size(); i++){
		dist =  Distance(positions[i].getXPos(), positions[i].getYPos(), x, y);
		//std::cout << "Distance: " << i << " : " << dist << "distance temp: " << distTemp << std::endl;
		if(distTemp > dist ){
			//std::cout << dist << std::endl;


			distTemp = dist;

		
			j = i;
		}
	}

	
	return j;
}

