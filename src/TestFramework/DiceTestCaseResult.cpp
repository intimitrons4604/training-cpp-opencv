#include "DiceTestCaseResult.h"

#include <algorithm>

DiceTestCaseResult::DiceTestCaseResult(
  const std::filesystem::path& imagePath, const std::vector<int>& expected, const std::vector<int>& actual)
    : imagePath{imagePath}, expected{expected}, actual{actual}
{
  // Intentionally empty
}

bool DiceTestCaseResult::isCorrect()
{
  std::sort(expected.begin(), expected.end());
  std::sort(actual.begin(), actual.end());

  return expected == actual;
}
