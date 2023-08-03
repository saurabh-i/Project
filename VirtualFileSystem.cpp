#include<stdio.h>
#include<stdlib.h> //malloc 
#include<string.h>
#include<unistd.h>  //system calls
#include<iostream>  
#include<fcntl.h>

//total no of files that you can create
#define MAXINODE 3

//permission
#define READ 1 
#define WRITE 2

#define MAXFILESIZE 2048 

#define REGULAR 1
#define SPECIAL 2  //directory files

//used in Lseek
#define START 0
#define CURRENT 1
#define END 2

//1)BOOTBLOCK
//2)SUPERBLOCK
typedef struct superblock{
    int TotalInodes;
    int FreeInode;
}SUPERBLOCK , *PSUPERBLOCK;


//INODE
typedef struct inode
{
    char FileName[50];
    int InodeNumber;
    int FileSize;
    int FileActualSize;
    int FileType;  //(Regular file)
    char *Buffer;
    int LinkCount;
    int ReferenceCount;
    int permission;
    struct inode *next;
}INODE,*PINODE ,**PPINODE;

//FILETABLE
typedef struct filetable{
    int readoffset;
    int writeoffset;
    int count ;
    int mode;
    PINODE ptrinode;
}FILETABLE , *PFILETABLE;

//UFDT
typedef struct ufdt{
    PFILETABLE ptrfiletable;
}UFDT;

//GLOBAL variable
UFDT UFDTArr[50];       //Array of structure 
SUPERBLOCK SUPERBLOCKobj;
PINODE Head = NULL;

void InitialiseSuperBlock()
{
    int i = 0;
    //this loop will make the all the pointer in ufdt to NULL;
    //UFDTArr is an array of structure ufdt (in ufdt it contain the pointer which pointing to file table)
    while(i < MAXINODE)
    {
        UFDTArr[i].ptrfiletable = NULL;
        i++;
    }

    //Inilize the inode with 50 i.e total inode
    SUPERBLOCKobj.TotalInodes = MAXINODE;
    SUPERBLOCKobj.FreeInode = MAXINODE;
    
}   

void CreateDILB()
{
    int i = 1;

    //Newn are used to allocate the memeory
    PINODE newn = NULL;
    //temp will store the Head
    PINODE temp = Head;

    while(i <= MAXINODE)
    {
        //allocate the memory
        newn = (PINODE)malloc(sizeof(INODE));

        newn->LinkCount = 0;
        newn->ReferenceCount = 0;
        newn->FileType = 0;
        newn->FileSize = 0;

        newn->Buffer = NULL;
        newn->next = NULL; 
        
        //Value of INODE is i
        newn->InodeNumber = i;

        //store the newn NODE to appropritate position
        if(temp == NULL)
        {
           Head = newn;
           //copy the Head into temp 
           temp = Head;
        }else
        {
            temp->next = newn;
            temp = temp->next;
        }
        i++;
    }
    printf("\n\t DILB created Sccesfully");
}

PINODE GET_Inode(char *name)
{
    PINODE temp = Head;
    int i = 0 ;

    if(name == NULL)
    {
        return NULL;
    }

    while(temp != NULL)
    {
        if(strcmp (name,temp->FileName) == 0)
        {
            break;
        }
        temp = temp->next;
    }
    //printf("Temp :%s Name :%s",temp->FileName , name);
    return temp;
}


