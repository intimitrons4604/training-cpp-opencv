#include <vector>

#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

int main()
{
  cv::Mat image = cv::imread("resources/002/nested.png");

  cv::Mat grayscaleImage;
  cv::cvtColor(image, grayscaleImage, cv::ColorConversionCodes::COLOR_BGR2GRAY);

  std::vector<std::vector<cv::Point>> contours;
  cv::findContours(
    grayscaleImage, contours, cv::RetrievalModes::RETR_LIST, cv::ContourApproximationModes::CHAIN_APPROX_SIMPLE);

  cv::drawContours(image, contours, -1, {0, 0, 255}, 2);
  cv::imshow("Contours", image);

  cv::waitKey();
}
