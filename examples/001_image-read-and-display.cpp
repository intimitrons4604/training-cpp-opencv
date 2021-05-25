#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

int main()
{
  cv::Mat image = cv::imread("resources/001/many-colours.jpg");

  cv::imshow("Window", image);
  cv::waitKey();
}
