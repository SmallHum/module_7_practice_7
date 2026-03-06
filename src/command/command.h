#include "device.h"

typedef struct {
    void (*doCommand)(void*);
    void (*undoCommand)(void*);
} CommandVTable;

typedef struct {
   CommandVTable   *vptr;
} ICommand;

static void doCommand(ICommand *c){
    c->vptr->doCommand(c);
}
static void undoCommand(ICommand *c){
    c->vptr->undoCommand(c);
}

const static char UNINITIALIZED_PREVIOUS_STATE = -1;

// TurnOnCommand

typedef struct {
    ICommand base;
    IDevice *reciever;
    char previous_state;
} TurnOnCommand;

static void doTurnOnCommand(void *command){
    TurnOnCommand *tptr = (TurnOnCommand*)command;

    tptr->previous_state = tptr->reciever->vptr->getState(tptr->reciever);
    tptr->reciever->vptr->turnOn(tptr->reciever);
}

static void undoTurnOnCommand(void *command){
    TurnOnCommand *tptr = (TurnOnCommand*)command;

    if(tptr->previous_state == UNINITIALIZED_PREVIOUS_STATE){
        printf("COMMAND WASN'T EXECUTED YET, CAN'T UNDO.\n");
        return;
    }

    if(tptr->previous_state){
        tptr->reciever->vptr->turnOn(tptr->reciever);
        return;
    }
    tptr->reciever->vptr->turnOff(tptr->reciever);
}

static CommandVTable turn_on_command_vtable = {.doCommand = &doTurnOnCommand, .undoCommand = &undoTurnOnCommand};

static void initTurnOnCommand(TurnOnCommand *c, IDevice *reciever){
    c->base.vptr = &turn_on_command_vtable;
    c->reciever = reciever;
    c->previous_state = UNINITIALIZED_PREVIOUS_STATE;
}




// TurnOffCommand

typedef struct {
    ICommand base;
    IDevice *reciever;
    char previous_state;
} TurnOffCommand;

static void doTurnOffCommand(void *command){
    TurnOffCommand *tptr = (TurnOffCommand*)command;

    tptr->previous_state = tptr->reciever->vptr->getState(tptr->reciever);
    tptr->reciever->vptr->turnOff(tptr->reciever);
}

static void undoTurnOffCommand(void *command){
    TurnOffCommand *tptr = (TurnOffCommand*)command;

    if(tptr->previous_state == UNINITIALIZED_PREVIOUS_STATE){
        printf("COMMAND WASN'T EXECUTED YET, CAN'T UNDO.\n");
        return;
    }

    if(tptr->previous_state){
        tptr->reciever->vptr->turnOn(tptr->reciever);
        return;
    }
    tptr->reciever->vptr->turnOff(tptr->reciever);
}

static CommandVTable turn_off_command_vtable = {.doCommand = &doTurnOffCommand, .undoCommand = &undoTurnOffCommand};

static void initTurnOffCommand(TurnOffCommand *c, IDevice *reciever){
    c->base.vptr = &turn_off_command_vtable;
    c->reciever = reciever;
    c->previous_state = UNINITIALIZED_PREVIOUS_STATE;
}


// InteractCommand

typedef struct {
    ICommand base;
    IDevice *reciever;
} InteractCommand;

static void doInteractCommand(void *command){
    InteractCommand *iptr = (InteractCommand*)command;

    iptr->reciever->vptr->interact(iptr->reciever);
}

static void undoInteractCommand(void *command){
    InteractCommand *iptr = (InteractCommand*)command;

    iptr->reciever->vptr->uninteract(iptr->reciever);
}

static CommandVTable interact_command_vtable = {.doCommand = &doInteractCommand, .undoCommand = &undoInteractCommand};

static void initInteractCommand(InteractCommand *c, IDevice *reciever){
    c->base.vptr = &interact_command_vtable;
    c->reciever = reciever;
}

// UninteractCommand

typedef struct {
    ICommand base;
    IDevice *reciever;
} UninteractCommand;

static void doUninteractCommand(void *command){
    UninteractCommand *iptr = (UninteractCommand*)command;

    iptr->reciever->vptr->uninteract(iptr->reciever);
}

static void undoUninteractCommand(void *command){
    UninteractCommand *iptr = (UninteractCommand*)command;

    iptr->reciever->vptr->interact(iptr->reciever);
}

static CommandVTable uninteract_command_vtable = {.doCommand = &doUninteractCommand, .undoCommand = &undoUninteractCommand};

static void initUninteractCommand(UninteractCommand *c, IDevice *reciever){
    c->base.vptr = &uninteract_command_vtable;
    c->reciever = reciever;
}

// MacroCommand


typedef struct {
    ICommand base;
    IDevice *reciever;

    ICommand **commands;
    size_t commands_size;
} MacroCommand;

static void doMacroCommand(void* command){
    MacroCommand *mptr = (MacroCommand*)command;

    printf("DOING A MACROCOMMAND...\n");

    for(size_t i = 0; i < mptr->commands_size; ++i){
        ICommand *current_command_ptr = mptr->commands[i];
        printf("* COMMAND %d:\n", (int)i);
        current_command_ptr->vptr->doCommand(current_command_ptr);
    }
}

static void undoMacroCommand(void* command){
    MacroCommand *mptr = (MacroCommand*)command;

    printf("UNDOING A MACROCOMMAND...\n");

    for(size_t i = mptr->commands_size-1; i != -1; --i){
        ICommand *current_command_ptr = mptr->commands[i];
        printf("* COMMAND %d:\n", (int)i);
        current_command_ptr->vptr->undoCommand(current_command_ptr);
    }
}

static CommandVTable macro_command_vtable = {.doCommand = &doMacroCommand, .undoCommand = &undoMacroCommand};

static size_t MAX_COMMANDS_SIZE = 512;

static void initMacroCommand(MacroCommand *c){
    c->base.vptr = &macro_command_vtable;
    c->commands = (ICommand**)malloc(MAX_COMMANDS_SIZE * sizeof(ICommand));
    c->commands_size = 0;
}

static void pushCommand(MacroCommand *c, ICommand *command){
    if(c->commands_size+1 == MAX_COMMANDS_SIZE){
        printf("REACHED MAX MACROCOMMAND SIZE I DON'T WANT TO WRITE DYNAMIC RESIZE FROM SCRATCH.\n");
        return;
    }
    c->commands[c->commands_size++] = command;
    printf("PUSHED A COMMAND INTO A MACROCOMMAND\n");
}

static void freeMacroCommand(MacroCommand *c){
    free(c->commands);
}
