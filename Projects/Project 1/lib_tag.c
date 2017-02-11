#include <lib.h>      // provides _syscall and message
#include <unistd.h>   // provides function prototype (see step 1 below)

int get_tag(int pid_in_question) {
   message m;
   m.m7_i1 = (int)getpid();   //Send own PID to check permissions
   m.m7_i2 = (int)getuid();   //Send UID to check if 0 (root)
   m.m7_i3 = pid_in_question; //Send PID of interest
   m.m7_i4 = -1;              //-1 = Not setting a new tag
   m.m7_i5 = -1;            //No new_pid

   int ret_val = _syscall(PM_PROC_NR, TAG_STUFF, &m);
   return ret_val;
}

int set_tag(int pid_in_question,int new_pid){
   message m;
   m.m7_i1 = (int)getpid();   //Send own PID to check permissions
   m.m7_i2 = (int)getuid();   //Send UID to check if 0 (root)
   m.m7_i3 = pid_in_question; //Send PID of interest
   m.m7_i4 = 1;               //1 = Setting a new tag
   m.m7_i5 = new_pid;         //Send replacement PID

   int ret_val = _syscall(PM_PROC_NR, TAG_STUFF, &m);
   return ret_val;
}
