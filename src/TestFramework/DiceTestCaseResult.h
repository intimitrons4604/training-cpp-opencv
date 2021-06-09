#pragma once

#include <filesystem>
#include <vector>

class DiceTestCaseResult
{
public:
  DiceTestCaseResult(
    const std::filesystem::path& imagePath, const std::vector<int>& expected, const std::vector<int>& actual);

  bool isCorrect();

private:
  std::filesystem::path imagePath;
  std::vector<int> expected;
  std::vector<int> actual;
};
