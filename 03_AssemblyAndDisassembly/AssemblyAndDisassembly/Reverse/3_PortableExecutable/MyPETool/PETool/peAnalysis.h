#ifndef PETOOL_H
#define PETOOL_H

#include "winnt.h"
#include <stdio.h>
#include <iostream>
#include <string>

#define TIMESTRING 50

class PETool
{
public:
    PETool();
    ~PETool();
    void readFileToHeapMemory();//读取文件到内存缓冲区中
    void initAllStructure();

    void TimeDateStampToString(DWORD stamp, char str[]);//时间戳转时间字符串

    void printFileHexValue();//PE的16进制文件转换输出
    void print_DOS_HEADER();//打印DOS头
    void print_NT_HEADERS();//打印NT头
    void print_FILE_HEADER();//打印标准PE头
    void print_OPTIONAL_HEADERS32();//打印可选PE头

    void print_SECTIONS_TABEL();//打印节表

    DWORD RVAToFOA(DWORD imageAddr);
    void print_DATA_DIRECTORY();//打印16个数据目录项地址与大小

    void print_ExportTable();//打印导出表
    void print_BaseRelocation();//打印重定位表
    void print_ImportDescriptor();//打印导入表
    void print_BoundImportDescriptor();//打印绑定导入表
    void print_IAT();
    void print_INT(IMAGE_THUNK_DATA32 * thunk);
public:
    FILE * fp_peMess;
    std::string outPEHeaderPath;
private:
    std::string path;
    std::string outHexPath;
    BYTE * pFileBuffer; //堆空间存储PE文件内容

    int fileBufferSize; //PE文件大小
    DWORD headSize;

    IMAGE_DOS_HEADER * dos_header;   //DOS头指针
    IMAGE_NT_HEADERS32 * nt_headers32;//nt头指针
    IMAGE_FILE_HEADER * file_header;//标准PE头指针
    IMAGE_OPTIONAL_HEADER32 * optional_header32;//可选PEt欧指针
    DWORD CpuType;  //CPU型号

    DWORD imageSize;//SizeOfImagebase
    DWORD sectionAlignment;//内存对齐
    DWORD fileAlignment;//文件对齐

    WORD sectionNum;//节数
    WORD optionalSize;//可选PEt头大小
    IMAGE_SECTION_HEADER * section_header;//节表首地址
    IMAGE_DATA_DIRECTORY * dataDir;//目录表指针
};

#endif // PETOOL_H
