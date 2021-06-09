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

  void printStatistics();

private:
  std::vector<int> parseData(const std::string& data);
  void printResult(const DiceTestCaseResult& result);
  void accumulateStatistics(const DiceTestCaseResult& result);

  TestCaseFileReader reader;
  std::optional<TestCase> currentTestCase = std::nullopt;
  std::optional<DiceTestCaseResult> currentResult = std::nullopt;

  int numberCorrect = 0;
  int numberIncorrect = 0;

  double minPercentAccuracy = 1;
  double maxPercentAccuracy = 0;
  double percentAccuracyAccumulator = 0;
};
