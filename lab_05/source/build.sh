echo Hello;
cd ./source;
make clean;
make;
../bin/app.exe
echo DONE
# xterm -e 'pwd;valgrind ../bin/app.exe; read';
