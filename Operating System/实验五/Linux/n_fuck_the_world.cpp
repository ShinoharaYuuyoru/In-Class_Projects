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
#include <unistd.h>
#include <ftw.h>
#include <sys/stat.h>
#define BUF_SIZE 512

std::string src_root;
std::string dst_root;
char link_buff[BUF_SIZE];
char cwd[BUF_SIZE];

int copy_file(const char *src_path, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
    std::string dst_path = dst_root + &src_path[src_root.length()];
    switch(typeflag) {
        case FTW_SL:
            readlink(src_path, link_buff, BUF_SIZE);
            getcwd(cwd, sizeof(cwd));
            chdir(dst_root.c_str());
            symlink(link_buff,&src_path[src_root.length()+1]);
            chdir(cwd);
            break;
        case FTW_D:
            mkdir(dst_path.c_str(), sb->st_mode);
            break;
        case FTW_F:
            std::ifstream  src(src_path, std::ios::binary);
            std::ofstream  dst(dst_path, std::ios::binary);
            dst << src.rdbuf();
            break;
    }
    return 0;
}

int main(int argc,char* argv[]) {
    if (argc != 3){
        std::cout<<"Usage: "<<argv[0]<<" <src_path> <dst_path>"<<std::endl;
        return -1;
    }
    
    src_root = argv[1];
    dst_root = argv[2];
    nftw(src_root.c_str(), copy_file, 64 ,FTW_PHYS);
    
}
