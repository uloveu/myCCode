#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <conio.h>
#include <io.h>
#include "string.h"

#define TOTALSPACE 5000  //起始空闲空间大小
#define INITADDRESS 2000 //起始地址
#define MINSPACE 100
#define MAXJOBCNT 10 //内存中作业数量最大值
struct JobMat
{
    char name[10];
    int address;
    int length;
    struct JobMat *next;
    struct JobMat *back;
};

struct FreeArea
{
    int address;
    int size;
    struct FreeArea *next;
    struct FreeArea *back;
};

struct JobMat *p_JobMat;
struct FreeArea *p_FreeArea;
int UnusedSpace;   //未分配的空闲空间大小
int CurrentJobCnt; //目前内存中的作业数量

int JobSize; //目前要分配的作业的大小
char JobName[10];
int JobAddress;

void initiation()
{
    p_FreeArea = (struct FreeArea *)malloc(sizeof(struct FreeArea));
    p_FreeArea->size = TOTALSPACE;
    p_FreeArea->address = INITADDRESS;
    p_FreeArea->next = NULL;
    p_FreeArea->back = NULL;
    UnusedSpace = TOTALSPACE;
    p_JobMat = NULL;
    CurrentJobCnt = 0;

    JobSize = 0;
    memset(JobName, 0, 10);
    JobAddress = 0;
}

void ffallocation()
{
    struct FreeArea *fp;
    struct JobMat *jp;
    struct JobMat *jp1;
    struct JobMat *jp2;
    JobAddress = -1;
    if (UnusedSpace < JobSize)
    {
        printf("Sorry, you input job length is too big ^_^ \n");
        return;
    }
    JobAddress = 0;
    fp = p_FreeArea;
    while (fp != NULL)
        if ((fp->size) < JobSize)
        {
            fp = fp->next;
        }
        else
        {
            CurrentJobCnt = CurrentJobCnt + 1;
            UnusedSpace = UnusedSpace - JobSize;
            jp2 = (struct JobMat *)malloc(sizeof(struct JobMat));
            strcpy(jp2->name, JobName);
            jp2->length = JobSize;
            jp2->address = fp->address;
            JobAddress = jp2->address;
            if (p_JobMat == NULL)
            {
                jp2->next = NULL;
                jp2->back = NULL;
                p_JobMat = jp2;
            }
            else
            {
                jp = p_JobMat;
                while ((jp != NULL) && (jp2->address < jp->address))
                {
                    jp1 = jp;
                    jp = jp->next;
                }
                jp2->next = jp;
                if (jp == NULL)
                {
                    jp2->back = jp1;
                    jp1->next = jp2;
                }

                else
                {
                    jp2->back = jp->back;
                    if (jp->back != NULL)
                        jp1->next = jp2;
                    else
                        p_JobMat = jp2;
                    jp->back = jp2;
                }
            }
            if (fp->size - JobSize < MINSPACE)
            {
                if (fp->next != NULL)
                    fp->next->back = fp->back;
                if (fp->back != NULL)
                    fp->back->next = fp->next;
                else
                    p_FreeArea = fp->next;
            }
            else
            {
                fp->size = fp->size - JobSize;
                fp->address = fp->address + JobSize;
            }
            /*exit(1);*/
            return;
        }
}
void ffcollection()
{
    struct FreeArea *fp;
    struct FreeArea *fp1;
    struct FreeArea *fp2;
    struct JobMat *jp;
    int f;
    jp = p_JobMat;
    f = 0;
    while ((jp != NULL) && strcmp(jp->name, JobName) != 0)
    {
        jp = jp->next;
    }
    if (jp != NULL)
    {
        CurrentJobCnt = CurrentJobCnt - 1;
        UnusedSpace = UnusedSpace + jp->length;
        if (p_FreeArea == NULL)
        {
            p_FreeArea = (struct FreeArea *)malloc(sizeof(struct FreeArea));
            p_FreeArea->address = jp->address;
            p_FreeArea->size = jp->length;
            p_FreeArea->next = NULL;
            p_FreeArea->back = NULL;
        }
        else
        {
            fp = p_FreeArea;
            while ((fp != NULL) && (fp->address < jp->address))
            {
                fp1 = fp;
                fp = fp->next;
            }
            if (fp != NULL)
            {
                if ((fp->next != NULL) && (fp->next->address == jp->address + jp->length))
                {
                    f = f + 1;
                }
                if ((fp->back != NULL) && (jp->address == fp1->address + fp1->size))
                {
                    f = f + 2;
                }
            }
            else if ((jp->address) == (fp1->address + (fp1->size)))
            {
                f = f + 2;
            }
            switch (f)
            {
            case 0:
                fp2 = (struct FreeArea *)malloc(sizeof(struct FreeArea));
                fp2->address = jp->address;
                fp2->size = jp->length;
                fp2->next = fp;
                if (fp != NULL)
                {
                    fp2->back = fp->back;
                    if (fp->back != NULL)
                        fp1->next = fp2;
                    else
                        p_FreeArea = fp2;
                    fp->back = fp2;
                }
                else
                {
                    fp2->back = fp1;
                    fp1->next = fp2;
                }
                break;
            case 1:
                fp->size = fp->size + jp->length;
                fp->address = jp->address;
                break;
            case 2:
                fp1->size = fp1->size + jp->length;
                break;
            case 3:
                fp1->size = fp1->size + jp->length + fp->size;
                fp1->next = fp->next;
                if (fp->next != NULL)
                {
                    fp->next->back = fp2;
                }
                free(fp);
                break;
            }
        }
        if (jp == p_JobMat)
            p_JobMat = jp->next;
        if (jp->next != NULL)
        {
            jp->next->back = jp->back;
        }
        if (jp->back != NULL)
            jp->back->next = jp->next;
        free(jp);
    }
}

