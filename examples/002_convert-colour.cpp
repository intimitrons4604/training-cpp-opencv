#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

int main()
{
  cv::Mat colourImage = cv::imread("resources/001/many-colours.jpg");

  cv::Mat grayscaleImage;
  cv::cvtColor(colourImage, grayscaleImage, cv::ColorConversionCodes::COLOR_BGR2GRAY);

  cv::imshow("Colour", colourImage);
  cv::imshow("Grayscale", grayscaleImage);

  cv::waitKey();
}
