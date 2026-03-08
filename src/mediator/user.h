#ifndef USER_H
#define USER_H

#include <stdlib.h>
#include "mediator.h"

//////////////////////////////
// AUser
//////////////////////////////

typedef struct{
//               self   message
    void (*send)(void*, char*);
//                  self   message
    void (*recieve)(void*, char*);
} AUserVTable;

static size_t user_id_count = 1;


typedef struct {
    AUserVTable *vptr;
    IMediator *mediator_ptr;
    size_t id;
} AUser;

static void sendAUser(AUser *self, char *message){
    self->vptr->send(self, message);
}

static void recieveAUser(AUser *self, char *message){
    self->vptr->recieve(self, message);
}

//////////////////////////////
// UserMishkaFreddy
//////////////////////////////

typedef struct{
    AUser base;
} UserMishkaFreddy;

static void sendMishkaFreddy(void *self, char *message){
    AUser *user = (AUser*)self;
    sendIMediator(user->mediator_ptr, message);
}

static void recieveMishkaFreddy(void *self, char *message){
    AUser *user = (AUser*)self;
    printf("USER (%d) RECIEVED A MESSAGE:   %s\n", (int)user->id, message);
}

static AUserVTable mishka_freddy_vtable = {
  .send = &sendMishkaFreddy,
  .recieve = &recieveMishkaFreddy
};

static void initMishkaFreddy(UserMishkaFreddy *user){
    user->base.vptr = &mishka_freddy_vtable;
    user->base.mediator_ptr = NULL;
    user->base.id = user_id_count++;
}

#endif
