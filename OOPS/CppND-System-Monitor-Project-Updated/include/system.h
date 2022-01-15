#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"

class System {
 public:
  virtual Processor& Cpu();                   // Done: See src/system.cpp
  virtual std::vector<Process>& Processes();  // Done: See src/system.cpp
  static float MemoryUtilization();          // Done: See src/system.cpp
  static long UpTime();                      // Done: See src/system.cpp
  static int TotalProcesses();               // Done: See src/system.cpp
  static int RunningProcesses();             // Done: See src/system.cpp
  static std::string Kernel();               // Done: See src/system.cpp
  static std::string OperatingSystem();      // Done: See src/system.cpp

  // Done: Define any necessary private members
 private:
  Processor cpu_ = {};
  std::vector<Process> processes_ = {};
};

#endif