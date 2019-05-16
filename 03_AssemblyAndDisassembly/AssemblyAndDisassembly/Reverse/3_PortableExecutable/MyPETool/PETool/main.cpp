#include <iostream>
#include "peAnalysis.h"
using namespace std;

int main()
{
    PETool head;

    head.fp_peMess = fopen(head.outPEHeaderPath.c_str(),"w");
    if(!head.fp_peMess){
        printf("open file error");
        exit(EXIT_FAILURE);
    }
    head.printFileHexValue();
#if 1
    head.print_DOS_HEADER();
    head.print_NT_HEADERS();
    head.print_SECTIONS_TABEL();
    head.print_ExportTable();
    head.print_BaseRelocation();
    head.print_ImportDescriptor();
    head.print_IAT();
    head.print_BoundImportDescriptor();

#endif
    fclose(head.fp_peMess);
    printf("deal over!\n");
    return 0;
}

