#pragma once

#include <filesystem>
#include <string>
#include <vector>

class DiceTestCaseResult
{
public:
  DiceTestCaseResult(
    const std::filesystem::path& imagePath, const std::vector<int>& expected, const std::vector<int>& actual);

  const std::filesystem::path& getImagePath() const;
  const std::vector<int>& getExpected() const;
  const std::vector<int>& getActual() const;

  bool isCorrect() const;
  double percentAccuracy() const;

private:
  std::filesystem::path imagePath;
  std::vector<int> expected;
  std::vector<int> actual;
};