//create FILE_NAME permission | eg crete demo.txt 3
int CreateFile(char *name , int permisssion)
{

    int i = 0 ;
    PINODE temp = Head;

    //READ = 1 WRITE = 2
    if((name == NULL) || (permisssion == 0) || (permisssion > 3))
    {
        return -1;
    }

    //If there is no any node is free
    if(SUPERBLOCKobj .FreeInode == 0)
    {
        return -2;
    }

    (SUPERBLOCKobj.FreeInode)--;

    if(GET_Inode(name) != NULL)
    {
        return -3;
    }

    while(temp != NULL)
    {
        if(temp->FileType == 0)
        {
            break;
        }
        temp = temp->next;
    }

    while(i < 50)
    {
        if(UFDTArr[i].ptrfiletable == NULL)
        {
            break;
        }
        i++;
    }

    UFDTArr[i].ptrfiletable = (PFILETABLE)malloc(sizeof(FILETABLE));

    UFDTArr[i].ptrfiletable->count = 1;
    UFDTArr[i].ptrfiletable->mode = permisssion;
    UFDTArr[i].ptrfiletable->readoffset = 0;
    UFDTArr[i].ptrfiletable->writeoffset = 0;

    UFDTArr[i].ptrfiletable->ptrinode = temp;

    strcpy(UFDTArr[i].ptrfiletable->ptrinode->FileName , name);
    UFDTArr[i].ptrfiletable->ptrinode->FileType = REGULAR ;
    UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount = 1;
    UFDTArr[i].ptrfiletable->ptrinode->LinkCount = 1;
    UFDTArr[i].ptrfiletable->ptrinode->FileSize = MAXFILESIZE;
    UFDTArr[i].ptrfiletable->ptrinode->FileActualSize = 0;
    UFDTArr[i].ptrfiletable->ptrinode->permission = permisssion;
    UFDTArr[i].ptrfiletable->ptrinode->Buffer = (char *)malloc(sizeof(MAXFILESIZE));
    
    return i;     
    
}


void Display()
{
    PINODE temp = Head;

    while(temp != NULL)
    {
        printf("\n\tFile Name is :  %s",temp->FileName);
        temp = temp->next;
    }
}

void ls_File()
{
    PINODE temp = Head;

    
    printf("\n\t| File Name \t| Inode Number \t| File Size |");

    while(temp != NULL)
    {
        printf("\n \t| %7s \t %7d \t %7d    |",temp->FileName , temp->InodeNumber , temp->FileActualSize);
        temp = temp->next;
    }

    printf("\n\t---------------------------------------------\n");
}

//stat FILE_NAME | eg stat Demo.txt
int stat_File(char *name)
{
    PINODE temp = Head;
    int i = 0;

    if(name == NULL)
    {
        return -1;
    }

    while(temp != NULL)
    {
        if(strcmp(temp->FileName , name) == 0)
        {
            break;
        }
        temp = temp->next;
    }

    if(temp == NULL)
    {
        return -2;
    }

    printf("\n\t-------------------Stastical Informaction about File-------------------\n");
    printf("\n\t File Name : %s",temp->FileName);
    printf("\n\t Inode Number : %d",temp->InodeNumber);
    printf("\n\t File Size :%d",temp->FileSize);
    printf("\n\t File Actual Size :%d",temp->FileActualSize);
    printf("\n\t Link count :%d",temp->LinkCount);
    printf("\n\t Reference count :%d",temp->ReferenceCount);
    
    if(temp->permission == 1)
    {
        printf("\n\t Permission : Read only");
    }else if(temp->permission == 2)
    {
        printf("\n\t Permission : Write only");
    }else if(temp->permission == 3)
    {
        printf("\n\t Permission : Read & Write only");
    }
    
    return 0;
}

//fstat fd | eg fstat 3 where 3 is the file descriptor 
int Fstat_File(int fd)
{
    PINODE temp = NULL;
    if(fd < 0)
    {
        return 1;
    }

    if(UFDTArr[fd].ptrfiletable == NULL)
    {
        return -2;
    }

    temp = UFDTArr[fd].ptrfiletable->ptrinode ;

    printf("\n\t-------------------Stastical Informaction about File-------------------\n");
    printf("\n\t File Name : %s",temp->FileName);
    printf("\n\t Inode Number : %d",temp->InodeNumber);
    printf("\n\t File Size :%d",temp->FileSize);
    printf("\n\t File Actual Size :%d",temp->FileActualSize);
    printf("\n\t Link count :%d",temp->LinkCount);
    printf("\n\t Reference count :%d",temp->ReferenceCount);
    
    if(temp->permission == 1)
    {
        printf("\n\t Permission : Read only");
    }else if(temp->permission == 2)
    {
        printf("\n\t Permission : Write only");
    }else if(temp->permission == 3)
    {
        printf("\n\t Permission : Read & Write only");
    }
    
    return 0;

}

//This function will return the file index of (FD) 
//In this functoin i will iterate till filname is not name is not same
int GetFDFromName(char *name)
{
    //int i will return the value of FD 
    int i = 0;

    while(i < 50)
    {
        if(UFDTArr[i].ptrfiletable != NULL)
        {
            
            if(strcmp((UFDTArr[i].ptrfiletable->ptrinode->FileName),name) == 0)
            {
                break;
            }
            
        }
        i++;
    }
   
    return i;
}

