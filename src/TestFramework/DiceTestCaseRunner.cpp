#include "DiceTestCaseRunner.h"

#include <algorithm>
#include <sstream>

DiceTestCaseRunner::DiceTestCaseRunner(const std::filesystem::path& testCaseFile) : TestCaseRunner{testCaseFile}
{
  // Intentionally empty
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

  std::sort(values.begin(), values.end());

  return values;
}

bool DiceTestCaseRunner::checkAnswer(const std::vector<int>& expected, const std::vector<int>& actual)
{
  if (expected.size() != actual.size())
  {
    return false;
  }

  auto actualSorted = actual;
  std::sort(actualSorted.begin(), actualSorted.end());

  return expected == actualSorted;
}
