#include "processor.h"

#include "linux_parser.h"
#include <iostream>

// TODO [COMPLETE]: Return the aggregate CPU utilization
float Processor::Utilization() { 
    float ActiveJiffies = LinuxParser::ActiveJiffies();
    float IdleJiffies = LinuxParser::IdleJiffies();
    float delta_ActiveJiffies = ActiveJiffies - active_jiffies;
    float delta_IdleJiffies = IdleJiffies - idle_jiffies;
    float cpu_utilization = (delta_ActiveJiffies - delta_IdleJiffies)/delta_ActiveJiffies;
    active_jiffies = float(LinuxParser::ActiveJiffies()); 
    idle_jiffies = float(LinuxParser::IdleJiffies());

    /*float cpu_utilization = 0.99;
    float ActiveJiffies = LinuxParser::ActiveJiffies();
    float IdleJiffies = LinuxParser::IdleJiffies();
    cpu_utilization = (ActiveJiffies - IdleJiffies)/ActiveJiffies;
    std::cout << "CPU Utilization = " << cpu_utilization << "\n";
    std::cout << "ActiveJiffies = " << ActiveJiffies << "\n";
    std::cout << "IdleJiffies = " << IdleJiffies << "\n";*/
    
    return cpu_utilization;
}