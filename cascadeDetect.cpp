/* Header files attachment */
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include <iostream>
#include <stdio.h>

/*namespace declaration*/ 
using namespace std;
using namespace cv;

/*function protyping*/
void detectAndDisplay( Mat frame );

/*cascade declaration*/
String cascade_name = "/usr/share/opencv/haarcascades/haarcascade_frontalface_default.xml";
CascadeClassifier cascade;
String window_name = "Capture - Object detection";

/*main function definition*/
int main( void )
{
     Mat frame;

    /* Loading cascade which can be generated using opencv_traincascade */
    if( !cascade.load( cascade_name ) ){ printf("--(!)Error loading the cascade\n"); return -1; };

    /* Reading the frame from video camera /dev/video0 */
    VideoCapture capture(0);
    if ( ! capture.isOpened() ) { printf("--(!)Error opening video capture\n"); return -1; }

    while ( 1 ) /*infinite loop*/
    {
        /*getting the frame*/
        capture.read(frame);

        if( frame.empty() )
        {
            printf(" --(!) No frame  captured-- Break!");
            break;
        }

        /* Calling the function detectAndDisplay() */
        detectAndDisplay( frame );

        /* exiting the program on spacebar */
        int c = waitKey(10);
        if( (char)c == 27 ) { break; }
    }
    return 0;
}



void detectAndDisplay( Mat frame )
{   /* vector containing details of objects */
    std::vector<Rect> objects;
    Mat frame_gray; /* grayscale image */
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    /* detection of objects using cascade file */
    // Adjust parameters accordingly //
    cascade.detectMultiScale( frame_gray, objects, 1.1, 2, 0, Size(80, 80) );

    /* loop over all the detected objects */ 
    for( size_t i = 0; i < objects.size(); i++ )
    {
            /* drawing the objects on image */
            Point center( objects[i].x + objects[i].width/2, objects[i].y + objects[i].height/2 );
            cv::rectangle(frame, Point(center.x-objects[i].width/2,center.y-objects[i].height/2),Point(center.x+objects[i].width/2,center.y+objects[i].height/2), cv::Scalar(255,0,255), 2);

    }
    /* showing the final image */
    imshow( window_name, frame );
 
    /*exit on any keypress */
    if(waitKey(30)>0)
        exit(0);
}

