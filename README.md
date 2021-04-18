# Collection of random utilities

## bpr.py - blender parallel rendering
Because reasons, blender can't render video on more than 1 core, but you can spin up more instances of blender at the same time. That's exactly what this small script does.  
It does so by starting as many main instances as you have cores (+1 for a few last frames) and then splicing the parts with ffmpeg.  
*It's a good idea to copy the entire project into a separate folder to avoid collisions with other projects/rendered parts.*

#### Requirements
- ffmpeg
- blender
> there are 2 global variables where you can set the path to the needed executables

#### Usage
- `python bpr.py`  
    This will try to find a .blend file, if it is not found you will have to input the filename manually  
    You will also have to specify the starting and ending frames of the rendered scene
- `python bpr.py project.blend 0 100`  
    This will render frames **0** to **100** in the file `project.blend` and not prompt for any input

&nbsp;
## lauchVSCode - launch vscode configured for C using MSVC
VSCode by default doesn't have paths to the compiler (cl.exe) and includes, which becomes very annoying very quickly. This program first launches the "developer command prompt" and from it launches vscode **in your project folder**, so all the includes are set and ready to compile.

#### Requirements
- VSCode (obviously)
- Visual Studio 2019 with c++ extensions (for the compiler suite and building)
> the file `launchVSCode.cpp` is encoded in code page 1250, non-ascii characters used only for 1 line

#### Usage
- `launchVSCode`  
    This just opens the windows folder selection dialog in the last folder you used
- `launchVSCode -d="<path>"`  
    This allows you to set a default starting folder for the dialog as `<path>`. This can for example be your common projects folder.