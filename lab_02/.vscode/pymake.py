import os

# consts
CC = "gcc"
CFLAGS = "-std=c99 -Wall -Werror"
MAINTARG = "app.exe"
MAINSOURCE = "main.c"
CLEAN = '''clean: 
    rm *.o *.exe'''


def makefile_write_targ(file, targ, sources):
    file.write(targ + ': ')
    for source in sources:
        file.write(source + ' ')
    file.write('\n\t');
    file.write(CC + ' ' + CFLAGS + ' -c ')
    file.write('$^\n')

def makefile_write_app(file, targ, sources):
    file.write(targ + ': ')
    for source in sources:
        file.write(source + ' ')
    file.write('\n\t');
    file.write(CC + ' ' + CFLAGS + ' -o $@ ')
    file.write('$^\n')
    

makefile = open("./source/Makefile", "w")

makefile.write('CC=' + CC + '\n')
makefile.write('CFLAGS=' + CFLAGS + '\n')

source_list = os.listdir('./source')
object_sources = list(map(lambda x: x[:x.find('.')] + '.o', filter(lambda x: x[-2:] == '.c', source_list)))

makefile_write_app(makefile, MAINTARG, object_sources)

for file in source_list:
    if file[-2:] == '.c' and file != 'main.c ' :
        makefile_write_targ(makefile, file[:file.find('.')] + '.o', (file, ))

makefile.write(CLEAN)

makefile.close();

