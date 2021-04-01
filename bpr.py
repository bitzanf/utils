import subprocess, re, os
from multiprocessing import cpu_count
from sys import argv

blender = 'blender' #path to blender executable
ffmpeg = 'ffmpeg'   #path to ffmpeg executable

def render(n_parts, startframe, endframe, soubor):
    step = int((endframe - startframe) / n_parts)
    
    ps = []
    i = 0
    for i in range(startframe, endframe - step, step):
        ps.append(subprocess.Popen(f'{blender} -b {soubor} -E CYCLES -s {i} -e {i+step-1} -a'))
    ps.append(subprocess.Popen(f'{blender} -b {soubor} -E CYCLES -s {i+step} -e {endframe} -a'))

    for p in ps:
        p.wait()


def invokeFFmpeg(outname, partsname='parts.txt'):
    filelist = os.listdir(os.getcwd())
    partsfile = open(partsname, 'w')

    for s in filelist:
        match = re.match('\d{4}-\d{4}\.mp4', s)
        if match != None:
            partsfile.write('file \'' + match.group(0) + '\'\n')

    partsfile.close()
    subprocess.call(f'{ffmpeg} -f concat -i {partsname} -c copy {outname.split(".")[0]}.mp4')


def main():
    if len(argv) == 1:
        filelist = os.listdir(os.getcwd())
        f = ""
        for s in filelist:
            mm = re.match('.*\.blend$', s)
            if mm != None:
                f = mm.group(0)
                print(f'found file: \'{f}\'')
                break
        if len(f) == 0:
            f = input('name of file: ')
        sf = int(input('starting frame: '))
        ef = int(input('ending frame: '))
        render(cpu_count(), sf, ef, f)
    elif len(argv) == 4:
        f = argv[1]
        render(cpu_count(), int(argv[2]), int(argv[3]), f)
    else:
        print(f'usage: {argv[0]} [file startframe endframe]')
        return
    
    invokeFFmpeg(f)


if __name__ == "__main__": main()
