// Include the most common headers from the C standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Include the main libnx system header, for Switch development
#include <switch.h>

// Include simpleini
#include "simpleini/SimpleIni.h"

// Include other libs
#include <iostream>
#include <utility>

// defines
#define EMUMMCINI "sdmc:/emummc/emummc.ini"

std::string getStatusVar(std::string emummc_value)
{
    if (emummc_value == "0")
        return "Not active.";
    else if (emummc_value == "1")
        return "Active.";
    else
        return "Something went wrong or your emummc_enabled value is incorrect. Fix this manually before using emunand-toggle.";
}

// Returns a pair containing a status var and the ini object.
std::string printAndReturnEmuMMCstatus()
{
    CSimpleIniA ini;
    ini.SetUnicode();
    ini.LoadFile(EMUMMCINI);

    std::string emummc_value = ini.GetValue("emummc", "emummc_enabled", "something is wrong");
    std::cout << "EmuNAND status: " << getStatusVar(emummc_value) << "\n\n\n";
    return emummc_value;
}

void toggleEmuMMCVar(std::string emuMMCStatus)
{
    CSimpleIniA ini;
    ini.SetUnicode();
    ini.LoadFile(EMUMMCINI);

    if (emuMMCStatus == "0")
        ini.SetValue("emummc", "emummc_enabled", "1");
    if (emuMMCStatus == "1")
        ini.SetValue("emummc", "emummc_enabled", "0");
    ini.SaveFile(EMUMMCINI);
}

std::string printMainContent()
{
    consoleClear();
    // Show welcome message
    std::cout << "Welcome to emuMMC-Toggle v1.0.0.\n\n(c) Valentijn \"noirscape\" V.\n\n";

    std::string emuMMCStatus = printAndReturnEmuMMCstatus();

    // Print tip message
    std::cout << "Press - to toggle emuNAND status.\nPress + to exit.";

    return emuMMCStatus;
}

// Main program entrypoint
int main(int argc, char* argv[])
{
    // This example uses a text console, as a simple way to output text to the screen.
    // If you want to write a software-rendered graphics application,
    //   take a look at the graphics/simplegfx example, which uses the libnx Framebuffer API instead.
    // If on the other hand you want to write an OpenGL based application,
    //   take a look at the graphics/opengl set of examples, which uses EGL instead.
    consoleInit(NULL);

    std::string emuMMCStatus = printMainContent();
    // Main loop
    while (appletMainLoop())
    {
        // Scan all the inputs. This should be done once for each frame
        hidScanInput();

        // hidKeysDown returns information about which buttons have been
        // just pressed in this frame compared to the previous one
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if (kDown & KEY_PLUS)
            break; // break in order to return to hbmenu

        if (kDown & KEY_MINUS) {
            toggleEmuMMCVar(emuMMCStatus);
            emuMMCStatus = printMainContent();
        }
        // Your code goes here

        // Update the console, sending a new frame to the display
        consoleUpdate(NULL);
    }

    // Deinitialize and clean up resources used by the console (important!)
    consoleExit(NULL);
    return 0;
}
