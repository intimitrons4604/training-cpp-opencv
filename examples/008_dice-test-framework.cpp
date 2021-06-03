#include <cstdlib>
#include <iostream>

#include "TestFramework/DiceTestCaseRunner.h"

int main(const int argc, const char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Missing testCaseFile argument" << std::endl;

    return EXIT_FAILURE;
  }

  DiceTestCaseRunner runner{argv[1]};

  while (runner.hasNextImage())
  {
    const auto imagePath = runner.nextImage();

    // Run your algorithm on the image and check if it got the correct answer
  }
}
