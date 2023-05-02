#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
    //******************************************************
    //Reading and printing the current system's hostname   *
    //******************************************************
    fstream procFile;

    procFile.open("/proc/sys/kernel/hostname", ios::in);
    string hostname;
    getline(procFile, hostname);
    cout << "A. Host Name: " + hostname << endl << endl;
    procFile.close();

    //***********************************************************************
    //Reading and printing the current system's number of processing units  *
    //***********************************************************************
    procFile.open("/proc/cpuinfo", ios::in);
    string cpuInfoLine;
    int processorCount=0;


    while(getline(procFile, cpuInfoLine)){
        if(cpuInfoLine.find("processor") != string::npos){
            processorCount++;
        }
    }
    procFile.close();
    cout << "B. Number of processing units: " << processorCount << endl << endl;
    
    //******************************************************   
    //Reading and printing each processor's information    *
    //******************************************************
    cout << "C. CPU(s) Type and model: " << endl;
    
    procFile.open("/proc/cpuinfo", ios::in);
    while(getline(procFile, cpuInfoLine)){
        if(cpuInfoLine.find("processor") != string::npos){
            cout << endl << "\t" << cpuInfoLine << endl;
        }
        else if(cpuInfoLine.find("vendor_id") != string::npos){
            cout << "\t" << cpuInfoLine << endl;
        }
        else if(cpuInfoLine.find("model") != string::npos){
            cout << "\t" << cpuInfoLine << endl;
        }
        else if(cpuInfoLine.find("model name") != string::npos){
            cout << "\t" << cpuInfoLine << endl;
        }
    }
    procFile.close();
    cout << endl;

    //******************************************************
    //Reading and printing the system's kernel version     *
    //******************************************************
    procFile.open("/proc/version", ios::in);
    string version; 
    getline(procFile, version);
    cout << "D. Linux Kernel Version: " + version << endl << endl;
    procFile.close();

    //**********************************************************************************
    //Reading and printing the current system's time since last booted and time idle.  *
    //**********************************************************************************
    procFile.open("/proc/uptime", ios::in);
    int uptime, idleTime, hrs, mins, secs = 0;
    string uptimeFileLine, uptimeStr, idleTimeStr;

    //Reading in the file's line and parsing it into two separate strings
    getline(procFile, uptimeFileLine);
    uptimeStr = uptimeFileLine.substr(0, uptimeFileLine.find(" "));
    idleTimeStr = uptimeFileLine.substr(uptimeFileLine.find(" "));

    //Convert strings into ints and convert those seconds into hours, mins, leftover seconds
    uptime = stoi(uptimeStr);
    mins = uptime/60;
    hrs = mins/60;
    secs = uptime%60;
    cout << "E. System Time:" << endl;
    printf("\tTime since last reboot: %i seconds which is equivalent to %i hours %i minutes and %i seconds\n", uptime, hrs, mins, secs);
    
    idleTime = stoi(idleTimeStr);
    mins = idleTime/60;
    hrs = mins/60;
    secs = idleTime%60;
    printf("\tTime spent idle: %i seconds which is equivalent to %i hours %i minutes and %i seconds\n", idleTime, hrs, mins, secs);
    cout << endl;
    procFile.close();

    //***************************************************************
    //Reading and printing the current system's memory information  *
    //***************************************************************
    procFile.open("/proc/meminfo", ios::in);
    string memInfoLine;

    cout << "Memory Information:" << endl;
    for(int i=0; i <= 1; i++){
        getline(procFile, memInfoLine);
        cout << "\t" + memInfoLine << endl;
    }
    procFile.close();
    
    exit(0);
}