void showyou()
{
    struct JobMat *jp;
    // clrscr();
    if (CurrentJobCnt <= 0)
    {
        printf("No job.\n");
    }
    else
    {
        printf("name   length(b)   addre\n");
        jp = p_JobMat;
        while (jp != NULL)
        {
            printf("%s      %d        %d\n", jp->name, jp->length, jp->address);
            jp = jp->next;
        }
    }
    printf("The total left is %d bytes\n", UnusedSpace);
}

void coalesce()
{
    struct FreeArea *fp;
    struct FreeArea *fp1;
    struct JobMat *jp;
    int bottom;
    if (CurrentJobCnt > 0)
    {
        jp = p_JobMat;
        bottom = TOTALSPACE + INITADDRESS;
        while (jp != NULL)
        {
            jp->address = bottom - jp->length;
            bottom = bottom - jp->length;
            jp = jp->next;
        }
        fp = p_FreeArea;
        while (fp != NULL)
        {
            fp1 = fp;
            fp = fp->next;
            free(fp1);
        }
        p_FreeArea = (struct FreeArea *)malloc(sizeof(struct FreeArea));
        p_FreeArea->size = UnusedSpace;
        p_FreeArea->address = INITADDRESS;
        p_FreeArea->next = NULL;
        p_FreeArea->back = NULL;
    }
}

void menu()
{
    int select;

    printf("\n\n\n****************MENU***************\n");
    printf("You can select one of the following:\n");
    printf("(1)Require to be allocate.\n");
    printf("(2)Require to collecte the size.\n");
    printf("(3)Check the memory.\n");
    printf("(4)Quit.\n");
    printf("***********************************\n");
    scanf("%d", &select);
    switch (select)
    {
    case 1:
        if (CurrentJobCnt >= MAXJOBCNT)
        {
            printf("The job is too many");
        }
        else
        {
            printf("Enter your job name:");
        }
        scanf("%s", JobName);
        printf("Enter your job length:");
        scanf("%d", &JobSize);
        ffallocation();
        switch (JobAddress)
        {
        case -1:
            printf("the memory is full");
            break;
        case 0:
            coalesce();
            ffallocation();
            break;
        default:
            break;
        }
        break;
    case 2:
        printf("Enter the name of job:");
        scanf("%s", JobName);
        ffcollection();

        break;
    case 3:

        break;
    case 4:
        exit(1);
        break;
    default:
        printf("You input a wrong number!\n");
        break;
    }
}

int main(void)
{
    initiation();
    while (1)
    {
        menu();
        showyou();
    }
    return 0;
}
