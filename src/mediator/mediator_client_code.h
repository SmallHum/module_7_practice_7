#include "mediator.h"
#include "user.h"

static void doMediatorClientCode(){

    //i couldn't understand channels so here's two chats

    IMediator *mediator_1 = (IMediator*)malloc(sizeof(ChatMediator));
    initChatMediator((ChatMediator*)mediator_1);

    IMediator *mediator_2 = (IMediator*)malloc(sizeof(ChatMediator));
    initChatMediator((ChatMediator*)mediator_2);

    AUser *user_1 = (AUser*)malloc(sizeof(UserMishkaFreddy));
    initMishkaFreddy((UserMishkaFreddy*)user_1);

    AUser *user_2 = (AUser*)malloc(sizeof(UserMishkaFreddy));
    initMishkaFreddy((UserMishkaFreddy*)user_2);

    AUser *user_3 = (AUser*)malloc(sizeof(UserMishkaFreddy));
    initMishkaFreddy((UserMishkaFreddy*)user_3);

    AUser *user_4 = (AUser*)malloc(sizeof(UserMishkaFreddy));
    initMishkaFreddy((UserMishkaFreddy*)user_4);

    pushUserChatMediator((ChatMediator*)mediator_1, user_1);
    pushUserChatMediator((ChatMediator*)mediator_1, user_2);
    pushUserChatMediator((ChatMediator*)mediator_2, user_3);
    pushUserChatMediator((ChatMediator*)mediator_2, user_4);

    sendAUser(user_1, "HEY USER 2 LOOK HERE [photo]");
    sendAUser(user_4, "WE HAD SO MUCH FUN AT THE CIMENA");
    sendAUser(user_2, "LMAO");
    sendAUser(user_4, "I WONDER WHAT USER 1 THINKS ABOUT YOU.");
    sendAUser(user_2, "IS THAT USER 3?");
    sendAUser(user_3, "DUDE WHY ARE YOU ASKING THIS?");
    sendAUser(user_1, "HIS UGLY ASS HAIRCUT");
    sendAUser(user_3, "LIKE I CARE WHAT SHE THINKS");
    sendAUser(user_2, "[photo]");
    sendAUser(user_3, "IT SHOULDN'T MATTER TO ME AND YOU TOO");
    sendAUser(user_4, "YEAH, SURE...");
    sendAUser(user_1, "XDXDXDDXXDX");


    free(mediator_1);
    free(mediator_2);
    free(user_1);
    free(user_2);
    free(user_3);
    free(user_4);
}
