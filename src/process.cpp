#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return process_id; }

void Process::setPid(int pid) { process_id = pid; }

void Process::CalculateCpuUtilization(int pid) {process_load = LinuxParser::ProcessLoad(pid);}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return process_load; }

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(process_id); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(process_id); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(process_id); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(process_id); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { 

    
    return true; }