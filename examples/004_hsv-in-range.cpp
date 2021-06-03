#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

int main()
{
  cv::Mat colourImage = cv::imread("resources/001/many-colours.jpg");
  cv::imshow("Colour", colourImage);

  cv::Mat hsvImage;
  cv::cvtColor(colourImage, hsvImage, cv::ColorConversionCodes::COLOR_BGR2HSV);

  const int hueMaximum = 180;
  const int saturationMaximum = 255;
  const int valueMaximum = 255;
  int hueLowerBound = 0, hueUpperBound = hueMaximum;
  int saturationLowerBound = 0, saturationUpperBound = saturationMaximum;
  int valueLowerBound = 0, valueUpperBound = valueMaximum;

  const auto inRangeWindowName = "In Range";
  cv::namedWindow(inRangeWindowName);

  cv::createTrackbar("H Lower", inRangeWindowName, &hueLowerBound, hueMaximum);
  cv::createTrackbar("H Upper", inRangeWindowName, &hueUpperBound, hueMaximum);
  cv::createTrackbar("S Lower", inRangeWindowName, &saturationLowerBound, saturationMaximum);
  cv::createTrackbar("S Upper", inRangeWindowName, &saturationUpperBound, saturationMaximum);
  cv::createTrackbar("V Lower", inRangeWindowName, &valueLowerBound, valueMaximum);
  cv::createTrackbar("V Upper", inRangeWindowName, &valueUpperBound, valueMaximum);

  do
  {
    const cv::Scalar lowerBound{(double) hueLowerBound, (double) saturationLowerBound, (double) valueLowerBound};
    const cv::Scalar upperBound{(double) hueUpperBound, (double) saturationUpperBound, (double) valueUpperBound};

    cv::Mat mask;
    cv::inRange(hsvImage, lowerBound, upperBound, mask);
    cv::cvtColor(mask, mask, cv::ColorConversionCodes::COLOR_GRAY2BGR);

    cv::Mat maskedImage;
    cv::bitwise_and(colourImage, mask, maskedImage);

    cv::imshow(inRangeWindowName, maskedImage);
  } while (cv::waitKey(500) == -1);
}
