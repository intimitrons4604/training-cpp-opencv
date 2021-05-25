#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

int main()
{
  cv::Mat colourImage = cv::imread("resources/001/many-colours.jpg");
  cv::imshow("Colour", colourImage);

  const auto thresholdedWindowName = "Thresholded";
  cv::namedWindow(thresholdedWindowName);

  int threshold = 0;
  cv::createTrackbar("Threshold", thresholdedWindowName, &threshold, 255);

  while (cv::waitKey(500) == -1)
  {
    cv::Mat thresholdedImage;
    cv::cvtColor(colourImage, thresholdedImage, cv::ColorConversionCodes::COLOR_BGR2GRAY);

    cv::threshold(thresholdedImage, thresholdedImage, threshold, 255, cv::ThresholdTypes::THRESH_BINARY);

    cv::imshow(thresholdedWindowName, thresholdedImage);
  }
}
