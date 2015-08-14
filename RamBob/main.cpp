//
//  main.cpp
//  RamBob
//
//  Created by Christian Treffs on 14.08.15.
//  Copyright (c) 2015 Christian Treffs. All rights reserved.
//  <ctreffs@gmail.com>
//
// Software is provided as is.
// The author will not be responsible for any damage this software causes to your system.
//

#include <iostream>
#include <cstring>
#include <sstream>
#include <cmath>

using namespace std;

int main(int argc, const char * argv[]) {
    const char *usageHelp = "usage: RamBob [disk size ...] [B|KB|MB|GB] [disk name ...]";
    
    const double BLOCK_SIZE = 512;
    
    // units that can be used
    const char *units[4]{"B","KB","MB","GB"};
    double      UNITS[4]{1.0,1000.0,1000000.0,1000000000.0};
    
    // default parameter values
    string diskName = "UNNAMED";
    double diskSize = -1;
    int unit = -1;
    
    // print help if not the right arg number
    if(argc != 4) {
        cout << usageHelp << endl;
        return 1;
    }
    
    // right arg number
    if(argc == 4) {
        // determine disk size
        try {
            diskSize   = stod(argv[1]);
        } catch (...)
        {
            cout << "no valid disk size" << endl;
            cout << usageHelp << endl;
            return 2;
        }
        
        
        // determine unit
        string unitStr = argv[2];
        for(int i=0; i < 4; ++i) {
            if(string(units[i]) == unitStr) {
                unit = UNITS[i];
                break;
            }
        }
        if(unit == -1) {
            cout << "no valid unit" << endl;
            cout << usageHelp << endl;
            return 3;
        }
        
        
        // determine disk name
        string optName = string(argv[3]);
        if(!optName.empty()) {
            diskName = optName;
        }
    }
    
    
    
    // calculate disk size
    double diskSizeByte = diskSize  * unit;
    const unsigned long diskSizeBlocks = static_cast<unsigned long>(floor(diskSizeByte/BLOCK_SIZE));
    
    // creation string
    ostringstream createRamDisk;
    createRamDisk << "diskutil erasevolume HFS+ \"" << diskName << "\" `hdiutil attach -owners on -nomount ram://" << diskSizeBlocks << "`\n";
    
    // send to system
    return system(createRamDisk.str().c_str());
}