int Rm_File(char *name)
{
    int fd = 0;
    fd = GetFDFromName(name);

    
    if(fd == -1)
    {
        return -1;
    }

    (UFDTArr[fd].ptrfiletable->ptrinode->LinkCount)--;

    if(UFDTArr[fd].ptrfiletable->ptrinode->LinkCount == 0)
    {
        UFDTArr[fd].ptrfiletable->ptrinode->FileType = 0;
        free(UFDTArr[fd].ptrfiletable);
    }
    UFDTArr[fd].ptrfiletable = NULL;
    (SUPERBLOCKobj.FreeInode)++;

    printf("File deleted succesfully");
}

void DisplayHelp()
{
    printf("\n\t ls : To list out all Files \n");
    printf("\n\t clear : To clear consol \n");
    printf("\n\t open : to open the file \n");
    printf("\n\t close : To close the Files \n");
    printf("\n\t closeall : To close all opened file \n");
    printf("\n\t read : To Read the contenets from the file \n");
    printf("\n\t write : To write contents into file \n");
    printf("\n\t exit : TO Terminate file System \n");
    printf("\n\t stat : stat To Display informaction of file using name \n");
    printf("\n\t fstat : stat To Display informaction of file using File descriptor \n");
    printf("\n\t truncate : To Remove all data from file \n");
    printf("\n\t rm : To Delete the file \n");
    printf("\n\t Filenames : Display all files ");
    
}


void man(char *name)
{
    if(name == NULL)
    {
        return ;
    }

    if(strcmp(name , "create") == 0)
    {
        printf("\n\t Description : Unsed to create new regular file \n");
        printf("\n\t Usage : create File_Name  Permission");
    }else if(strcmp(name , "read") == 0)
    {
        printf("\n\t Description : Unser to read data from file \n");
        printf("\n\t Usage : read File_name No_Of_Byutes_To_Read");
    }else if(strcmp(name , "write") ==  0)
    {
        printf("\n\t Description : Used to write into regular file \n");
        printf("\n\t Usage : write File_name  After this enter the data we want ot write \n");
    }else if(strcmp(name , "ls") == 0)
    {
        printf("\n\t Description : Unsed to list all information of files \n");
        printf("\n\t Usage : ls\n");
    }else if(strcmp(name , "stat") == 0)
    {
        printf("\n\t Description : Used to display informaction of file \n");
        printf("\n\t Usage : stat File_name\n");
    }
    else if(strcmp(name , "fstat") == 0)
    {
        printf("\n\t Description : Used to display informaction of file \n");
        printf("\n\t Usage : fstat File_Descriptor\n");
    }else if(strcmp(name , "truncate") == 0)
    {
        printf("\n\t Description : Used to remove the data form file \n");
        printf("\n\t Usage : truncate File_name\n");
    }else if(strcmp(name , "open") == 0)
    {
        printf("\n\t Description : Used to open existing file \n");
        printf("\n\t Usage : open File_name mode\n");
    }else if(strcmp(name , "close") == 0)
    {
        printf("\n\t Description : Used to close the opened file \n");
        printf("\n\t Usage : close File_name\n");
    }else if(strcmp(name , "closeall") == 0)
    {
        printf("\n\t Description : Used to close all opened file \n");
        printf("\n\t Usage : closeall\n");
    }else if(strcmp(name , "lseek") == 0)
    {
        printf("\n\t Description : Used to change file offset  \n");
        printf("\n\t Usage : lseek File_Name ChangeInOffset StarPoint\n");
    }else if(strcmp(name , "rm") == 0)
    {
        printf("\n\t Description : Used to delete the file \n");
        printf("\n\t Usage : rm File_Name\n");
    }else {
        printf("\n\t ERROR : No manual entry available");
    }
}

//WRITE FILE_NAME
int WriteFile(int fd , char *arr , int length)
{
    //checking the mode in filetable
    if((UFDTArr[fd].ptrfiletable->mode != WRITE) && UFDTArr[fd].ptrfiletable->mode != (READ + WRITE))
    {
        return -1;
    }
    //checking the permissdion in Inode 
    if((UFDTArr[fd].ptrfiletable->ptrinode->permission != WRITE) && (UFDTArr[fd].ptrfiletable->ptrinode->permission != (WRITE + READ)))
    {
        return -1;
    }

    //if file is already fulled 
    if(UFDTArr[fd].ptrfiletable->writeoffset > MAXFILESIZE)
    {
        return -2;
    }

    if(UFDTArr[fd].ptrfiletable->ptrinode->FileType != REGULAR)
    {
        return -3;
    }
    
    strncpy((UFDTArr[fd].ptrfiletable->ptrinode->Buffer), arr , length);
    
    (UFDTArr[fd].ptrfiletable->writeoffset) = (UFDTArr[fd].ptrfiletable->writeoffset) + length;

    (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize ) = (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) + length;

    return length; 
}

