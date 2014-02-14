STSuperUnamedHomework 1 Final.

Fangyu Xiong (Panda)

There are three folders, each of which contains one portion of the homework.

[hw1a]
Executable: out/hw1a
Files: main.c //main flow of the program
       intr_info.c/.h // contains helper function that handles 
                      // parsing interrupt info from the system
Usage: ./hw1a
       C-c to terminate.


[hw1b]
Executable: out/hw1b
Files: main.c //main flow of the program
       intr_info.c/.h // contains helper function that handles 
                      // parsing interrupt info from the system
Usage: ./hw1b [-s $interval] //$interval: unsigned int. Interval in second(s)
       C-c to terminate.
Default interval is set to 1s. Default interval will be used if custom interval is invalid or no custom interval is specified.

[microcat]
Executable:  out/microcat
Files: main.c //Program main
       cat.c  //cat function for reading and writing files
Usage: ./microcat [source_filename | - ]+ {[=]{[=]} [target_filename]}

        Multiple source file name can be included for displaying.
        If any file name is "-", microcat will read from stdin.
        "=" stands for redirection to file. File will be truncated if exists. 
        Redirecting to multiple files not supported. (According to cat behavior)
        "==" stands for redirection to file and append to that file. If file does not exist, a new file will be created.

        Any argument begyond target_filename will be dumped. (cat behavior)
    
        Example: ./microcat super.c haha.c = hoho.c
                 //Read from super.c and haha.c and concat them, write to hoho.c
                 
                 ./microcat == ioio.c
                 //Read from stdin and append to ioio.c
 
                 ./microcat yy.c - = some.c
                 //Concat content of yy.c and input from stdin and write them to                   a new file some.c


Bugs: no known bugs.
Memory leak detected for hw1a and hw1b. May because of system call since no "malloc" is ever explicitly called.
