#include "remote_control.h"

// можете просто запустить.ехе и убедиться что оно живое.
int main(){

    RemoteControl remote_control;
    initRemoteControl(&remote_control);

    Lamp lamp;
    initLamp(&lamp);

    Computer computer;
    initComputer(&computer);

    Conditioner conditioner;
    initConditioner(&conditioner);




    TurnOnCommand turn_on_lamp;
    initTurnOnCommand(&turn_on_lamp, (IDevice*)&lamp);

    TurnOnCommand turn_on_computer;
    initTurnOnCommand(&turn_on_computer, (IDevice*)&computer);

    TurnOnCommand turn_on_conditioner;
    initTurnOnCommand(&turn_on_conditioner, (IDevice*)&conditioner);

    InteractCommand interact_with_lamp;
    initInteractCommand(&interact_with_lamp, (IDevice*)&lamp);

    InteractCommand interact_with_computer;
    initInteractCommand(&interact_with_computer, (IDevice*)&computer);

    InteractCommand interact_with_conditioner;
    initInteractCommand(&interact_with_conditioner, (IDevice*)&conditioner);

    UninteractCommand uninteract_with_conditioner;
    initUninteractCommand(&uninteract_with_conditioner, (IDevice*)&conditioner);

    TurnOffCommand turn_off_lamp;
    initTurnOffCommand(&turn_off_lamp, (IDevice*)&lamp);

    TurnOffCommand turn_off_computer;
    initTurnOffCommand(&turn_off_computer, (IDevice*)&computer);

    TurnOffCommand turn_off_conditioner;
    initTurnOffCommand(&turn_off_conditioner, (IDevice*)&conditioner);



    MacroCommand turn_on_everything;
    initMacroCommand(&turn_on_everything);

    pushCommand(&turn_on_everything, (ICommand*)&turn_on_conditioner);
    pushCommand(&turn_on_everything, (ICommand*)&turn_on_lamp);
    pushCommand(&turn_on_everything, (ICommand*)&turn_on_computer);

    MacroCommand interact_with_everything;
    initMacroCommand(&interact_with_everything);

    pushCommand(&interact_with_everything, (ICommand*)&interact_with_conditioner);
    pushCommand(&interact_with_everything, (ICommand*)&interact_with_lamp);
    pushCommand(&interact_with_everything, (ICommand*)&interact_with_computer);

    MacroCommand turn_off_everything;
    initMacroCommand(&turn_off_everything);

    pushCommand(&turn_off_everything, (ICommand*)&turn_off_conditioner);
    pushCommand(&turn_off_everything, (ICommand*)&turn_off_lamp);
    pushCommand(&turn_off_everything, (ICommand*)&turn_off_computer);


    MacroCommand test_nested_macro_command;
    initMacroCommand(&test_nested_macro_command);

    pushCommand(&test_nested_macro_command, (ICommand*)&turn_on_everything);
    pushCommand(&test_nested_macro_command, (ICommand*)&turn_off_everything);

    MacroCommand scene_nested_macro_command;
    initMacroCommand(&scene_nested_macro_command);

    pushCommand(&scene_nested_macro_command, (ICommand*)&interact_with_everything);
    pushCommand(&scene_nested_macro_command, (ICommand*)&turn_on_everything);
    pushCommand(&scene_nested_macro_command, (ICommand*)&interact_with_everything);
    pushCommand(&scene_nested_macro_command, (ICommand*)&turn_off_everything);

    MacroCommand conditioner_macro_command;
    initMacroCommand(&conditioner_macro_command);

    pushCommand(&conditioner_macro_command, (ICommand*)&interact_with_conditioner);
    pushCommand(&conditioner_macro_command, (ICommand*)&turn_on_conditioner);
    pushCommand(&conditioner_macro_command, (ICommand*)&interact_with_conditioner);
    pushCommand(&conditioner_macro_command, (ICommand*)&interact_with_conditioner);
    pushCommand(&conditioner_macro_command, (ICommand*)&interact_with_conditioner);
    pushCommand(&conditioner_macro_command, (ICommand*)&interact_with_conditioner);
    pushCommand(&conditioner_macro_command, (ICommand*)&uninteract_with_conditioner);
    pushCommand(&conditioner_macro_command, (ICommand*)&uninteract_with_conditioner);
    pushCommand(&conditioner_macro_command, (ICommand*)&turn_off_conditioner);
    pushCommand(&conditioner_macro_command, (ICommand*)&uninteract_with_conditioner);



    doRemoteControlCommand(&remote_control, (ICommand*)&test_nested_macro_command);
    undoRemoteControlCommand(&remote_control);
    undoRemoteControlCommand(&remote_control);

    doRemoteControlCommand(&remote_control, (ICommand*)&scene_nested_macro_command);
    undoRemoteControlCommand(&remote_control);

    doRemoteControlCommand(&remote_control, (ICommand*)&conditioner_macro_command);
    undoRemoteControlCommand(&remote_control);


    freeRemoteControl(&remote_control);
    freeMacroCommand(&turn_on_everything);
    freeMacroCommand(&interact_with_everything);
    freeMacroCommand(&turn_off_everything);
    freeMacroCommand(&test_nested_macro_command);
    freeMacroCommand(&scene_nested_macro_command);
    freeMacroCommand(&conditioner_macro_command);

    return 0;
}
