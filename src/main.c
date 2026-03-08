#include "command/command_client_code.h"
#include "template_method/template_method_client_code.h"
#include "mediator/mediator_client_code.h"

// можете просто запустить.ехе и убедиться что оно живое.
int main(){

    int reply;

    while(1){
        printf("\nWHAT DO YOU WANT TO SEE?\n\
1 - COMMAND\n\
2 - TEMPLATE METHOD\n\
3 - MEDIATOR\n\
OTHER - QUIT\n");

        scanf("%d", &reply);

        switch (reply) {
            case 1:
                doCommandClientCode();
                break;
            case 2:
                doTemplateMethodClientCode();
                break;
            case 3:
                doMediatorClientCode();
                break;
            default:
                printf("OKAY BYE.\n");
                return 0;
        }
    }
    return 0;
}
