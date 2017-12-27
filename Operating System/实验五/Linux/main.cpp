//
//  main.cpp
//  File_Duplicator
//
//  Created by 林理露 on 18/04/2017.
//  Copyright © 2017 林理露. All rights reserved.
//

#include <string>
#include <iostream>
#include <fstream>

#include <ftw.h>
#include <sys/stat.h>

std::string src_root;
std::string dst_root;

constexpr int ftw_max_fd = 100;

extern "C" int copy_file(const char*, const struct stat, int);

int copy_file(const char* src_path, const struct stat* sb, int typeflag) {
    std::string dst_path = dst_root + &src_path[src_root.length()];
    switch(typeflag) {
        case FTW_D:
            mkdir(dst_path.c_str(), sb->st_mode);
            break;
        case FTW_F:
            std::ifstream  src(src_path, std::ios::binary);
            std::ofstream  dst(dst_path, std::ios::binary);
            dst << src.rdbuf();
    }
    return 0;
}

int main(int argc,char* argv[]) {
    if (argc != 3)
        std::cout<<"Usage: mycp <src_path> <dst_path>"<<std::endl;
    else{
        src_root = argv[1];
        dst_root = argv[2];
        ftw(src_root.c_str(), copy_file, ftw_max_fd);
    }
}
