#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    
    processes_.clear();
    vector<int> pids = LinuxParser::Pids();
    for(int pid : pids){
        Process process;
        process.setPid(pid);
        process.CalculateUser(pid);
        process.CalculateCommand(pid);
        process.CalculateRam(pid);
        process.CalculateCpuUtilization(pid);   
        process.CalculateUpTime(pid);

        processes_.emplace_back(process);
        sort(processes_.begin(), processes_.end());        
    }    
    return processes_;
}

// TODO [COMPLETE]: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO [COMPLETE]: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization();}

// TODO [COMPLETE]: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO [COMPLETE]: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO [COMPLETE]: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO [COMPLETE]: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }