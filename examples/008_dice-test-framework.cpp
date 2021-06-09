#include <cstdlib>
#include <iostream>

#include "TestFramework/DiceTestCaseRunner.h"

// Run your program with a test case file argument, for example:
// ./main ./resources/003/TestCases.txt
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

    // Run your algorithm on the image and submit an answer
    // The result will be printed and you may use the result returned by submitAnswer() if desired

    runner.submitAnswer({});
  }

  runner.printStatistics();
}
