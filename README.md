# TermKeyboard
This program injects keyboard events from your terminal into the OS.

Use case: You have a linux box, and have connected it to a monitor, but you don't have a keyboard to connect to it. You can ssh into it from another computer (or phone/tablet), run this program and use its keyboard to send keyevents to your linux box.

Modifier keys (CTRL and ALT) work only with only the a-z keys (e.g., ALT+F4 won't work.. )
If you're missing functionality of any key, open an issue.

===How to compile/run===
Download libtermkey from https://github.com/neovim/libtermkey
Compile it with "make". Install any missing libraries if the compilation fails.
"make install".
Download this git repo.
Compile this code ("make")
Make sure you've loaded the uinput module ("modprobe uinput") with root priviles
Run the program (./kbd) with root privileges
