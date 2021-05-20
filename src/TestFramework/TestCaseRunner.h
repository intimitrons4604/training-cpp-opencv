#pragma once

#include <filesystem>
#include <optional>
#include <string>

#include "TestCaseFileReader.h"

template<typename Answer>
class TestCaseRunner
{
public:
  bool hasNextImage();
  std::filesystem::path nextImage();

  Answer answer();
  bool isCorrect(const Answer answer);

protected:
  TestCaseRunner(const std::filesystem::path& testCaseFile);

  virtual Answer parseData(const std::string& data) = 0;
  virtual bool checkAnswer(const Answer& expected, const Answer& actual) = 0;

private:
  TestCaseFileReader reader;
  std::optional<Answer> currentAnswer = std::nullopt;
};

template<typename Answer>
TestCaseRunner<Answer>::TestCaseRunner(const std::filesystem::path& testCaseFile) : reader{testCaseFile}
{
  // Intentionally empty
}

template<typename Answer>
bool TestCaseRunner<Answer>::hasNextImage()
{
  return reader.hasNext();
}

template<typename Answer>
std::filesystem::path TestCaseRunner<Answer>::nextImage()
{
  const auto testCase = reader.next();

  currentAnswer = parseData(testCase.data);

  return testCase.imagePath;
}

template<typename Answer>
Answer TestCaseRunner<Answer>::answer()
{
  return currentAnswer.value();
}

template<typename Answer>
bool TestCaseRunner<Answer>::isCorrect(const Answer answer)
{
  return checkAnswer(currentAnswer.value(), answer);
}
