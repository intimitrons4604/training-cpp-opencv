#include "TestCaseFileReader.h"

TestCaseFileReader::TestCaseFileReader(const std::filesystem::path& file) : stream{file}, base{file.parent_path()}
{
  // Intentionally empty
}

std::optional<TestCase> TestCaseFileReader::parseNextLine()
{
  std::string line;
  std::getline(stream, line);

  auto splitIndex = line.find_first_of(',');
  if (splitIndex == std::string::npos)
  {
    return std::nullopt;
  }

  const auto imagePathPart = line.substr(0, splitIndex);
  const auto dataPart = line.substr(splitIndex + 1);

  std::filesystem::path imageRelativePath{imagePathPart, std::filesystem::path::format::generic_format};
  if (!(imageRelativePath.is_relative() && imageRelativePath.has_filename()))
  {
    return std::nullopt;
  }

  const TestCase testCase{.imagePath = base / imageRelativePath, .data = dataPart};

  return testCase;
}

bool TestCaseFileReader::hasNext()
{
  if (nextTestCase)
  {
    return true;
  }

  while (stream.good() && !nextTestCase)
  {
    nextTestCase = parseNextLine();
  }

  return nextTestCase.has_value();
}

TestCase TestCaseFileReader::next()
{
  const auto testCase = nextTestCase.value();
  nextTestCase = std::nullopt;

  return testCase;
}
