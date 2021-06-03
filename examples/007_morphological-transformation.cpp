#include <vector>

#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

int main()
{
  cv::Mat image = cv::imread("resources/002/blobs.png");
  cv::imshow("Original", image);

  cv::Mat grayscaleImage;
  cv::cvtColor(image, grayscaleImage, cv::ColorConversionCodes::COLOR_BGR2GRAY);

  const auto transformedWindowName = "Transformed";
  cv::namedWindow(transformedWindowName);

  int xSize = 0;
  int ySize = 0;
  cv::createTrackbar("X Size", transformedWindowName, &xSize, 100);
  cv::createTrackbar("Y Size", transformedWindowName, &ySize, 100);

  do
  {
    cv::Mat transformedImage = grayscaleImage.clone();

    if (xSize != 0 && ySize != 0)
    {
      cv::morphologyEx(transformedImage, transformedImage, cv::MorphTypes::MORPH_ERODE,
        cv::getStructuringElement(cv::MorphShapes::MORPH_RECT, {xSize, ySize}));
    }

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(
      transformedImage, contours, cv::RetrievalModes::RETR_LIST, cv::ContourApproximationModes::CHAIN_APPROX_SIMPLE);

    cv::cvtColor(transformedImage, transformedImage, cv::ColorConversionCodes::COLOR_GRAY2BGR);
    cv::drawContours(transformedImage, contours, -1, {0, 0, 255}, 2);

    cv::imshow(transformedWindowName, transformedImage);
  } while (cv::waitKey(500) == -1);
}
