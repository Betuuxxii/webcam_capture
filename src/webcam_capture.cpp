
//opencv
#include "opencv2/opencv.hpp"

//std
#include <iostream>
#include <cstdlib>

//main
int main(int argc, char *argv[])
{
    cv::VideoCapture camera; //OpenCV video capture object
    cv::Mat image; //OpenCV image object
    cv::Mat imageCopy; //OpenCV image object
	int cam_id; //camera id . Associated to device number in /dev/videoX
	int user_key; //user pressed key to quit
	cv::Vec3b pixel_intensity; //pixel RGB intensity

	//check user args
	switch(argc)
	{
		case 1: //no argument provided, so try /dev/video0
			cam_id = 0;
			break;
		case 2: //an argument is provided. Get it and set cam_id
			cam_id = atoi(argv[1]);
			break;
		default:
			std::cout << "Invalid number of arguments. Call program as: webcam_capture [video_device_id]. " << std::endl;
			std::cout << "EXIT program." << std::endl;
			break;
	}

	//advertising to the user
	std::cout << "Opening video device " << cam_id << std::endl;

    //open the video stream and make sure it's opened
    if( !camera.open(cam_id) )
	{
        std::cout << "Error opening the camera. May be invalid device id. EXIT program." << std::endl;
        return -1;
    }

    //capture loop. Out of user press a key
    while(1)
	{
		//Read image and check it. Blocking call up to a new image arrives from camera.
        if(!camera.read(image))
		{
            std::cout << "No frame" << std::endl;
            cv::waitKey();
        }

        //Basic operations with images

        //Print pixel intensity values

  //      float blue = pixel_intensity.val[0];
  //      float green = pixel_intensity.val[1];
  //      float red = pixel_intensity.val[2];
    //    std::cout << "Valors de Blue 150x150 " << blue;
    //    std::cout << "Valors de Green150x150 " << green;
  //      std::cout << "Valors de Red150x150 " << red;


        //Clone images
        imageCopy  = image.clone();
for( int y = 0; y < image.rows; y++ ) {
  for( int x = 0; x < image.cols; x++) {
      pixel_intensity = image.at<cv::Vec3b>(y, x);
    if ((pixel_intensity[1] < 190)&&(x < image.cols/2) ){
        		// manipulate the central pixel value. Set it as blue
        		pixel_intensity[0] = pixel_intensity[0] ;
            pixel_intensity[1] = pixel_intensity[1]+65;
        	  pixel_intensity[2] =pixel_intensity[2];
          }

    else if((pixel_intensity[2] < 190)&& (x >= image.cols/2) ){
        		// manipulate the central pixel value. Set it as blue
        		pixel_intensity[0] = pixel_intensity[0] ;
            pixel_intensity[1] = pixel_intensity[1];
        	  pixel_intensity[2] =pixel_intensity[2]+65;
          }
	  imageCopy.at<cv::Vec3b>(y, x) = pixel_intensity;
      }

    }


        //show image in a window
        cv::imshow("Original Output Window", image);
        cv::imshow("Output Window ", imageCopy);

		//Waits 30 millisecond to check if 'q' key has been pressed. If so, breaks the loop. Otherwise continues.
    	if( (unsigned char)(cv::waitKey(60) & 0xff) == 'q' ) break;

    }
}
