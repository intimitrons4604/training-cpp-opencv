#pragma once

#include <filesystem>
#include <fstream>
#include <optional>
#include <string>

struct TestCase
{
  std::filesystem::path imagePath;
  std::string data;
};

class TestCaseFileReader
{
public:
  TestCaseFileReader(const std::filesystem::path& file);

  bool hasNext();
  TestCase next();

private:
  std::optional<TestCase> parseNextLine();

  std::ifstream stream;
  const std::filesystem::path base;
  std::optional<TestCase> nextTestCase = std::nullopt;
};
