#include "DiceTestCaseRunner.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
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
  currentResult = std::nullopt;

  return currentTestCase.value().imagePath;
}

DiceTestCaseResult DiceTestCaseRunner::submitAnswer(const std::vector<int>& answer)
{
  if (currentResult)
  {
    return currentResult.value();
  }

  const auto testCase = currentTestCase.value();
  const auto expected = parseData(testCase.data);

  const DiceTestCaseResult result{testCase.imagePath, expected, answer};
  printResult(result);
  accumulateStatistics(result);

  currentResult = result;

  return result;
}

void DiceTestCaseRunner::printStatistics()
{
  const auto totalCases = numberCorrect + numberIncorrect;
  if (totalCases == 0)
  {
    std::cout << "No test results available\n";
    return;
  }

  std::ostringstream stream;
  stream << std::fixed << std::setprecision(2);

  stream << "Executed " << totalCases << " test cases\n";
  stream << numberCorrect << " correct, " << numberIncorrect << " incorrect - "
         << (double) numberCorrect * 100 / totalCases << "% correct\n";
  stream << "Accuracy (Minimum, Maximum, Mean): " << minPercentAccuracy * 100 << "%, " << maxPercentAccuracy * 100
         << "%, " << percentAccuracyAccumulator * 100 / totalCases << "%\n";

  std::cout << stream.str();
}

std::vector<int> DiceTestCaseRunner::parseData(const std::string& data)
{
  std::istringstream stream{data};
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

void DiceTestCaseRunner::printResult(const DiceTestCaseResult& result)
{
  std::ostringstream stream;
  stream << std::fixed << std::setprecision(2);

  stream << result.getImagePath().generic_string() << '\n';
  if (result.isCorrect())
  {
    stream << "Correct\n";
  }
  else
  {
    const auto expected = result.getExpected();
    const auto actual = result.getActual();

    stream << "Incorrect - " << result.percentAccuracy() * 100 << "% accuracy\n";

    stream << "Expected: { ";
    std::copy(expected.cbegin(), expected.cend(), std::ostream_iterator<int>{stream, " "});
    stream << "}\n";

    stream << "Actual:   { ";
    std::copy(actual.cbegin(), actual.cend(), std::ostream_iterator<int>{stream, " "});
    stream << "}\n";
  }

  stream << '\n';

  std::cout << stream.str();
}

void DiceTestCaseRunner::accumulateStatistics(const DiceTestCaseResult& result)
{
  double accuracy;

  if (result.isCorrect())
  {
    accuracy = 1;
    numberCorrect++;
  }
  else
  {
    accuracy = result.percentAccuracy();
    numberIncorrect++;
  }

  minPercentAccuracy = std::min(minPercentAccuracy, accuracy);
  maxPercentAccuracy = std::max(maxPercentAccuracy, accuracy);
  percentAccuracyAccumulator += accuracy;
}
