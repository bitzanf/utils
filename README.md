## Collection of random utilities

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

