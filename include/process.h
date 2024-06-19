#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // TODO: See src/process.cpp                       
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp  
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  void setPid(int pid);
  
  void CalculateUser(int pid);
  void CalculateCommand(int pid);
  void CalculateRam(int pid);

  void CalculateCpuUtilization(int pid);
  void CalculateUpTime(int pid);


  // TODO: Declare any necessary private members
 private:
 int process_id;
 std::string process_user;
 std::string process_command; 
 float process_load;
 std::string process_ram;
 long process_uptime;
};

#endif