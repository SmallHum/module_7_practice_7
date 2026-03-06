#include <stdio.h>
#include <stdlib.h>

// 0000  000   0000  0  0  0000   000  0000
//  0    0  0  0     0  0   0    0     0
//  0    0  0  0000  0 0    0    0     0000
//  0    0  0  0     0 0    0    0     0
// 0000  000   0000  00    0000   000  0000

typedef struct{
    void (*turnOn)(void*);
    void (*turnOff)(void*);
    void (*interact)(void*);
    void (*uninteract)(void*);
    char (*getState)(void*);
} DeviceVTable;

typedef struct{
    DeviceVTable *vptr;
} IDevice;

static void turnOnDevice(IDevice *d){
    d->vptr->turnOn(d);
}

static void turnOffDevice(IDevice *d){
    d->vptr->turnOff(d);
}

static void interactDevice(IDevice *d){
    d->vptr->interact(d);
}

static void uninteractDevice(IDevice *d){
    d->vptr->uninteract(d);
}

static char getState(IDevice *d){
    return d->vptr->getState(d);
}

// 0       0    0     0  0000
// 0      0 0   00   00  0   0
// 0     0   0  0 0 0 0  0000
// 0     00000  0  0  0  0
// 0000  0   0  0  0  0  0

typedef struct{
    IDevice base;
    // ВСМЫСЛЕ В С НЕТ БУЛОВ
    char state;
} Lamp;

static void turnOnLamp(void* lamp){
    Lamp *lptr = (Lamp*)lamp;

    if (lptr->state) {
        printf("LAMP ALREADY TURNED ON\n");
        return;
    }
    printf("TURNING ON LAMP\n");
    lptr->state = 1;
}

static void turnOffLamp(void* lamp){
    Lamp *lptr = (Lamp*)lamp;

    if (lptr->state) {
        printf("TURNING OFF LAMP\n");
        lptr->state = 0;
        return;
    }
    printf("LAMP ALREADY TURNED OFF\n");
}

static void interactLamp(void* lamp){
    Lamp *lptr = (Lamp*)lamp;

    if (lptr->state) {
        printf("YOU TOUCHED THE LAMP. NOTHING HAPPENED.\n");
        return;
    }
    printf("LAMP NOT TURNED ON TO INTERACT WITH IT...\n");
}

static void uninteractLamp(void* lamp){
    Lamp *lptr = (Lamp*)lamp;

    if (lptr->state) {
        printf("YOU CAN'T UNITERACT A TURNED ON LAMP...\n");
        return;
    }
    printf("YOU UNTOUCHED THE LAMP. NOTHING UNHAPPENED.\n");
}

static char getLampState(void *lamp){
    Lamp *lptr = (Lamp*)lamp;
    return lptr->state;
}

static DeviceVTable lamp_vtable = {
    .turnOn = &turnOnLamp,
    .turnOff = &turnOffLamp,
    .interact = &interactLamp,
    .uninteract = &uninteractLamp,
    .getState = &getLampState
};

static void initLamp(Lamp *lamp){
    lamp->base.vptr = &lamp_vtable;
    lamp->state = 0;
}

//  000   000   0     0  0000  0   0 00000 00000 0000
// 0     0   0  00   00  0   0 0   0   0   0     0   0
// 0     0   0  0 0 0 0  0000  0   0   0   00000 0000
// 0     0   0  0  0  0  0     0   0   0   0     0 00
//  000   000   0  0  0  0      000    0   00000 0   0

typedef struct{
    IDevice base;
    char state;
} Computer;

static void turnOnComputer(void* computer){
    Computer *cptr = (Computer*)computer;

    if (cptr->state) {
        printf("COMPUTER ALREADY TURNED ON\n");
        return;
    }
    printf("TURNING ON COMPUTER\n");
    cptr->state = 1;
}

static void turnOffComputer(void* computer){
    Computer *cptr = (Computer*)computer;

    if (cptr->state) {
        printf("TURNING OFF COMPUTER\n");
        cptr->state = 0;
        return;
    }
    printf("COMPUTER ALREADY TURNED OFF\n");
}

