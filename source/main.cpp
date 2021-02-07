/* 
* emuMMC-Toggle - Toggle the emuMMC on and off.
* Copyright (C) 2019 - Valentijn "noirscape" V.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published
* by the Free Software Foundation at version 3 of the License.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
*
* In addition, the additional clauses 7b and 7c are in effect for this program.
*
* b) Requiring preservation of specified reasonable legal notices or
* author attributions in that material or in the Appropriate Legal
* Notices displayed by works containing it; or
*
* c) Prohibiting misrepresentation of the origin of that material, or
* requiring that modified versions of such material be marked in
* reasonable ways as different from the original version
*/

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
#define UFUCKEDUP "something is wrong"

std::string getStatusVar(std::string emummc_value)
{
    if (emummc_value == "0")
        return "Not active.";
    else if (emummc_value == "1")
        return "Active.";
    else
        return "Something went wrong or your emummc_enabled value is incorrect. Fix this manually before using emuMMC-Toggle.";
}

// Returns a pair containing a status var and the ini object.
std::string printAndReturnEmuMMCstatus()
{
    CSimpleIniA ini;
    ini.SetUnicode();
    ini.LoadFile(EMUMMCINI);

    std::string emummc_value = ini.GetValue("emummc", "enabled", UFUCKEDUP);
    std::cout << "emuMMC status: " << getStatusVar(emummc_value) << "\n\n\n";
    return emummc_value;
}

void toggleEmuMMCVar(std::string emuMMCStatus)
{
    CSimpleIniA ini;
    ini.SetUnicode();
    ini.LoadFile(EMUMMCINI);

    if (emuMMCStatus == "0")
        ini.SetValue("emummc", "enabled", "1");
    if (emuMMCStatus == "1")
        ini.SetValue("emummc", "enabled", "0");
    ini.SaveFile(EMUMMCINI);
}

std::string printMainContent()
{
    consoleClear();
    // Show welcome message
    std::cout << "Welcome to emuMMC-Toggle v1.1.1.\n\n(c) Valentijn \"noirscape\" V.\n\n";

    std::string emuMMCStatus = printAndReturnEmuMMCstatus();

    // Print tip message
    if (emuMMCStatus != UFUCKEDUP)
        std::cout << "Press - to toggle emuMMC status.\n";
    std::cout << "Press + to exit.\n";

    return emuMMCStatus;
}

// Main program entrypoint
int main(int argc, char* argv[])
{
    consoleInit(NULL);

    // Configure our supported input layout: a single player with standard controller styles
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);

    // Initialize the default gamepad (which reads handheld mode inputs as well as the first connected controller)
    PadState pad;
    padInitializeDefault(&pad);

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
        // Scan the gamepad. This should be done once for each frame
        padUpdate(&pad);

        // padGetButtonsDown returns the set of buttons that have been newly pressed in this frame compared to the previous one
        u64 kDown = padGetButtonsDown(&pad);

        if (kDown & HidNpadButton_Plus)
            break; // break in order to return to hbmenu

        if (kDown & HidNpadButton_Minus) {
            if (emuMMCStatus != UFUCKEDUP) {
                toggleEmuMMCVar(emuMMCStatus);
                emuMMCStatus = printMainContent();
            }
        }
        // Your code goes here

        // Update the console, sending a new frame to the display
        consoleUpdate(NULL);
    }

    // Deinitialize and clean up resources used by the console (important!)
    consoleExit(NULL);
    return 0;
}
