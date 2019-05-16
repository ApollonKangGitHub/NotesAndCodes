#include "bmp.h"

int main()
{
    int ret,reta;
    char path[256],Newpath[256];
    BITMAPFILEHEADER bmfh;
    BITMAPINFOHEADER bmih;
    BYTE *imgData;
    DWORD temp;

    printf("Input the path of the image(.bmp) : \n");
    scanf("%s",path);
    reta=checkPath(path);
    if(reta==-1)
    {
        printf("Error: the path of the image is invalid.\n");
        return -1;
    }

    do
    {
        ret=printMenu();
        switch(ret)
        {
            case 1:
                reta=printBmpFileHeader(path);
                if(reta==-1)
                {
                    printf("Error: can not print the File Header.\n");
                    break;
                }
                break;
            case 2:
                reta=printBmpInfoHeader(path);
                if(reta==-1)
                {
                    printf("Error: can not print the Info Header.\n");
                    break;
                }
                break;
            case 3:
                printf("Input the path you want to save as:\n");
                scanf("%s",Newpath);
                reta=saveBmp(Newpath,path);
                if(reta==-1)
                {
                    printf("Error: can not save as the image.\n");
                    break;
                }
                printf("Save as the image successfully.\n");
                break;
            default:
                break;
        }
    }while(ret!=0);

    return 0;
}





