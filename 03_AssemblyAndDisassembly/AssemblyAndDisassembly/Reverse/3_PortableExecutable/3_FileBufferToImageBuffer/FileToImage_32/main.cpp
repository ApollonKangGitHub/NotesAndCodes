#include <iostream>
#include "filetoimage.h"
using namespace std;

int main()
{
#if 1
    string fileBuffer("notepadFileBuffer.txt");
    string imageBuffer("notepadImageBuffer.txt");
    string newFileBuffer("newnotepadFileBuffer.txt");

    FileToImage fti;

    string path_in("../FileToImage/notepad.exe");
    fti.readFileToHeapMemory(path_in);
    fti.printHexValueToFile(fti.pFileBuffer, fileBuffer, fti.fileSize);

    fti.fileToImage();
    fti.printHexValueToFile(fti.pImageBuffer, imageBuffer, fti.imageSize);

    string path_out("../FileToImage/newNotepad.exe");
    fti.imageToNewFile();
    fti.printHexValueToFile(fti.pNewFileBuffer, newFileBuffer, fti.fileSize);
    fti.copyMemoryToFile(path_out);

    printf("over\n");
#endif
#if 0
    string fileBuffer("DosBoxFileBuffer.txt");
    string imageBuffer("DosBoxImageBuffer.txt");
    string newFileBuffer("newDosBoxFileBuffer.txt");

    FileToImage fti;

    string path_in("../FileToImage/DosBox.exe");
    fti.readFileToHeapMemory(path_in);
    fti.printHexValueToFile(fti.pFileBuffer, fileBuffer, fti.fileSize);

    fti.fileToImage();
    fti.printHexValueToFile(fti.pImageBuffer, imageBuffer, fti.imageSize);

    string path_out("../FileToImage/newDosBox.exe");
    fti.imageToNewFile();
    fti.printHexValueToFile(fti.pNewFileBuffer, newFileBuffer, fti.fileSize);
    fti.copyMemoryToFile(path_out);

    printf("over\n");
#endif
    return 0;
}

