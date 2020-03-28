# CS550Assignment2
## Name: Bo Yan

-----------------------------------------------------------------------
-----------------------------------------------------------------------

## Description:
Files provided:

    process_list.c
    user.c
    Makefile
    
Usage of Makefile:

    sudo make
        This will create
            process_list.ko along with all other files
            user
    sudo make clean
        This will remove all files except the two source code files and Makefile
        
Usage of process_list.ko and user:
    
    sudo insmod process_list.ko
    sudo ./user
    sudo rmmod process_list.ko
    
Design:
    
    1. For kernel module:
        use miscdevice
        define custom read() function by:
            using for_each_process() to grab information from task_struct
            using copy_to_user() to pass result
    2. For user level code:
        simply use open() and read() to read from miscdevice
        use bitwise and to get state string
    
Exception handling:

    All system call exceptions catched will print the perror messages.
    Other exceptions catched will print the custom error messages.

Assumptions:

    total number of processes won't achieve 2500 
        
Reference:

    Slides Kernel Modules from professor
    https://elixir.bootlin.com/linux/latest/Source
    
