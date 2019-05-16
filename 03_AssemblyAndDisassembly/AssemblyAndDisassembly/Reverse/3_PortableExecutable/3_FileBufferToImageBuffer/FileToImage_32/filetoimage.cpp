#include "filetoimage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FileToImage::FileToImage()
{
    pFileBuffer = NULL;
    pImageBuffer = NULL;
    pNewFileBuffer = NULL;

    dos_header = NULL;
    nt_headers = NULL;
    section_header = NULL;
}

void FileToImage::readFileToHeapMemory(std::string &path)
{
    FILE * fp = fopen(path.c_str(),"rb");

    if(!fp){
        printf("open in_file error");
        exit(EXIT_FAILURE);
    }
    //获取文件大小
    fseek(fp,0,SEEK_END);
    fileSize = ftell(fp);
    fseek(fp,0,SEEK_SET);

    //堆内存分配
    pFileBuffer = (BYTE *)malloc(fileSize);
    if(NULL == pFileBuffer){
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    //读取文件到堆内存中
    int len = fread(pFileBuffer, 1, fileSize, fp);
    if(len != fileSize){
        printf("read error");
        exit(EXIT_FAILURE);
    }

    fclose(fp);  
}
void FileToImage::init(BYTE * pBuffer)
{
    dos_header = (IMAGE_DOS_HEADER *)pBuffer;
    nt_headers = (IMAGE_NT_HEADERS32 *)(pBuffer + dos_header->e_lfanew);
    section_header = (IMAGE_SECTION_HEADER *)(pBuffer + dos_header->e_lfanew + 4 + 20 + nt_headers->FileHeader.SizeOfOptionalHeader);
    imageSize = nt_headers->OptionalHeader.SizeOfImage;
    headerSize = nt_headers->OptionalHeader.SizeOfHeaders;
    numSections = nt_headers->FileHeader.NumberOfSections;
}
void FileToImage::printHexValueToFile(BYTE * pBuffer, std::string &fileName,DWORD size)
{
    std::string path("../FileToImage/HexFile_");
    path += fileName;
    FILE * fp = fopen(path.c_str(),"w");
    if(!fp){
        printf("open file error");
        exit(EXIT_FAILURE);
    }
    BYTE str[17] = {0};
    for(int i=0; i<size; i++){
        if(i%16 == 0){
            fprintf(fp,"%08xh: ",i);
        }
        fprintf(fp,"%02X ",pBuffer[i]);
        if((i+1)%16 == 0){
            //字符区域组包打印
            for(int j = 15; j > -1; j--){
                //如果是前32个控制字符，则全部打印'.',否则会破坏打印格式
                if(pBuffer[i-j] < 32){
                    str[15-j] = '.';
                    continue;
                }
                //如果最后一个(第16个)在ASCII扩展表中，则需要特别处理
                if(j==0 && pBuffer[i-j] & 0X80){
                    str[15] = '?';
                    continue;
                }
                str[15-j] = pBuffer[i-j];
            }
            str[16] = '\0';
            fprintf(fp,";%s\n",str);
        }
    }
    fclose(fp);
}
void FileToImage::fileToImage()
{
    if(((WORD *)pFileBuffer)[0] != IMAGE_DOS_SIGNATURE_VALUE){
        printf("it's not a PE file format!\n");
        //free(pFileBuffer);
        exit(EXIT_FAILURE);
    }
    init(pFileBuffer);

    pImageBuffer = (BYTE *)malloc(imageSize);
    if(NULL == pImageBuffer){
        printf("malloc pImageBuffer!\n");
        exit(EXIT_FAILURE);
    }
    memset(pImageBuffer, 0, imageSize);//清空，保证对齐时不必再填充'0'
    memcpy(pImageBuffer, pFileBuffer, headerSize);//复制头部

    //遍历节表，进行节的复制
    IMAGE_SECTION_HEADER * section = section_header;
    DWORD virAddr, fileAddr, copySize;
    for(int i = 0; i < numSections; i++){
       virAddr = section[i].VirtualAddress;//内存偏移地址计算
       fileAddr = section[i].PointerToRawData;//文件偏移地址计算
       copySize = section[i].SizeOfRawData;
       memcpy(pImageBuffer + virAddr, pFileBuffer + fileAddr, copySize);
    }
}
void FileToImage::imageToNewFile()
{
    init(pImageBuffer);

    pNewFileBuffer = (BYTE *)malloc(fileSize);
    if(NULL == pNewFileBuffer){
        printf("malloc pNewFileBuffer!\n");
        exit(EXIT_FAILURE);
    }
    //清空
    memset(pNewFileBuffer, 0, fileSize);
    //复制头部
    memcpy(pNewFileBuffer, pImageBuffer, headerSize);

    //遍历节表复制节
    IMAGE_SECTION_HEADER * section = section_header;
    DWORD virAddr, fileAddr, copySize;
    for(int i = 0; i < numSections; i++){
        virAddr = section[i].VirtualAddress;//内存偏移地址计酸
        fileAddr = section[i].PointerToRawData;//文件偏移地址计算
        copySize = section[i].SizeOfRawData;
        memcpy(pNewFileBuffer + fileAddr, pImageBuffer + virAddr, copySize);
    }
}
void FileToImage::copyMemoryToFile(std::string &path)
{
    init(pNewFileBuffer);

    FILE * fp = fopen(path.c_str(),"w");

    if(!fp){
        printf("open out_file error");
        exit(EXIT_FAILURE);
    }
#if 1
     fwrite(pNewFileBuffer, headerSize, 1, fp);//DOS头到节表对齐后的所有数据
     IMAGE_SECTION_HEADER * section = section_header;
     DWORD fileAddr, copySize;
     for(int i = 0; i < numSections; i++){
         fileAddr = section[i].PointerToRawData;//文件偏移地址计算
         //printf("%X\n",fileAddr);
         copySize = section[i].SizeOfRawData;
         fwrite(pNewFileBuffer + fileAddr, copySize, 1, fp);
     }
#endif

    fclose(fp);
}
