#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include "linux_parser.h"
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid() const;                               // Done: See src/process.cpp
  std::string User() const;                      // Done: See src/process.cpp
  std::string Command() const;                   // Done: See src/process.cpp
  float CpuUtilization() const;                  // Done: See src/process.cpp
  std::string Ram() const;                       // Done: See src/process.cpp
  long int UpTime() const;                       // Done: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  explicit Process(int pid):pid_(pid){};
  // Done: Declare any necessary private members
 private:
    int pid_;
};

#endif