#include "benchmark/benchmark.h"
#include "parse_csv.hpp"

static void BM_GetLineCSV(benchmark::State &state) 
{
  std::string file_contents;
  for (auto _ : state)
  {
    const std::string path = "C:\\Users\\uchid\\OneDrive\\Desktop\\projects\\jmim\\test\\data\\AAPL.csv";
    file_contents = GetLineCSV(path);
  }
}

static void BM_StreamCSV(benchmark::State &state)
{
  std::string file_contents;
  for (auto _: state)
  {
    const std::string path = "C:\\Users\\uchid\\OneDrive\\Desktop\\projects\\jmim\\test\\data\\AAPL.csv";
    file_contents = StreamCSV(path); 
  }
}

BENCHMARK(BM_GetLineCSV); 
BENCHMARK(BM_StreamCSV);
