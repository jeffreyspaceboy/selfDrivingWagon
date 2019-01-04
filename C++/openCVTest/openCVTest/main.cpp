//
//  main.cpp
//  openCVTest
//
//  Created by Jeffrey Fisher on 12/29/18.
//  Copyright © 2018 Jeffrey Fisher. All rights reserved.
//

#include<opencv/cvaux.h>                            //
#include<opencv/highgui.h>                            //
#include<opencv2/core/core.hpp>                        //
#include<opencv/cxcore.h>                            // OpenCV includes, links to the libraries
#include<opencv2/highgui/highgui.hpp>                //
#include<stdio.h>                                    //
#include "opencv2/opencv.hpp"                        //
#include<stdlib.h>                                    //
#include<iostream>

#include <unistd.h>

using namespace std;
using namespace cv;

/*
 Mat Original;        //Declare Matrix, Original (ie. camera feed)
 cap >> Original;
 namedWindow("Original", 1);        //declare window
 Mat maskRegion;
 
 Mat gBlur;
 GaussianBlur(Original, gBlur, Size(5, 5), 2);
 Mat hsv;
 cvtColor(gBlur, hsv, CV_BGR2HSV);
 Point vertices[1][8];
 vertices[0][0] = Point (0,0);
 vertices[0][1] = Point (1300,0);
 vertices[0][2] = Point (1300,720);
 vertices[0][3] = Point (1200,720);
 vertices[0][4] = Point (700,500);
 vertices[0][5] = Point (500,500);
 vertices[0][6] = Point (0,720);
 vertices[0][7] = Point (0,720);
 const Point* ppt[1] = {vertices[0]};
 int npt[] = {8};
 fillPoly(hsv,ppt,npt,1,Scalar(0,0,0),8);
 


Mat maskW;
int lowW[] = {0,0,150};
int highW[] = {255,255,255};
inRange(hsv, Scalar(lowW[0],lowW[1],lowW[2]), Scalar(highW[0],highW[1],highW[2]), maskW);
Mat maskY;
int lowY[] = {18,94,140};
int highY[] = {48,255,255};
inRange(hsv, Scalar(lowY[0],lowY[1],lowY[2]), Scalar(highY[0],highY[1],highY[2]), maskY);
Mat edgesY;
Mat edgesW;
Canny(maskY, edgesY, 75, 150);
Canny(maskW, edgesW, 50, 100);
vector<Vec4i> linesY;
vector<Vec4i> linesW;
HoughLinesP(edgesY, linesY, 1, (CV_PI/180), 50, 10, 50);
HoughLinesP(edgesW, linesW, 1, (CV_PI/180), 50, 1, 200);
for(size_t i = 0; i < linesY.size(); i++ )
{
    line(Original, Point(linesY[i][0], linesY[i][1]),
         Point(linesY[i][2], linesY[i][3]), Scalar(0,255,0), 3);
}
for(size_t i = 0; i < linesW.size(); i++ )
{
    line(Original, Point(linesW[i][0], linesW[i][1]),
         Point(linesW[i][2], linesW[i][3]), Scalar(0,0,255), 3);
}
imshow("Original", Original);
sleep(0.5);
if (waitKey(27) >= 1) break;
 */

int main(int argc, char** argv) {
    // VideoCapture cap("road_car_view.mp4");
    VideoCapture cap(argv[1]);        //VideoCapture is OpenCV function that uses webcam stream - cap(0) <-- zero being the first camera, 1 being 2nd camera if multiple
    if (!cap.isOpened())        //if not cap opened
    {
        cout << "Cannot Open Video Camera" << endl;        //disp error message
        cin.ignore();        //wait until key hit
        return -1;            //close program, return -1
    }
    
    for (;;)                //for loop, keeps the program running until the esc key break (at the end)
    {
        Mat Original;        //Declare Matrix, Original (ie. camera feed)
        cap >> Original;
        namedWindow("Original", 1);        //declare window
        Mat maskRegion;
        
        Mat gBlur;
        GaussianBlur(Original, gBlur, Size(5, 5), 1);
        Mat hsv;
        cvtColor(gBlur, hsv, CV_BGR2HSV);
        
        Point vertices[1][8];
        vertices[0][0] = Point (0,0);
        vertices[0][1] = Point (960,0);
        vertices[0][2] = Point (960,540);
        vertices[0][3] = Point (900,540);
        vertices[0][4] = Point (550,300);
        vertices[0][5] = Point (450,300);
        vertices[0][6] = Point (100,540);
        vertices[0][7] = Point (0,540);
        const Point* ppt[1] = {vertices[0]};
        int npt[] = {8};
        fillPoly(hsv,ppt,npt,1,Scalar(0,0,0),8);
        
        Mat maskW;
        int lowW[] = {0,0,200};
        int highW[] = {255,255,255};
        inRange(hsv, Scalar(lowW[0],lowW[1],lowW[2]), Scalar(highW[0],highW[1],highW[2]), maskW);
        
        Mat edgesW;
        Canny(maskW, edgesW, 50, 100);
        vector<Vec4i> linesW;
        HoughLinesP(edgesW, linesW, 1, (CV_PI/180), 60, 100, 250);
        for(size_t i = 0; i < linesW.size(); i++ )
        {
            line(Original, Point(linesW[i][0], linesW[i][1]),
                 Point(linesW[i][2], linesW[i][3]), Scalar(0,255,0), 3);
        }
        imshow("Original", Original);
        sleep(0.25);
        if (waitKey(27) >= 1) break;
    }
}

/*
 // VideoCapture cap("road_car_view.mp4");
 VideoCapture cap(argv[1]);        //VideoCapture is OpenCV function that uses webcam stream - cap(0) <-- zero being the first camera, 1 being 2nd camera if multiple
 if (!cap.isOpened())        //if not cap opened
 {
 cout << "Cannot Open Video Camera" << endl;        //disp error message
 cin.ignore();        //wait until key hit
 return -1;            //close program, return -1
 }
 
 for (;;)                //for loop, keeps the program running until the esc key break (at the end)
 {
 Mat Original;        //Declare Matrix, Original (ie. camera feed)
 cap >> Original;
 namedWindow("Original", 1);        //declare window
 Mat hsv;
 cvtColor(Original, hsv, CV_BGR2HSV);
Mat gBlur;
GaussianBlur(hsv, gBlur, Size(231, 231), 25);
Mat edges;
Canny(gBlur, edges, 13, 13);

vector<Vec4i> lines;
HoughLinesP(edges, lines, 1, (CV_PI/180), 300, 250, 300);
for(size_t i = 0; i < 2; i++ )//lines.size()
{
    line(Original, Point(lines[i][0], lines[i][1]),
         Point(lines[i][2], lines[i][3]), Scalar(0,255,0), 5);
}
sleep(0.5);
imshow("Original", Original);
if (waitKey(27) >= 1) break;
}
*/
