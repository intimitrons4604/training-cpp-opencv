#pragma once

#include <filesystem>
#include <optional>
#include <vector>

#include "DiceTestCaseResult.h"
#include "TestCaseFileReader.h"

class DiceTestCaseRunner
{
public:
  DiceTestCaseRunner(const std::filesystem::path& testCaseFile);

  bool hasNextImage();
  std::filesystem::path nextImage();
  DiceTestCaseResult submitAnswer(const std::vector<int>& answer);

private:
  std::vector<int> parseData(const std::string& data);

  TestCaseFileReader reader;
  std::optional<TestCase> currentTestCase = std::nullopt;
};
