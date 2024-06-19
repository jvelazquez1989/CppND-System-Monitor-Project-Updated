#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "format.h"
#include "math.h"

#include <iostream>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO [COMPLETE]: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string line;
  string key;
  float value;
  float MemTotal;
  float MemFree;
  std::ifstream input_file(kProcDirectory + kMeminfoFilename);
  
  if (input_file.is_open()) {
    for(int i = 0; i < 2; i++){
      std::getline(input_file, line);    
      std::istringstream linestream(line);
      linestream >> key >> value;

      if(key == "MemTotal:"){MemTotal = value;}
      if(key == "MemFree:"){MemFree = value;}

      //std::cout << "line = " << line << "\n"; //debugging    
    }   
  }
  //std::cout << "MemTotal = " << MemTotal << "\n"; //debugging 
  //std::cout << "MemFree = " << MemFree << "\n"; //debugging 
  
  //calculate total memory utilization
  return (MemTotal - MemFree)/MemTotal;
  }

// TODO [COMPLETE]: Read and return the system uptime
long LinuxParser::UpTime() { 
  string line;
  long total_uptime;
  long idle_uptime;
  std::ifstream input_file(kProcDirectory + kUptimeFilename);

  if (input_file.is_open()) {
    std::getline(input_file, line);    
    std::istringstream linestream(line);
    linestream >> total_uptime >> idle_uptime;
  }
  
  //std::cout << "line = " << line << "\n"; //debugging 
  //std::cout << "total_uptime = " << total_uptime << "\n"; //debugging 
  //std::cout << "idle_uptime = " << idle_uptime << "\n"; //debugging 
  
  return total_uptime; 
  }

// TODO [COMPLETE]: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  long uptime;
  long ticks;

  uptime = UpTime();
  ticks = (sysconf(_SC_CLK_TCK));

  /*std::cout << "uptime = " << uptime << "\n"; //debugging
  std::cout << "ticks = " << ticks << "\n"; //debugging
  std::cout << "Jiffies = " << uptime*ticks << "\n"; //debugging*/
  return uptime*ticks;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) {  
  
  // NOT USED

  return 0;
}

// TODO [COMPLETE]: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  string line;
  string key;
  long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
  std::ifstream input_file(kProcDirectory + kStatFilename);

  if (input_file.is_open()){
    std::getline(input_file, line);
    std::istringstream linestream(line);
    linestream >> key >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;

    //std::cout << "line = " << line << "\n"; //debugging
  }

  return user + nice + system + idle + iowait + irq + softirq + steal + guest + guest_nice;
}

// TODO [COMPLETE]: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  string line;
  string key;
  long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
  std::ifstream input_file(kProcDirectory + kStatFilename);

  if (input_file.is_open()){
    std::getline(input_file, line);
    std::istringstream linestream(line);
    linestream >> key >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;

    //std::cout << "line = " << line << "\n"; //debugging
  }

  return idle + iowait;
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  
  //NOT USED
  
  return {};
}

// TODO [COMPLETE]: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string line;
  string key;
  int value;
  int total_processes = 999;
  std::ifstream input_file(kProcDirectory + kStatFilename);

  if (input_file.is_open()) {
    while (std::getline(input_file, line)){         
      std::istringstream linestream(line);
      linestream >> key >> value;     

      if(key == "processes"){
        /*std::cout << line << "\n"; //debugging
        std::cout << "key = " << key << "\n"; //debugging
        std::cout << "value = " << value << "\n"; //debugging */
        total_processes = value;        
      }
    }
  }  
  return total_processes;
}

// TODO [COMPLETE]: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string line;
  string key;
  int value;
  int running_processes = 999;
  std::ifstream input_file(kProcDirectory + kStatFilename);

  if (input_file.is_open()) {
    while (std::getline(input_file, line)){         
      std::istringstream linestream(line);
      linestream >> key >> value;     

      if(key == "procs_running"){
        //std::cout << line << "\n"; //debugging
        //std::cout << "key = " << key << "\n"; //debugging
        //std::cout << "value = " << value << "\n"; //debugging
        running_processes = value;        
      }
    }
  }  
  return running_processes;  
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string line;    
  std::ifstream input_file(kProcDirectory + std::to_string(pid) + kCmdlineFilename);

  if (input_file.is_open()) {
    std::getline(input_file, line);
  }
  input_file.close();

  return line;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string line;
  string key;
  float value;
  string ram;
  std::ifstream input_file(kProcDirectory + std::to_string(pid) + kStatusFilename);

  if (input_file.is_open()) {
    while (std::getline(input_file, line)){
      std::istringstream linestream(line);
      linestream >> key >> value;     

      if(key == "VmSize:"){
        /*std::cout << line << "\n"; //debugging
        std::cout << "key = " << key << "\n"; //debugging
        std::cout << "value = " << value << "\n"; //debugging*/
        //ram = std::to_string(value/1000);
        ram = std::to_string(value/1000);
      }  
    }
  } 
  return ram;
}


// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string line;
  string key;
  string value;
  string UID;
  std::ifstream input_file(kProcDirectory + std::to_string(pid) + kStatusFilename);

  if (input_file.is_open()) {
    while (std::getline(input_file, line)){
      std::istringstream linestream(line);
      linestream >> key >> value;     

      if(key == "Uid:"){
        /*std::cout << line << "\n"; //debugging
        std::cout << "key = " << key << "\n"; //debugging
        std::cout << "value = " << value << "\n"; //debugging*/
        UID = value;
      }  
    }
  }  
  return UID;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string UID = LinuxParser::Uid(pid);
  string line;
  string user_key;
  string x_key;
  string uid_key;
  string USER = "user0";
  std::ifstream input_file(kPasswordPath);

  if (input_file.is_open()) {
    while (std::getline(input_file, line)){
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> user_key >> x_key >> uid_key;

      if(uid_key == UID){USER = user_key;}
      /*std::cout << "line_post = " << line << "\n"; //debugging
      std::cout << "user_key = " << user_key << "\n";//debugging
      std::cout << "x_key = " << x_key << "\n"; //debugging
      std::cout << "uid_key = " << uid_key << "\n"; //debugging
      std::cout << "UID = " << UID << "\n"; //debugging*/
    }
  }  
  return USER;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string line;
  string temp_key;  
  vector<string> keys;
  long uptime_secs;
  std::ifstream input_file(kProcDirectory + std::to_string(pid) + kStatFilename);

  if (input_file.is_open()) {
    std::getline(input_file, line);
    std::istringstream linestream(line);   
    for(int i = 0; i < 22; i++){      
      linestream >> temp_key;
      keys.push_back(temp_key);
    }

    uptime_secs = std::stol(keys[21])/sysconf(_SC_CLK_TCK);
    /*std::cout << "line = " << line << "\n"; //debugging
    std::cout << "uptime key = " << keys[21] << "\n"; //debugging
    std::cout << "uptime_secs = " << uptime_secs << "\n"; //debugging*/
  }
  input_file.close();
  return LinuxParser::UpTime() - uptime_secs;
}

float LinuxParser::ProcessLoad(int pid){
  string line;
  string temp_key;  
  vector<string> keys;
  
  std::ifstream input_file(kProcDirectory + std::to_string(pid) + kStatFilename);

  if (input_file.is_open()){
    std::getline(input_file, line);
    std::istringstream linestream(line);   
    for(int i = 0; i < 22; i++){      
      linestream >> temp_key;
      keys.push_back(temp_key);
    }
  }  

  // https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat/16736599#16736599
  float uptime = LinuxParser::UpTime();
  float utime = std::stol(keys[13]);
  float stime = std::stol(keys[14]);
  float cutime = std::stol(keys[15]);
  float cstime = std::stol(keys[16]);
  float starttime = std::stol(keys[21]);

  float total_time = utime + stime + cutime + cstime;
  float seconds = uptime - (starttime/sysconf(_SC_CLK_TCK));
  float load = total_time / sysconf(_SC_CLK_TCK) / seconds;
  
  /*
  std::cout << "line = " << line << "\n"; //debugging
  std::cout << "uptime = " << uptime << "\n"; //debugging
  std::cout << "utime = " << utime << "\n"; //debugging
  std::cout << "stime = " << stime << "\n"; //debugging
  std::cout << "cutime = " << cutime << "\n"; //debugging
  std::cout << "cstime = " << cstime << "\n"; //debugging
  std::cout << "starttime = " << starttime << "\n"; //debugging
  std::cout << "total_time = " << total_time << "\n"; //debugging
  std::cout << "load = " << load << "\n"; //debugging
  */
  return load;
}