static void interactComputer(void* computer){
    Computer *cptr = (Computer*)computer;

    if (cptr->state) {
        printf("YOUR DESKTOP. THE MAN WHO MADE THE PLOV IS ON THE WALLPAPER.\n\
YOU DECIDE TO DRAW SOMETHING.\n\
YOU DREW THE MAN WHO MADE THE PLOV.\n\
YOU HAVEN'T SEEN ANYTHING MORE INSPIRING THAN MEN LIKE HIM.\n");
        return;
    }
    printf("IT'S A COMPUTER.\n\
IT'S TURNED OFF.\n");
}

static void uninteractComputer(void* computer){
    Computer *cptr = (Computer*)computer;

    if (cptr->state) {
        printf("YOUR DESKTOP. THE MAN WHO MADE THE PLOV IS ON THE WALLPAPER.\n\
YOU HATE HIM.\n\
NO, YOU CAN'T HATE HIM, HE DOESN'T EVEN KNOW YOU.\n\
YOU DELETE ALL YOUR DRAWINGS OF HIM YOU'VE MADE.\n\
YOU FEEL EMPTY.\n\
WHAT A CREEP YOU ARE.\n");
        return;
    }
    printf("IT'S A COMPUTER.\n\
IT'S TURNED OFF.\n\
FOR A SECOND, YOU THOUGHT YOU COULD UNDO SOMETHING.\n\
FORTUNATELY, THERE'S NOTHING TO UNDO.\n");
}

static char getComputerState(void *lamp){
    Computer *cptr = (Computer*)lamp;
    return cptr->state;
}

static DeviceVTable computer_vtable = {
    .turnOn = &turnOnComputer,
    .turnOff = &turnOffComputer,
    .interact = &interactComputer,
    .uninteract = &uninteractComputer,
    .getState = &getComputerState
};

static void initComputer(Computer *computer){
    computer->base.vptr = &computer_vtable;
    computer->state = 0;
}

//  000  000  0   0 0000  0000 00000 0000  000  0   0 0000 0000
// 0    0   0 00  0 0   0  0     0    0   0   0 00  0 0    0   0
// 0    0   0 0 0 0 0   0  0     0    0   0   0 0 0 0 0000 0000
// 0    0   0 0  00 0   0  0     0    0   0   0 0  00 0    0 00
//  000  000  0   0 0000  0000   0   0000  000  0   0 0000 0   0

typedef struct {
    IDevice base;
    char state;
    int temperature_celsius;
} Conditioner;

static void turnOnConditioner(void* conditioner){
    Conditioner *cptr = (Conditioner*)conditioner;

    if (cptr->state) {
        printf("CONDITIONER ALREADY TURNED ON\n");
        return;
    }
    printf("TURNING ON CONDITIONER\n");
    cptr->state = 1;
}

static void turnOffConditioner(void* conditioner){
    Conditioner *cptr = (Conditioner*)conditioner;

    if (cptr->state) {
        printf("TURNING OFF CONDITIONER\n");
        cptr->state = 0;
        return;
    }
    printf("CONDITIONER ALREADY TURNED OFF\n");
}

static void interactConditioner(void *conditioner){
    Conditioner *cptr = (Conditioner*)conditioner;

    if(!cptr->state){
        printf("CONDITIONER NOT TURNED ON.\n");
        return;
    }

    cptr->temperature_celsius += 5;
    printf("+5 TEMPERATURE TO CONDITIONER. NOW IT'S %d.\n", cptr->temperature_celsius);
}

static void uninteractConditioner(void *conditioner){
    Conditioner *cptr = (Conditioner*)conditioner;

    if(!cptr->state){
        printf("CONDITIONER NOT TURNED ON.\n");
        return;
    }

    cptr->temperature_celsius -= 5;
    printf("-5 TEMPERATURE TO CONDITIONER. NOW IT'S %d.\n", cptr->temperature_celsius);
}

static char getConditionerState(void *conditioner){
    Conditioner *cptr =(Conditioner*)conditioner;
    return cptr->state;
}

static DeviceVTable conditioner_vtable = {
    .turnOn = &turnOnConditioner,
    .turnOff = &turnOffConditioner,
    .interact = &interactConditioner,
    .uninteract = &uninteractConditioner,
    .getState = &getConditionerState
};

static void initConditioner(Conditioner *conditioner){
    conditioner->base.vptr = &conditioner_vtable;
    conditioner->state = 0;
    conditioner->temperature_celsius = -273;
}
