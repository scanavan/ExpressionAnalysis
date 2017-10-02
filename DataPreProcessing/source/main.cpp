#include <opencv2/opencv.hpp>

int main()
{
	//load color image from file
	cv::Mat image = cv::imread("images/000.jpg", cv::IMREAD_COLOR);
	//image file can't be loaded
	if (image.empty())
	{
		std::cout << "Failed to load image." << std::endl;
	}

	//create window to show image on
	cv::namedWindow("Test", cv::WINDOW_AUTOSIZE);
	//show image
	cv::imshow("Test", image);
	//wait for user input so window doesn't close
	cv::waitKey(0);

	return EXIT_SUCCESS;
}