# TermKeyboard
This program injects keyboard events from your terminal into the OS.

### When to use this program
You have a linux box connected to a monitor but don't have a physical keyboard to connect to it or don't want to use a physical keyboard.

### How to use
ssh (or telnet or any other fancy protocol) into the linux box on which you want to simulate keyboard events from another computer/phone/tablet/whatever and run this program. Whatever you type in the program will be sent to the linux box! To quit the program, Type 'Ctrl+a' and 'q'.

### How to compile/run
- Download libtermkey from https://github.com/neovim/libtermkey
- Compile it with "make". Install any missing libraries if the compilation fails.
- "make install".
- Download this git repo.
- Compile this code ("make")
- Make sure you've loaded the uinput module ("modprobe uinput") with root priviles
- Run the program (./kbd) with root privileges

#####Note
Modifier keys (CTRL and ALT) work only with only the a-z keys (e.g., ALT+F4 won't work).
If you're missing functionality of any key, open an issue.

