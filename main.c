#include <stdio.h>
#include "KernelConnector.h"
#include "Commands.h"
#include <string.h>
#include <errno.h>

int main(void)
{

    char ssid[256];
    char passwd[256];
    int code;
    char is_encrypted;

    printf("1: Connect, 2: Disconnect: ");
    scanf("%d", &code);

    switch (code)
    {
        case COM_JOIN: {
            printf("SSID: ");
            scanf("%s", ssid);
            
            fflush(stdin);
            do
            {
                printf("Does it have password? (Y/N): ");
                scanf("%c", &is_encrypted);
            } while (is_encrypted != 'Y' && is_encrypted != 'N'
                    && is_encrypted != 'y' && is_encrypted != 'n');
            
            switch (is_encrypted)
            {
                case 'Y':
                case 'y':
                    printf("Password: ");
                    scanf("%s", passwd);
                    break;
                case 'N':
                case 'n':
                    passwd[0] = '\0';
                    break;
            }

            int a = send_join_ssid(ssid, passwd);
            printf("%s", strerror(a));  

            break;
        }
        case COM_DISCON: {
            int a = send_disconnect();
            printf("%s", strerror(a));  

            break;
       }
    }
    return 0;
}
