#include <windows.h>
#include <stdio.h>

DWORD mydrives = 100;
char lpBuffer[100];
typedef BOOL(WINAPI* P_GDFSE)(LPCTSTR, PULARGE_INTEGER, PULARGE_INTEGER, PULARGE_INTEGER);
BOOLEAN bSuccess;
DWORD dwSectorsPerCluster;
DWORD dwBytesPerSector;
DWORD dwFreeClusters;
DWORD dwTotalClusters;
DWORD test;
int i;

struct Computer
{
    char name[MAX_COMPUTERNAME_LENGTH + 1];
};

void main()
{
    DWORD cchComputerName = MAX_COMPUTERNAME_LENGTH + 1;
    Computer computer = { 0 };
    if (!GetComputerNameA(&computer.name[0], &cchComputerName))
    {
        printf("Failed to get computer name, Error: %u\r\n", GetLastError());
    }
    else
    {
        printf("Computer Name: %s\r\n", computer.name);
        printf("------");
    }

    test = GetLogicalDriveStrings(mydrives, (LPWSTR)lpBuffer);
    if (test != 0)
    {
        printf("\nThe logical drives of this machine are:\n");
        for (i = 0; i < 100; i++)
            printf("%c", lpBuffer[i]);
        printf("\n");
    }
    else
        printf("GetLogicalDriveStrings() is failed lor!!! Error code: %d\n", GetLastError());

    bSuccess = GetDiskFreeSpace(
        NULL, //current drive
        &dwSectorsPerCluster, //sectors per cluster
        &dwBytesPerSector, //bytes per sector
        &dwFreeClusters, //free clusters
        &dwTotalClusters //total clusters
    );

    if (!bSuccess) {
        printf("Could not get drive information.\n");
        exit(EXIT_FAILURE);
    }

    printf("------\n");
    printf("Bytes per sector: %d\n", dwBytesPerSector);
    printf("Sectors per cluster: %d\n", dwSectorsPerCluster);
    printf("Free clusters: %d\n", dwFreeClusters);
    printf("Total clusters: %d\n", dwTotalClusters);
    unsigned int uiKBPerCluster = dwBytesPerSector * dwSectorsPerCluster / 1024;
    printf("You have %.2f MB of free storage\n", (double)uiKBPerCluster * dwFreeClusters / 1024);
    printf("You have %.2f MB of total storage\n", (double)uiKBPerCluster * dwTotalClusters / 1024);
}

