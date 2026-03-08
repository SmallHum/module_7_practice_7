#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <stdio.h>

#define MAX_CAPACITY 512

//////////////////////////////////////
// IMediator
//////////////////////////////////////

typedef struct{
//              self   message
   void (*send)(void*, char*);
} IMediatorVTable;

static size_t mediator_id_count = 1;

typedef struct{
    IMediatorVTable *vptr;
    size_t id;
} IMediator;

static void sendIMediator(IMediator *self, char *message){
    self->vptr->send(self, message);
}

//////////////////////////////////////
// CHAT MEDIATOR
//////////////////////////////////////

#include "user.h"

typedef struct{
    IMediator base;
    AUser *users[MAX_CAPACITY];
    size_t users_size;
} ChatMediator;

static void pushUserChatMediator(ChatMediator *self, AUser *user){
    if (user->mediator_ptr != NULL){
        printf("ERROR: COULDN'T ADD USER THAT WAS ALREADY ADDED TO A MEDIATOR.\n");
        return;
    }
    user->mediator_ptr = (IMediator*)self;
    self->users[self->users_size++] = user;
    printf("USER (%d) ADDED TO MEDIATOR (%d)!\n", (int)user->id, (int)self->base.id);
}

static void sendChatMediator(void *self, char *message){
    ChatMediator *cptr = (ChatMediator*)self;

    for (size_t i = 0; i != cptr->users_size; i++){
        recieveAUser(cptr->users[i], message);
    }
}

static IMediatorVTable chat_mediator_vtable = {
  .send = &sendChatMediator
};

static void initChatMediator(ChatMediator *self){
    self->base.vptr = &chat_mediator_vtable;
    self->users_size = 0;
    self->base.id = mediator_id_count++;
}

#endif
