#include "DiceTestCaseRunner.h"

#include <sstream>

DiceTestCaseRunner::DiceTestCaseRunner(const std::filesystem::path& testCaseFile) : reader{testCaseFile}
{
  // Intentionally empty
}

bool DiceTestCaseRunner::hasNextImage()
{
  return reader.hasNext();
}

std::filesystem::path DiceTestCaseRunner::nextImage()
{
  currentTestCase = reader.next();

  return currentTestCase.value().imagePath;
}

DiceTestCaseResult DiceTestCaseRunner::submitAnswer(const std::vector<int>& answer)
{
  const auto testCase = currentTestCase.value();
  const auto expected = parseData(testCase.data);

  return {testCase.imagePath, expected, answer};
}

std::vector<int> DiceTestCaseRunner::parseData(const std::string& data)
{
  std::stringstream stream{data};
  std::vector<int> values;

  while (stream.good())
  {
    int value;
    stream >> value;

    if (value >= 1 && value <= 6)
    {
      values.push_back(value);
    }
  }

  return values;
}
