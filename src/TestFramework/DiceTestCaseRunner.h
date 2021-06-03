#pragma once

#include <filesystem>
#include <vector>

#include "TestCaseRunner.h"

class DiceTestCaseRunner : public TestCaseRunner<std::vector<int>>
{
public:
  DiceTestCaseRunner(const std::filesystem::path& testCaseFile);

protected:
  std::vector<int> parseData(const std::string& data) override;
  bool checkAnswer(const std::vector<int>& expected, const std::vector<int>& actual) override;
};
