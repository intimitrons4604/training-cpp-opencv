#include "DiceTestCaseResult.h"

#include <algorithm>

DiceTestCaseResult::DiceTestCaseResult(
  const std::filesystem::path& imagePath, const std::vector<int>& expected, const std::vector<int>& actual)
    : imagePath{imagePath}, expected{expected}, actual{actual}
{
  std::sort(this->expected.begin(), this->expected.end());
  std::sort(this->actual.begin(), this->actual.end());
}

const std::filesystem::path& DiceTestCaseResult::getImagePath() const
{
  return imagePath;
}

const std::vector<int>& DiceTestCaseResult::getExpected() const
{
  return expected;
}

const std::vector<int>& DiceTestCaseResult::getActual() const
{
  return actual;
}

bool DiceTestCaseResult::isCorrect() const
{
  return expected == actual;
}

double DiceTestCaseResult::percentAccuracy() const
{
  if (isCorrect())
  {
    return 1;
  }

  int numberOfDiceCorrect = 0;

  auto expectedIt = expected.cbegin();
  auto actualIt = actual.cbegin();
  while (expectedIt != expected.cend() && actualIt != actual.cend())
  {
    if (*expectedIt == *actualIt)
    {
      numberOfDiceCorrect++;
      expectedIt++;
      actualIt++;
    }
    else if (*expectedIt < *actualIt)
    {
      while (*expectedIt < *actualIt && expectedIt != expected.cend())
      {
        expectedIt++;
      }
    }
    else
    {
      while (*expectedIt > *actualIt && actualIt != actual.cend())
      {
        actualIt++;
      }
    }
  }

  return (double) numberOfDiceCorrect / std::max(expected.size(), actual.size());
}
