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

  const auto dilatedWindowName = "Dilated";
  cv::namedWindow(dilatedWindowName);

  int xSize = 0;
  int ySize = 0;
  cv::createTrackbar("X Size", dilatedWindowName, &xSize, 100);
  cv::createTrackbar("Y Size", dilatedWindowName, &ySize, 100);

  while (cv::waitKey(500) == -1)
  {
    cv::Mat dilatedImage = grayscaleImage.clone();

    if (xSize != 0 && ySize != 0)
    {
      cv::dilate(dilatedImage, dilatedImage, cv::getStructuringElement(cv::MorphShapes::MORPH_RECT, {xSize, ySize}));
    }

    cv::imshow(dilatedWindowName, dilatedImage);
  }
}
