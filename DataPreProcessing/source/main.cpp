#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <windows.h>
#include <string>

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

void detectAndDisplay(Mat frame, int x, int y, string firstFloderName, string secondFolderName, string imgName);

string face_cascade_name = "C:/Users/asthasharma017/Development/FacialExpressionRecognitionProjectWorkspace/ThirdParty/opencv/sources/samples/winrt_universal/VideoCaptureXAML/video_capture_xaml/video_capture_xaml.Windows/Assets/haarcascade_frontalface_alt.xml";
CascadeClassifier face_cascade;
string window_name = "Capture - Face detection";
string sBasePath = "E:\\MMSE\\first 10 subjects 2D\\";
string sCroppedImagePath = "E:\\MMSE\\cropped\\";
int filenumber;
string filename;

int main(void)
{
	if (!face_cascade.load(face_cascade_name)) {
		printf("--(!)Error loading\n");
		return (-1);
	}
	WIN32_FIND_DATA findFileDataFirst;
	HANDLE hFindFirst;
	string sPathFirst;
	vector<string> MyVectFirst;
	sPathFirst.assign(sBasePath + "*");
	hFindFirst = FindFirstFile(sPathFirst.data(), &findFileDataFirst);
	do
	{
		if (findFileDataFirst.dwFileAttributes == 16)
		{
			MyVectFirst.push_back(findFileDataFirst.cFileName);
		}
	} while (FindNextFile(hFindFirst, &findFileDataFirst));
	FindClose(hFindFirst);
	for (int i = 0; i < MyVectFirst.size(); i++) {
		if (MyVectFirst.at(i) == "." || MyVectFirst.at(i) == "..") {
			continue;
		}
		std::string sPathSecond(sBasePath + MyVectFirst.at(i));
		sPathSecond.append("\\*");
		WIN32_FIND_DATA findFileDataSecond;
		HANDLE hFindSecond;
		vector<string> MyVectSecond;
		hFindSecond = FindFirstFile(sPathSecond.data(), &findFileDataSecond);
		do
		{
			if (findFileDataSecond.dwFileAttributes == 16)
			{
				MyVectSecond.push_back(findFileDataSecond.cFileName);
			}
		} while (FindNextFile(hFindSecond, &findFileDataSecond));
		FindClose(hFindSecond);
		for (int j = 0; j < MyVectSecond.size(); j++) {
			if (MyVectSecond.at(i) == "." || MyVectSecond.at(i) == "..") {
				continue;
			}
			std::string sPathImage(sBasePath + MyVectFirst.at(i) + "\\" + MyVectSecond.at(j));
			sPathImage.append("\\*");
			WIN32_FIND_DATA imageData;
			HANDLE hFindImage;
			if ((hFindImage = FindFirstFile(sPathImage.c_str(), &imageData)) != INVALID_HANDLE_VALUE) {
				do {
					Mat frame = imread(sBasePath + MyVectFirst.at(i) + "\\" + MyVectSecond.at(j) + "\\" + imageData.cFileName);
					cout << sBasePath + MyVectFirst.at(i) + "\\" + MyVectSecond.at(j) + "\\" + imageData.cFileName << endl;
					if (!frame.empty()) {
						detectAndDisplay(frame, 48, 48, MyVectFirst.at(i), MyVectSecond.at(j), imageData.cFileName);
					}
					else {
						cout << " --(!) No captured frame -- Break!" << endl;
					}
					int c = waitKey(10);
					if (27 == char(c)) {
						//break;
					}
				} while (FindNextFile(hFindImage, &imageData) != 0);
				FindClose(hFindImage);
			}
		}
	}
	return 0;
}

void detectAndDisplay(Mat frame, int x, int y, string firstFolderName, string secondFolderName, string imgName)
{
	std::vector<Rect> faces;
	Mat frame_gray;
	Mat crop;
	Mat res;
	Mat gray;
	string text;
	stringstream sstm;

	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(48, 48));

	// Set Region of Interest
	cv::Rect roi_b;
	cv::Rect roi_c;

	size_t ic = 0; // ic is index of current element
	int ac = 0; // ac is area of current element

	size_t ib = 0; // ib is index of biggest element
	int ab = 0; // ab is area of biggest element

	for (ic = 0; ic < faces.size(); ic++) // Iterate through all current elements (detected faces)

	{
		roi_c.x = faces[ic].x;
		roi_c.y = faces[ic].y;
		roi_c.width = (faces[ic].width);
		roi_c.height = (faces[ic].height);

		ac = roi_c.width * roi_c.height; // Get the area of current element (detected face)

		roi_b.x = faces[ib].x;
		roi_b.y = faces[ib].y;
		roi_b.width = (faces[ib].width);
		roi_b.height = (faces[ib].height);

		ab = roi_b.width * roi_b.height; // Get the area of biggest element, at beginning it is same as "current" element

		if (ac > ab)
		{
			ib = ic;
			roi_b.x = faces[ib].x;
			roi_b.y = faces[ib].y;
			roi_b.width = (faces[ib].width);
			roi_b.height = (faces[ib].height);
		}

		crop = frame(roi_b);
		resize(crop, res, Size(128, 128), 0, 0, INTER_LINEAR);
		cvtColor(crop, gray, CV_BGR2GRAY); // Convert cropped image to Grayscale

		filename = "";
		stringstream ssfn;
		ssfn << filenumber << ".jpg";
		filename = ssfn.str();
		filenumber++;

		Point pt1(faces[ic].x, faces[ic].y); // Display detected faces on main window
		Point pt2((faces[ic].x + faces[ic].height), (faces[ic].y + faces[ic].width));
		rectangle(frame, pt1, pt2, Scalar(0, 255, 0), 2, 8, 0);
	}

	// Show image
	sstm << "Crop area size: " << roi_b.width << "x" << roi_b.height << " Filename: " << filename;
	text = sstm.str();

	putText(frame, text, cvPoint(30, 30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 255), 1, CV_AA);

	if (!crop.empty())
	{
		resize(crop, crop, Size(x, y));
		imwrite(sCroppedImagePath + firstFolderName + "_" + secondFolderName + "_" + imgName + ".jpg", crop);
		cv::waitKey();
	}
	else
		destroyWindow("detected");
}