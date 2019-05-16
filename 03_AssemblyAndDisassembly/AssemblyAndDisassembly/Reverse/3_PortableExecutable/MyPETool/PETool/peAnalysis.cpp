#include "peAnalysis.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

PETool::PETool()
{
    pFileBuffer = NULL;
    dos_header = NULL;
    nt_headers32 = NULL;
    section_header = NULL;

    readFileToHeapMemory();
    initAllStructure();

    //输出文件名格式化
    outPEHeaderPath = std::string(path,0,path.find_last_of('.'));
    outPEHeaderPath += "_PE_Analysis.txt";
    outHexPath = std::string(path,0,path.find_last_of('.'));
    outHexPath += "_HexMessage.txt";
}
void PETool::readFileToHeapMemory()
{
    printf("Please Absolute path of PEfile:\n");
    std::cin>>path;
    //打开文件
    FILE * fp = fopen(path.c_str(),"rb");

    if(!fp){
        printf("open file error");
        exit(EXIT_FAILURE);
    }
    //获取文件大小
    fseek(fp,0,SEEK_END);
    fileBufferSize = ftell(fp);
    fseek(fp,0,SEEK_SET);

    //堆内存分配
    pFileBuffer = (BYTE *)malloc(fileBufferSize);
    if(NULL == pFileBuffer){
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    memset(pFileBuffer, 0, fileBufferSize);
    //读取文件到堆内存中
    int len = fread(pFileBuffer, 1, fileBufferSize, fp);
    if(len != fileBufferSize){
        printf("read error");
        exit(EXIT_FAILURE);
    }
    fclose(fp);
}
void PETool::initAllStructure()
{
    if(((WORD *)pFileBuffer)[0] != IMAGE_DOS_SIGNATURE_VALUE){
        printf("it's not a PE file format!\n");
        exit(EXIT_FAILURE);
    }
    //DOS头的结构体指针指向PE文件缓冲区的首字节地址
    dos_header = (IMAGE_DOS_HEADER *)pFileBuffer;
    if(*((DWORD *)(pFileBuffer + dos_header->e_lfanew)) != IMAGE_NT_SIGNATURE_VALUE){
        printf("It's not a Effective Signature!\n");
        exit(EXIT_FAILURE);
    }
    //nt_headers32/nt_headers64指向NT头首字节地址
    DWORD n = dos_header->e_lfanew;

    CpuType = *((WORD*)(pFileBuffer + n + 4));
    if( CpuType == IMAGE_FILE_MACHINE_I386){//32bit
        nt_headers32 = (IMAGE_NT_HEADERS32 *)(pFileBuffer + n);
        optionalSize = nt_headers32->FileHeader.SizeOfOptionalHeader;//保存可选PE头大小
        sectionNum = nt_headers32->FileHeader.NumberOfSections;//保存节数
        fileAlignment = nt_headers32->OptionalHeader.FileAlignment;
        sectionAlignment = nt_headers32->OptionalHeader.SectionAlignment;
        imageSize = nt_headers32->OptionalHeader.SizeOfImage;
        headSize = nt_headers32->OptionalHeader.SizeOfHeaders ;
    }else{
        printf("It's not a Win32 Program!\n");
        exit(EXIT_FAILURE);
    }

    //将section_header指向节表首字节地址
    DWORD sectionTabelStart = n + 4 + IMAGE_SIZEOF_FILE_HEADER + optionalSize;
    section_header = (IMAGE_SECTION_HEADER *)(pFileBuffer + sectionTabelStart);

    //将数据表首地址指向IMAGE_OPTIONAL_HEADER结构的最后一个数组首元素的地址
    WORD dataDirSize = IMAGE_SIZEOF_DATA_DIRECTORY * IMAGE_NUMBEROF_DIRECTORY_ENTRIES;
    dataDir = (IMAGE_DATA_DIRECTORY *)(pFileBuffer + sectionTabelStart - dataDirSize);
}
void PETool::TimeDateStampToString(DWORD stamp, char str[])
{
        struct tm * p;
        p = gmtime((const time_t *)(&stamp));
        strftime(str, TIMESTRING, "%Y-%m-%d %H:%M:%S", p);
}
void PETool::printFileHexValue()
{
    FILE * fp = fopen(outHexPath.c_str(),"w");
    if(!fp){
        printf("open file error");
        exit(EXIT_FAILURE);
    }
    BYTE str[17] = {0};
    for(int i=0; i<fileBufferSize; i++){
        if(i%16 == 0){
            fprintf(fp,"%08xh: ",i);
        }
        unsigned char byte = pFileBuffer[i];
        fprintf(fp, "%02X ", byte);
        if((i+1)%16 == 0){//(i+1)%16 == 0 || (fileBufferSize-i) == 1
            //字符区域组包打印
            for(int j = 15; j > -1; j--){
                //如果是前32个控制字符，则全部打印'.',否则会破坏打印格式
                if(pFileBuffer[i-j] < 32){
                    str[15-j] = '.';
                    continue;
                }
                //如果最后一个(第16个)在ASCII扩展表中，则需要特别处理
                if(j==0 && pFileBuffer[i-j] & 0X80){
                    str[15] = '?';
                    continue;
                }
                str[15-j] = pFileBuffer[i-j];
            }
            str[16] = '\0';
            fprintf(fp,";%s\n",str);
            memset(str, 0, 16);
        }
    }
    fclose(fp);
}
void PETool::print_DOS_HEADER()
{
    if(NULL == dos_header){
        printf("error dos_header");
        exit(EXIT_FAILURE);
    }
    fprintf(fp_peMess,"DOS头(DOS header):\n");
    fprintf(fp_peMess,"\te_magic   :[%04X]\n",dos_header->e_magic);
    fprintf(fp_peMess,"\te_cblp    :[%04X]\n",dos_header->e_cblp);
    fprintf(fp_peMess,"\te_cp      :[%04X]\n",dos_header->e_cp);
    fprintf(fp_peMess,"\te_crlc    :[%04X]\n",dos_header->e_crlc);
    fprintf(fp_peMess,"\te_cparhdr :[%04X]\n",dos_header->e_cparhdr);
    fprintf(fp_peMess,"\te_minalloc:[%04X]\n",dos_header->e_minalloc);
    fprintf(fp_peMess,"\te_maxalloc:[%04X]\n",dos_header->e_maxalloc);
    fprintf(fp_peMess,"\te_ss      :[%04X]\n",dos_header->e_ss);
    fprintf(fp_peMess,"\te_sp      :[%04X]\n",dos_header->e_sp);
    fprintf(fp_peMess,"\te_csum    :[%04X]\n",dos_header->e_csum);
    fprintf(fp_peMess,"\te_ip      :[%04X]\n",dos_header->e_ip);
    fprintf(fp_peMess,"\te_cs      :[%04X]\n",dos_header->e_cs);
    fprintf(fp_peMess,"\te_lfarlc  :[%04X]\n",dos_header->e_lfarlc);
    fprintf(fp_peMess,"\te_ovno    :[%04X]\n",dos_header->e_ovno);

    fprintf(fp_peMess,"\te_res     :[");
    for(int i = 0; i<4; i++)
        fprintf(fp_peMess,"%04X",dos_header->e_res[i]);
    fprintf(fp_peMess,"]\n");

    fprintf(fp_peMess,"\te_oemid   :[%04X]\n",dos_header->e_oemid);
    fprintf(fp_peMess,"\te_oeminfo :[%04X]\n",dos_header->e_oeminfo);

    fprintf(fp_peMess,"\te_res2    :[");
    for(int i = 0; i<10; i++)
        fprintf(fp_peMess,"%04X",dos_header->e_res2[i]);
    fprintf(fp_peMess,"]\n");

    fprintf(fp_peMess,"\te_lfanew  :[%08X]\n",dos_header->e_lfanew);
}
void PETool::print_NT_HEADERS()
{
    if(!nt_headers32){
        printf("nt_header error!\n");
        exit(EXIT_FAILURE);
    }
    else{
        fprintf(fp_peMess,"NT头(NT header):\n");
        fprintf(fp_peMess,"\tPE标志(Signature):[%X]\n",nt_headers32->Signature);//打印Signature
        file_header = &(nt_headers32->FileHeader);
        print_FILE_HEADER();//打印标准PE头
        optional_header32 = &(nt_headers32->OptionalHeader);
        print_OPTIONAL_HEADERS32();//打印可选PE头
        print_DATA_DIRECTORY();//打印数据目录项
    }
}
void PETool::print_FILE_HEADER()
{
    char str[TIMESTRING] = {0};
    DWORD stamp = file_header->TimeDateStamp;
    TimeDateStampToString(stamp, str);
    fprintf(fp_peMess,"\t标准PE头(file header):\n");
    fprintf(fp_peMess,"\t\tMachine             :[%04X]\n",file_header->Machine);
    fprintf(fp_peMess,"\t\tNumberOfSections    :[%04X]\n",file_header->NumberOfSections);
    fprintf(fp_peMess,"\t\tTimeDateStamp       :[%08X]\t[%s]\n",stamp, str);
    fprintf(fp_peMess,"\t\tPointerToSymbolTable:[%08X]\n",file_header->PointerToSymbolTable);
    fprintf(fp_peMess,"\t\tNumberOfSymbols     :[%08X]\n",file_header->NumberOfSymbols);
    fprintf(fp_peMess,"\t\tSizeOfOptionalHeader:[%04X]\n",file_header->SizeOfOptionalHeader);
    fprintf(fp_peMess,"\t\tCharacteristics     :[%04X]\n",file_header->Characteristics);
}
void PETool::print_OPTIONAL_HEADERS32()
{
    fprintf(fp_peMess,"\t可选PE头(optional header):\n");
    fprintf(fp_peMess,"\t\tMagic                      :[%04X]\n",optional_header32->Magic);
    fprintf(fp_peMess,"\t\tMajorLinkerVersion         :[%02X]\n",optional_header32->MajorLinkerVersion);
    fprintf(fp_peMess,"\t\tMinorLinkerVersion         :[%02X]\n",optional_header32->MinorLinkerVersion);
    fprintf(fp_peMess,"\t\tSizeOfCode                 :[%08X]\n",optional_header32->SizeOfCode);
    fprintf(fp_peMess,"\t\tSizeOfInitializedData      :[%08X]\n",optional_header32->SizeOfInitializedData);
    fprintf(fp_peMess,"\t\tSizeOfUninitializedData    :[%08X]\n",optional_header32->SizeOfUninitializedData);
    fprintf(fp_peMess,"\t\tAddressOfEntryPoint        :[%08X]\n",optional_header32->AddressOfEntryPoint);
    fprintf(fp_peMess,"\t\tBaseOfCode                 :[%08X]\n",optional_header32->BaseOfCode);
    fprintf(fp_peMess,"\t\tBaseOfData                 :[%08X]\n",optional_header32->BaseOfData);
    fprintf(fp_peMess,"\t\tImageBase                  :[%08X]\n",optional_header32->ImageBase);
    fprintf(fp_peMess,"\t\tSectionAlignment           :[%08X]\n",optional_header32->SectionAlignment);
    fprintf(fp_peMess,"\t\tFileAlignment              :[%08X]\n",optional_header32->FileAlignment);
    fprintf(fp_peMess,"\t\tMajorOperatingSystemVersion:[%04X]\n",optional_header32->MajorOperatingSystemVersion);
    fprintf(fp_peMess,"\t\tMinorOperatingSystemVersion:[%04X]\n",optional_header32->MinorOperatingSystemVersion);
    fprintf(fp_peMess,"\t\tMajorImageVersion          :[%04X]\n",optional_header32->MajorImageVersion);
    fprintf(fp_peMess,"\t\tMinorImageVersion          :[%04X]\n",optional_header32->MinorImageVersion);
    fprintf(fp_peMess,"\t\tMajorSubsystemVersion      :[%04X]\n",optional_header32->MajorSubsystemVersion);
    fprintf(fp_peMess,"\t\tMinorSubsystemVersion      :[%04X]\n",optional_header32->MinorSubsystemVersion);
    fprintf(fp_peMess,"\t\tWin32VersionValue          :[%08X]\n",optional_header32->Win32VersionValue);
    fprintf(fp_peMess,"\t\tSizeOfImage                :[%08X]\n",optional_header32->SizeOfImage);
    fprintf(fp_peMess,"\t\tSizeOfHeaders              :[%08X]\n",optional_header32->SizeOfHeaders);
    fprintf(fp_peMess,"\t\tCheckSum                   :[%08X]\n",optional_header32->CheckSum);
    fprintf(fp_peMess,"\t\tSubsystem                  :[%04X]\n",optional_header32->Subsystem);
    fprintf(fp_peMess,"\t\tDllCharacteristics         :[%04X]\n",optional_header32->DllCharacteristics);
    fprintf(fp_peMess,"\t\tSizeOfStackReserve         :[%08X]\n",optional_header32->SizeOfStackReserve);
    fprintf(fp_peMess,"\t\tSizeOfStackCommit          :[%08X]\n",optional_header32->SizeOfStackCommit);
    fprintf(fp_peMess,"\t\tSizeOfHeapReserve          :[%08X]\n",optional_header32->SizeOfHeapReserve);
    fprintf(fp_peMess,"\t\tSizeOfHeapCommit           :[%08X]\n",optional_header32->SizeOfHeapCommit);
    fprintf(fp_peMess,"\t\tLoaderFlags                :[%08X]\n",optional_header32->LoaderFlags);
    fprintf(fp_peMess,"\t\tNumberOfRvaAndSizes        :[%08X]\n",optional_header32->NumberOfRvaAndSizes);
}
void PETool::print_SECTIONS_TABEL()
{
    fprintf(fp_peMess, "节表(Section Table):\n");
    IMAGE_SECTION_HEADER * section = section_header;
    char name[IMAGE_SIZEOF_SHORT_NAME + 1] = {0};
    for(int i = 0; i < sectionNum; i++){
        memset(name, 0, IMAGE_SIZEOF_SHORT_NAME + 1);
        memcpy(name, section+i, IMAGE_SIZEOF_SHORT_NAME);
        fprintf(fp_peMess,"\tsection[%d]:\n",i);

        fprintf(fp_peMess, "\t\tName                :[%s]\n",name);
        fprintf(fp_peMess, "\t\tVirtualSize:        :[%08X]\n",section[i].Misc.VirtualSize);
        fprintf(fp_peMess, "\t\tVirtualAddress      :[%08X]\n",section[i].VirtualAddress);
        fprintf(fp_peMess, "\t\tSizeOfRawData       :[%08X]\n",section[i].SizeOfRawData);
        fprintf(fp_peMess, "\t\tPointerToRawData    :[%08X]\n",section[i].PointerToRawData);
        fprintf(fp_peMess, "\t\tPointerToRelocations:[%08X]\n",section[i].PointerToRelocations);
        fprintf(fp_peMess, "\t\tPointerToLinenumbers:[%08X]\n",section[i].PointerToLinenumbers);
        fprintf(fp_peMess, "\t\tNumberOfRelocations :[%04X]\n",section[i].NumberOfRelocations);
        fprintf(fp_peMess, "\t\tNumberOfLinenumbers :[%04X]\n",section[i].NumberOfLinenumbers);
        fprintf(fp_peMess, "\t\tCharacteristics     :[%08X]\n",section[i].Characteristics);
    }
}
void PETool::print_DATA_DIRECTORY()
{
    fprintf(fp_peMess, "\t数据目录(data directory):\n");
    fprintf(fp_peMess, "\t\tDirectory\t\tRVA\t\t\tSIZE\n");

    #define NUMOFDIR IMAGE_NUMBEROF_DIRECTORY_ENTRIES
    for(int i = 0; i < NUMOFDIR; i++){
        switch(i){
            case 0:fprintf(fp_peMess, "\t\t导出表:\t");
                break;
            case 1:fprintf(fp_peMess, "\t\t导入表:\t");
                break;
            case 2:fprintf(fp_peMess, "\t\t资源表:\t");
                break;
            case 3:fprintf(fp_peMess, "\t\t异常信息:");
                break;
            case 4:fprintf(fp_peMess, "\t\t安全证书:");
                break;
            case 5:fprintf(fp_peMess, "\t\t重定位表:");
                break;
            case 6:fprintf(fp_peMess, "\t\t调试信息:");
                break;
            case 7:fprintf(fp_peMess, "\t\t版权所有:");
                break;
            case 8:fprintf(fp_peMess, "\t\t全局指针:");
                break;
            case 9:fprintf(fp_peMess, "\t\tTLS表:\t");
                break;
            case 10:fprintf(fp_peMess, "\t\t加载配置:");
                break;
            case 11:fprintf(fp_peMess, "\t\t绑定导入:");
                break;
            case 12:fprintf(fp_peMess, "\t\tIAT表:\t");
                break;
            case 13:fprintf(fp_peMess, "\t\t延迟导入:");
                break;
            case 14:fprintf(fp_peMess, "\t\tCOM信息:");
                break;
            case 15:fprintf(fp_peMess, "\t\t保留:\t");
                break;
        }
        fprintf(fp_peMess, "\t\t[%08X]\t[%08X]\n", dataDir[i].VirtualAddress, dataDir[i].Size);
    }
}

DWORD PETool::RVAToFOA(DWORD imageAddr)
{
    /*
     * 相对虚拟地址转文件偏移地址
     * ①获取Section数目
     * ②获取SectionAlignment
     * ③判断需要转换的RVA位于哪个Section中(section[n])，
     * offset = 需要转换的RVA-VirtualAddress，计算出RVA相对于本节的偏移地址
     * ④section[n].PointerToRawData + offset就是RVA转换后的FOA
    */

    if(imageAddr > imageSize){
        printf("RVAToFOA in_addr is error!%08X\n",imageAddr);
        exit(EXIT_FAILURE);
    }
    if(imageAddr < section_header[0].PointerToRawData){
        return imageAddr;//在头部（包括节表与对齐）则直接返回
    }
    IMAGE_SECTION_HEADER * section = section_header;
    DWORD offset = 0;
    for(int i = 0; i < sectionNum; i++){
        DWORD lower = section[i].VirtualAddress;//该节下限
        DWORD upper = section[i].VirtualAddress+section[i].Misc.VirtualSize;//该节上限
        if(imageAddr >= lower && imageAddr <= upper){
            //printf("%d\n",i);
            offset = imageAddr - lower + section[i].PointerToRawData;//计算出RVA的FOA
            break;
        }
    }
    return offset;
}

void PETool::print_ExportTable()
{
    fprintf(fp_peMess, "导出表(export table):\n");
    if(dataDir[0].VirtualAddress == 0){
        fprintf(fp_peMess, "\t不存在导出表!\n");
        return;
    }
    DWORD offset = RVAToFOA(dataDir[0].VirtualAddress);
    IMAGE_EXPORT_DIRECTORY * exportTb = (IMAGE_EXPORT_DIRECTORY * )(pFileBuffer + offset);

    fprintf(fp_peMess, "\tOffset to Export Table:[%08X]\n",dataDir[0].VirtualAddress);
    fprintf(fp_peMess, "\tCharacteristics:       [%08X]\n", exportTb->Characteristics);
    fprintf(fp_peMess, "\tTimeDateStamp:         [%08X]\n", exportTb->TimeDateStamp);
    fprintf(fp_peMess, "\tMajorVersion:          [%04X]\n", exportTb->MajorVersion);
    fprintf(fp_peMess, "\tMinorVersion:          [%04X]\n", exportTb->MinorVersion);
    fprintf(fp_peMess, "\tNameAddr:              [%08X]\n", exportTb->Name);
    fprintf(fp_peMess, "\tNameString:            [%s]\n", pFileBuffer + RVAToFOA(exportTb->Name));
    fprintf(fp_peMess, "\tBase:                  [%08X]\n", exportTb->Base);
    fprintf(fp_peMess, "\tNumberOfFunctions:     [%08X]\n", exportTb->NumberOfFunctions);
    fprintf(fp_peMess, "\tNumberOfNames:         [%08X]\n", exportTb->NumberOfNames);
    fprintf(fp_peMess, "\tAddressOfFunctions:    [%08X]\n", exportTb->AddressOfFunctions);
    fprintf(fp_peMess, "\tAddressOfNames:        [%08X]\n", exportTb->AddressOfNames);
    fprintf(fp_peMess, "\tAddressOfNameOrdinals: [%08X]\n", exportTb->AddressOfNameOrdinals);

    //打印导出表
    fprintf(fp_peMess, "\n\tOrdina\tfunc_FOA\tname_FOA\tFunctionName\n");
    DWORD * addrFunc = (DWORD *)(pFileBuffer + RVAToFOA(exportTb->AddressOfFunctions));
    DWORD * addrName = (DWORD *)(pFileBuffer + RVAToFOA(exportTb->AddressOfNames));
    WORD * addrOrdi = (WORD *)(pFileBuffer + RVAToFOA(exportTb->AddressOfNameOrdinals));

    DWORD i, j;
    for(i = 0; i < exportTb->NumberOfFunctions; i++){//导出时序号有NumberOfFunctions个
        if(addrFunc[i] == 0){
            continue;//地址值为0代表该序号没有对应的函数，是空余的
        }
        for(j = 0; j < exportTb->NumberOfNames; j++){//序号表序号有NumberOfNames个
            if(addrOrdi[j] == i){//序号表的值为地址表的索引
                fprintf(fp_peMess, "\t%04X\t%08X\t%08X\t%s\n", i + exportTb->Base, addrFunc[i], addrName[j], pFileBuffer + addrName[j]);
                break;
            }
        }
        //存在addrOrdi[j]时,i(索引)等于addrOrdi[j](值),不存在，则i依旧有效,i+Base依旧是序号
        if(j != exportTb->NumberOfNames){
            continue;//在序号表中找到
        }
        else{//如果在序号表中没有找到地址表的索引，说明函数导出是以地址导出的，匿名函数
            fprintf(fp_peMess, "\t%04X\t%08X\t%s\t%s\n", i + exportTb->Base, addrFunc[i], "--------", "--------");
        }
    }
}
void PETool::print_BaseRelocation()
{
    fprintf(fp_peMess, "重定位表(Relocation):\n");
    if(dataDir[5].VirtualAddress == 0){
        fprintf(fp_peMess, "\t不存在重定位表!\n");
        return;
    }
    BYTE secName[9] = {0};
    //rec指向重定位表第一个IMAGE_BASE_RELOCATION结构体
    IMAGE_BASE_RELOCATION * rec = (IMAGE_BASE_RELOCATION *)(pFileBuffer + RVAToFOA(dataDir[5].VirtualAddress));
    for(int i = 1; rec->SizeOfBlock && rec->VirtualAddress; i++){
        DWORD foa = RVAToFOA(rec->VirtualAddress);
        DWORD size = (rec->SizeOfBlock - 8) / 2;
        //确定该结构体所处节，并获取节名称
        IMAGE_SECTION_HEADER * section = section_header;
        for(int t = 0; t < sectionNum; t++){
            DWORD lower = RVAToFOA(section[t].VirtualAddress);
            DWORD upper = RVAToFOA(section[t].VirtualAddress) + section[t].Misc.VirtualSize;
            if(foa >= lower && foa <= upper){
                memcpy(secName, section[t].Name, 8);
                break;
            }
        }
        //打印该页主要信息
        fprintf(fp_peMess, "\tIndex[%d]\tsection[%s]\tOffset[%08X]\tItems[%dD:%XH]\t【Block】\n", i, secName, foa, size, size);

        //打印一个页中所有重定位地址与信息
        WORD * recAddr = (WORD *)((BYTE *)rec + 8);//recAddr指向重定位表结构体后的首字节
        fprintf(fp_peMess, "\t\tindex\toffset\t\ttype\t【Block Items】\n");
        for(DWORD j = 0; j < size; j++){
            DWORD offset = (recAddr[j] & 0X0FFF) + foa;//低四位是偏移地址
            WORD type = recAddr[j] >> 12;//高四位是有效判断位
            if(type == 0){
                fprintf(fp_peMess, "\t\t[%d] \t[--------]\tABSOLUTE[%d]\n", j+1, type);
                continue;
            }
            fprintf(fp_peMess, "\t\t[%d] \t[%08X]\tHIGHLOW[%d]\n", j+1, offset, type);
        }
        memset(secName, 0, 9);
        rec = (IMAGE_BASE_RELOCATION *)((BYTE *)rec + rec->SizeOfBlock);//进行下一页的判断
    }
}

void PETool::print_ImportDescriptor()
{
    fprintf(fp_peMess, "导入表(Import Descriptor):\n");
    if(dataDir[1].VirtualAddress == 0){
        fprintf(fp_peMess, "\t不存在导入表!\n");
        return;
    }
    char str[TIMESTRING] = {0};
    //导入表为数据目录的第2项,将import指向导入表第一个结构体
    IMAGE_IMPORT_DESCRIPTOR * import = (IMAGE_IMPORT_DESCRIPTOR *)(pFileBuffer + RVAToFOA(dataDir[1].VirtualAddress));
    while(true){
        if(import->Characteristics == 0){
            break;//最后一个结构体20字节为0则结束(直接判断一个Characteristics即可)
        }
        DWORD name = RVAToFOA(import->Name);
        DWORD original_ft = RVAToFOA(import->OriginalFirstThunk);
        DWORD ft = RVAToFOA(import->FirstThunk);
        //打印结构体信息
        fprintf(fp_peMess, "\t【Name:%s】\t"
                           "【NameAddr:%08X】\t"
                           "【OriginalFirstThunk:%08X】\t"
                           "【FirstThunk:%08X】\t"
                           "【TimeDateStamp:%08X】\n",
                pFileBuffer + name, name, original_ft, ft, import->TimeDateStamp);
        memset(str, 0, TIMESTRING);

        IMAGE_THUNK_DATA32 * thunk = (IMAGE_THUNK_DATA32 * )(pFileBuffer + original_ft);
        //打印INT表的详细信息
        print_INT(thunk);
        import++;
    }
}
void PETool::print_INT(IMAGE_THUNK_DATA32 * thunk)
{
    fprintf(fp_peMess, "\t\tThunkOffset\t\tThunkValue\t\tHint\t\tAPI Name\n");
    while(true){
        DWORD thunkValue = thunk->u1.AddressOfData;
        if(thunkValue == 0){
            break;//读取完毕
        }
        if(thunkValue >> 31){//最高位为1打印序号
            DWORD rva = thunkValue & 0X7FFFFFFF;//去掉最高位才是实际的值,否则RVAToFOA会出错
            DWORD offset = RVAToFOA(rva);
            fprintf(fp_peMess, "\t\t[%08X]\t\t[%08X]\t\t[--]\t\t函数序号[%04XH:%dD]\n",
                    offset, offset, rva, rva);
        }else{//最高位为0打印名称
            DWORD offset = RVAToFOA(thunkValue);
            //获取IMAGE_IMPORT_BY_NAME的地址
            IMAGE_IMPORT_BY_NAME * byName = (IMAGE_IMPORT_BY_NAME * )(pFileBuffer + offset);
            fprintf(fp_peMess, "\t\t[%08X]\t\t[%08X]\t\t[%04X]\t\t[%s]\n",
                    offset, offset, byName->Hint, byName->Name);
        }
        thunk++;
    }
}

void PETool::print_IAT()
{
    fprintf(fp_peMess, "IAT表(Import Address Table):\n");
    IMAGE_IMPORT_DESCRIPTOR * import = (IMAGE_IMPORT_DESCRIPTOR *)(pFileBuffer + RVAToFOA(dataDir[1].VirtualAddress));
    while(true){
        if(import->Characteristics == 0){
            break;
        }
        DWORD * addr = (DWORD *)(pFileBuffer + RVAToFOA(import->FirstThunk));
        //根据导入表的时间戳判断IAT中存放的是函数地址还是名字结构体的地址
        if(import->TimeDateStamp == -1){//函数地址
            fprintf(fp_peMess, "\tdllName:【%s】:\n", pFileBuffer + RVAToFOA(import->Name));
            for(int i = 0; addr[i]; i++){
                fprintf(fp_peMess, "\t\tFunction Addr:[%08X]\n", addr[i]);
            }
        }
        else if(import->TimeDateStamp == 0){//等同于INT表
            fprintf(fp_peMess, "\t等同于INT表!\n");
            break;
        }
        import++;
    }
}

void PETool::print_BoundImportDescriptor()
{
    fprintf(fp_peMess, "绑定导入表(Bound Import Descriptor):\n");
    if(dataDir[11].VirtualAddress == 0){
        fprintf(fp_peMess, "\t不存在绑定导入表!\n");
        return;
    }
    DWORD desAddr = dataDir[11].VirtualAddress;//获取第一个Bound Import Descriptor的RVA
    char str[TIMESTRING] = {0};\
    DWORD stamp = 0, off = 0, ref = 0, i = 0;

    IMAGE_BOUND_IMPORT_DESCRIPTOR * bound = (IMAGE_BOUND_IMPORT_DESCRIPTOR * )(pFileBuffer + RVAToFOA(desAddr));
    while(bound->TimeDateStamp != 0 && bound->OffsetModuleName != 0){
        stamp = bound->TimeDateStamp;//获取时间戳
        TimeDateStampToString(stamp, str);//时间戳转时间
        off = bound->OffsetModuleName;//获取名字偏移地址
        ref = bound->NumberOfModuleForwarderRefs;//获取依赖dll数

        fprintf(fp_peMess, "\tDllName:%s\n", pFileBuffer + RVAToFOA(desAddr + off));
        fprintf(fp_peMess, "\t\tTimeDateStamp:[%08XH:%dD]\n", stamp, stamp);
        fprintf(fp_peMess, "\t\tGMT:%s\n", str);
        fprintf(fp_peMess, "\t\tOffsetModuleName:%04X\n", off);
        fprintf(fp_peMess, "\t\tNumberOfModuleForwarderRefs:[%04XH:%dD]\n", ref, ref);

        IMAGE_BOUND_FORWARDER_REF * boundFor = (IMAGE_BOUND_FORWARDER_REF *)(bound);
        for(boundFor++, i = 0; i < ref; i++, boundFor++){
            memset(str, 0, TIMESTRING);
            off = boundFor->OffsetModuleName;
            stamp = boundFor->TimeDateStamp;
            TimeDateStampToString(stamp, str);

            fprintf(fp_peMess, "\t\t###############################################\n");
            fprintf(fp_peMess, "\t\tDllName:%s\n", pFileBuffer + RVAToFOA(desAddr + off));
            fprintf(fp_peMess, "\t\t\tTimeDateStamp:%08X\n",stamp);
            fprintf(fp_peMess, "\t\t\tGMT:%s\n", str);
            fprintf(fp_peMess, "\t\t\tOffsetModuleName:%04X\n", off);
            fprintf(fp_peMess, "\t\t\tReserved:%04X\n", boundFor->Reserved);
        }
        bound = (IMAGE_BOUND_IMPORT_DESCRIPTOR *)(boundFor);//下一个绑定dll
        memset(str, 0, TIMESTRING);
    }
}

PETool::~PETool()
{
    free(pFileBuffer);
}
