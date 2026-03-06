#include "command.h"

typedef struct {
    ICommand **history;
    size_t history_size;
} RemoteControl;

const static size_t MAX_REMOTE_CONTROL_HISTORY_SIZE = 512;

static void initRemoteControl(RemoteControl *r) {
    r->history = (ICommand**)malloc(MAX_REMOTE_CONTROL_HISTORY_SIZE * sizeof(ICommand));
    r->history_size = 0;
}

static void doRemoteControlCommand(RemoteControl *r, ICommand *command){
    if (r->history_size + 1 == MAX_REMOTE_CONTROL_HISTORY_SIZE){
        printf("OUT OF HISTORY MEMORY SORRY...\n");
            return;
    }
    r->history[r->history_size++] = command;
    command->vptr->doCommand(command);
}

static void undoRemoteControlCommand(RemoteControl *r){
    if (r->history_size == 0){
        printf("NOTHING TO UNDO.\n");
        return;
    }
    ICommand *current_command = r->history[r->history_size-1];
    current_command->vptr->undoCommand(current_command);
    r->history_size--;
}

static void freeRemoteControl(RemoteControl *r) {
    free(r->history);
}
