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

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return process_load; }

// TODO: Return the command that generated this process
string Process::Command() { return process_command; }

// TODO: Return this process's memory utilization
string Process::Ram() { return process_ram; }

// TODO: Return the user (name) that generated this process
string Process::User() { return process_user; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return process_uptime; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { return a.process_load < process_load; }

void Process::setPid(int pid) { process_id = pid; }

void Process::CalculateUpTime(int pid){ process_uptime = LinuxParser::UpTime(pid);}

void Process::CalculateCpuUtilization(int pid) {process_load = LinuxParser::ProcessLoad(pid);}

void Process::CalculateUser(int pid) { process_user = LinuxParser::User(pid);}

void Process::CalculateCommand(int pid) { process_command = LinuxParser::Command(pid);}

void Process::CalculateRam(int pid) { process_ram = LinuxParser::Ram(pid);}