//Read FILE_NAME NO_OF_BYTES
int ReadFile(int fd ,char *ptr , int length)
{
    int read_size = 0;
    
    if(UFDTArr[fd].ptrfiletable == NULL)
    {
        return -1;
    }

    if((UFDTArr[fd].ptrfiletable->mode != READ ) && (UFDTArr[fd].ptrfiletable->mode != (READ + WRITE)))
    {
        return -2;
    }   

    if((UFDTArr[fd].ptrfiletable->ptrinode->permission != READ ) && (UFDTArr[fd].ptrfiletable->ptrinode->permission != READ + WRITE ))
    {
        return -2;
    }

    if(UFDTArr[fd].ptrfiletable->readoffset == UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize)
    {
        return -3;
    }

    if(UFDTArr[fd].ptrfiletable->ptrinode->FileType != REGULAR)
    {
        return -4;
    }

    read_size = (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) -(UFDTArr[fd].ptrfiletable->readoffset);

    if(read_size < length)
    {
        strncpy( ptr , (UFDTArr[fd].ptrfiletable->ptrinode->Buffer) + (UFDTArr[fd].ptrfiletable->readoffset), read_size );
        UFDTArr[fd].ptrfiletable->readoffset = UFDTArr[fd].ptrfiletable->readoffset + read_size;
    }else{
        strncpy( ptr , (UFDTArr[fd].ptrfiletable->ptrinode->Buffer) + (UFDTArr[fd].ptrfiletable->readoffset), length );
        UFDTArr[fd].ptrfiletable->readoffset = UFDTArr[fd].ptrfiletable->readoffset + length;
    }

    return length;

}
//open File_name mode
int OpenFile( char *name , int mode)
{
    int i = 0;
    PINODE temp = NULL;

    if(name == NULL || mode <= 0)
    {
        return -1;
    }

    temp = GET_Inode(name);

    if(temp == NULL)
    {
        return -2;
    }

    if(temp->permission < mode)
    {
        return -3;
    }    

    while(i < 50)
    {
        if(UFDTArr[i].ptrfiletable == NULL)
        {
            break;
        }
        i++;
    }

    UFDTArr[i].ptrfiletable = (PFILETABLE)malloc(sizeof(FILETABLE));

    if(UFDTArr[i].ptrfiletable == NULL)
    {
        return -1;
    }

    UFDTArr[i].ptrfiletable->count = 1;

    UFDTArr[i].ptrfiletable->mode = mode;

    if(mode == READ + WRITE)
    {
        UFDTArr[i].ptrfiletable->readoffset = 0;
        UFDTArr[i].ptrfiletable->writeoffset = 0;
    }else if(mode == READ )
    {
        UFDTArr[i].ptrfiletable->readoffset = 0;
    }else if(mode == WRITE)
    {
        UFDTArr[i].ptrfiletable->writeoffset= 0;
    }

    UFDTArr[i].ptrfiletable->ptrinode = temp;
    (UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount)++;
}

/*
int READ_FILE(char * name)
{
    if(name == NULL)
    {
        return -1;
    }

    PINODE temp = Head;

    while(temp != NULL)
    {
        if(strcmp(temp->FileName , name) == 0)
        {
            break;
        }
        temp = temp->next;
    }

    char * Arr = (char *)malloc(sizeof(MAXFILESIZE));

    if(Arr == NULL)
    {
        printf("\n\t ERROR : memory allocation failuer");
    }

    printf("temp->buffer :%s",temp->Buffer);
}


int WRITE_FILE(char * name)
{
    printf("function called");
    if(name == NULL)
    {
        return -1;
    }
    PINODE temp = Head;

    while(temp != NULL)
    {
        if(strcmp(temp->FileName , name) == 0)
        {
            break;
        }
        temp = temp->next;
    }

    printf("temp->Filename :%s",temp->FileName);

    char * Arr = (char *)malloc(sizeof(MAXFILESIZE));

    if(Arr == NULL)
    {
        printf("\n\t ERROR : memory allocation failuer");
    }

    printf("\n\t Enter Data :");
    scanf("%[^\n]",Arr);

    printf("\n\n Data is :%s",Arr);

    strcpy(((temp->Buffer) + temp->FileActualSize) + 1 ,Arr );

    printf("\n\t temp->buffer :%s",temp->Buffer);

}
*/

