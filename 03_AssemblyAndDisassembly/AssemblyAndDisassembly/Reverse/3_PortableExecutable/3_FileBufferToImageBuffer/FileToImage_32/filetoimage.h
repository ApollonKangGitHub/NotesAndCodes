#ifndef FILETOIMAGE_H
#define FILETOIMAGE_H
#include "winnt.h"
#include <iostream>
class FileToImage
{
public:
    FileToImage();
    void readFileToHeapMemory(std::string &path);
    void init(BYTE * pBuffer);
    void printHexValueToFile(BYTE * pBuffer, std::string &fileName, DWORD size);
    void fileToImage();
    void imageToNewFile();
    void copyMemoryToFile(std::string &path);
public:
    BYTE * pFileBuffer; //堆空间存储PE文件内容
    BYTE * pImageBuffer;//
    BYTE * pNewFileBuffer;
    int fileSize; //PE文件大小

    IMAGE_DOS_HEADER * dos_header;   //DOS头

    IMAGE_NT_HEADERS32 * nt_headers;
    IMAGE_FILE_HEADER * file_header;
    IMAGE_OPTIONAL_HEADER32 * optional_header;

    IMAGE_SECTION_HEADER * section_header;

    DWORD headerSize;
    DWORD imageSize;
    WORD numSections;
};

#endif // FILETOIMAGE_H
