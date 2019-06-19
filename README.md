## emuMMC-Toggle

This very simple homebrew just flips the number in `emummc/emummc.ini` that determines if Atmosphere should load emuMMC.

### Idea

Removes the need for SD pulls to reboot from emuMMC to sysMMC or vice versa if using fusee-primary.

### Usage

Open the `.nro` using the HBL.

- Press `-` to toggle emuMMC on or off.
- Press `+` to exit the application.

Don't attempt to toggle emuMMC if it says something is wrong. That's bad behavior.

### Building

- Install devKitPro
- Clone _recursively_
- Run `make`
- ???
- Profit

### Credits

- Dax for recommending `simpleini` library.

### License

```c
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
```