void Save_AllFIle()
{
    printf("\n\t inside save function ");
    PINODE temp = Head;
    int fd = 0 , fd1 = 0;
    int iret = 0;
    char *Data = NULL;

    if(Head == NULL)
     {   
        printf("\n\t No such file");
        return ;
    }

    while(temp != NULL)
    {
        fd = creat(temp->FileName , 0777);
        if(fd == -1)
        {
            printf("\n\t Unable to create File");
            return ;
        }

        fd1 = open(temp->FileName ,_O_RDWR);

        if(fd1 == -1)
        {
            printf("\n\t Unable to open file");
            return;
        }

        Data = (char *)malloc(sizeof(temp->Buffer));

        if(Data == NULL)
        {
            printf("\n\t Memory Allocation failure");
            return;
        }

        //printf("\n\t before :%s length :%d",Data , strlen(Data));
        fflush(stdin);
        strcpy(Data , temp->Buffer);

        
        //printf("\n\t Data :%s",Data);


        iret = write(fd1 , Data , strlen(Data));
        //printf("\n\t Data written succesfully with %d",iret);

        free(Data);
        Data = NULL;
        temp = temp->next;
    }
    
}

int main()
{
    char *ptr = NULL;
    int iret = 0 , fd = 0 , count = 0 , ret = 0;
    char command[4][80], str[80] , arr[1024];

    //Auxilazarya Data inilizaction (Application should inilzed )
    InitialiseSuperBlock();
    //Create emmpty link list 
    CreateDILB();

    while(1)
    {
        fflush(stdin);
        //clear the str string
        strcpy(str,"");

        printf("\n\t Lokare's VFS ->");


        fgets(str,80 , stdin); //scanf("%[^'\n']");
        //ssanf() function will return the count of string cutted into how many no of part it is also called tockenizacton
        count = sscanf(str,"%s %s %s %s ",command[0] , command[1] , command[2] , command[3]);

        if(count == 1)
        {
            if(strcmp(command[0] ,"exit") == 0)
            {
                Save_AllFIle();                
                printf("\n\t Terminating the application ");
                break;
            }
            else if(strcmp(command[0],"ls") == 0)
            {
                ls_File();                
            }
            else if(strcmp(command[0] , "Filenames") == 0)
            {
                Display();                              //------------------------------------------
            }
            else if(strcmp(command[0] , "Help") == 0)
            {
                DisplayHelp();                              
            }
            else if(strcmp(command[0] , "clear") == 0)
            {
                    system("cls");
                    continue;              
            }else{
                printf("\n\t ERROR : Command not found");
            }
        }else if(count == 2)
        {   
            //stat FILE_NAME
            if(strcmp(command[0] , "stat") == 0)
            {
                iret = stat_File(command[1]);

                if(iret == -1)
                {
                    printf("\n\t ERROR :Incorrect parameter");
                }else if(iret == -2)
                {
                    printf("\n\t ERROR : There is no such File");
                }else{
                    printf("\n\t ERROR :Command not found");
                }
            }
            else if(strcmp(command[0] , "fstat") == 0)             //fstat fd where fd is file descriptor
            {
                iret = Fstat_File(atoi(command[1]));

                if(iret == -1)
                {
                    printf("\n\t ERROR :Incorrect parameter");
                }else if(iret == -2)
                {
                    printf("\n\t ERROR : There is no such File");
                }else{
                    printf("\n\t ERROR :Command not found");
                }
            }
            //rm directory name 
            else if(strcmp(command[0] , "rm") == 0)
            {
                iret = Rm_File(command[1]);
                if(iret == -1)
                {
                    printf("\n\t ERROR :There is no such files ");
                }
                else{
                    printf("\n\t ERROR :ommand not found");
                }
                continue;
            }
            //man COMMAND
            else if(strcmp(command[0] , "man") == 0)
            {
                
                man(command[1]);
            }
            //Write FILE_NAME
            else if(strcmp(command[0] , "write") == 0)
            {
                
                fd = GetFDFromName(command[1]);

                if(fd == -1)
                {
                    printf("\n\t ERROR : Incorrect parameter ");
                }
                printf("\n\t Enter Data :");
                scanf("%[^\n]",arr);

                iret = strlen(arr);
                if(iret == 0)
                {
                    printf("\n\t ERROR :Incorrect Parameter \n");
                    continue;
                }
                //calling Write Function with file Descriptor , Arrray , lenght of array
                iret = WriteFile(fd , arr , iret);
                if(iret == -1)
                {
                    printf("\n\t ERROR :Permission Denied\n");
                }else if(iret == -2)
                {
                    printf("\n\t ERROR : There is no sufficient memory\n");
                }else if(iret == -3 )
                {
                    printf("\n\t ERROR : It is not regular File\n");
                }
                
            }
            /*else if(strcmp(command[0] , "READ") == 0)      //---------------------------------------------------
            {
                ret = READ_FILE(command[1]);

                if(ret == -1)
                {
                    printf("\n\t ERROR : Invalid Parameter");
                }
            }else if(strcmp(command[0] , "WRITE") == 0)      //---------------------------------------------------
            {
                ret = WRITE_FILE(command[1]);

                if(ret == -1)
                {
                    printf("\n\t ERROR : Invalid Parameter");
                }
            }*/
            else{
                printf("\n\t ERROR : Command not found");
            }
        }
        else if(count == 3)
        {
            
            //create (Filename , 777)
            if(strcmp(command[0] ,"create") == 0)
            {
                
                iret = CreateFile(command[1] , atoi(command[2]));
                if(iret >= 0)
                {   
                    printf("\n\tFile is successfully created with file descriptor : %d\n",iret);
                }else if(iret == -1)
                {
                    printf("\n\t ERROR : Incorrect Parameter ");
                }else if(iret == -2)
                {
                    printf("\n\t ERROR : Their is no INODE");
                }else if(iret == -3)
                {
                    printf("\n\t ERROR : File is already present");
                }else if(iret == -4)
                {
                    printf("\n\t ERROR : MEMORY Allocation Failure");
                    continue;
                }else{
                    printf("\n\t ERROR :Command not found");
                }
            }
            //Read FILE_NAME HOW_MUCH_WANT_TO_READ_IN_BYTES
            else if(strcmp(command[0] , "read") == 0)
            {
                fd = GetFDFromName(command[1]);

                if(fd == -1)
                {
                    printf("\n\t ERROR : Incorrect prameter ");
                }
                ptr = (char *)malloc(sizeof(atoi(command[2] + 1)));

                if(ptr == NULL)
                {
                    printf("\n\t ERROR : Memory allocation failure");
                }
                ret = ReadFile(fd , ptr , atoi(command[2]));
                if(ret == -1)
                {
                    printf("\n\t ERROR : File not existnig\n");
                }else if(ret == -2)
                {
                    printf("\n\t ERROR : Permisssion denied \n");
                }else if(ret == -3)
                {
                    printf("\n\t ERROR : Reached at the end of file \n");
                }else if(ret == -4)
                {
                    printf("\n\t ERROR : It is not regular file \n");
                }else if(ret == 0)
                {
                    printf("\n\t ERROR : File is empty \n");
                }else if(ret > 0)
                {
                    write(2 , ptr , ret);
                }continue;
            }else if(strcmp(command[0],"open") == 0)
            {
                ret = OpenFile(command[1] , atoi(command[2]));

                if(ret >= 0)
                {
                    printf("\n\t File is succesfully opened with file Descriptor : %d\n",ret);
                }else if(ret == -1)
                {
                    printf("\n\t ERROR : Incorrect Parameter ");
                }else if(ret == -2)
                {
                    printf("\n\t ERROR : File not present");
                }else if(ret == -3)
                {
                    printf("\n\t ERROR : Permission denied");
                    continue;
                }
            }
            else{
                printf("\n\t ERROR : command not found");
            }
        }
        else{
            printf("\n\t ERROR : Command not found");
        }
    }

}


//create 
//FIlenames
//ls
//stat
//fstat
//rm 
//clear
//help
//man
//read 
//write



//closeall
//close
//truncate
//lseek