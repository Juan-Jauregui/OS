//For Project 1
#include <stdio.h>
#include "pm.h"      //For global message passing
#include "mproc.h"  // for process table mproc


int tag_stuff(){
   int caller_pid = m_in.m7_i1;
   int caller_uid = m_in.m7_i2;
   int pid_in_question = m_in.m7_i3;
   int set_or_nah = m_in.m7_i4;     //1 or -1
   int new_tag = m_in.m7_i5;


   //If caller PID is same as PID in question, they can get the tag
   int can_get_it = 0;
   if((caller_pid == pid_in_question) || caller_uid == 0)
      can_get_it = 1;

   //If the caller's UID is 0 (root), they can set the tag
   int can_set_it = 0;
   if(caller_uid == 0){
      can_set_it = 1;
   }

   struct mproc *proc_entry = find_proc(pid_in_question);
   if(proc_entry != NULL){
      if(can_get_it == 1 && set_or_nah == -1){
         //get the tag
         return proc_entry->tag;

      } else if(can_set_it == 1 && set_or_nah == 1){
         //set the tag
         proc_entry->tag = new_tag;
         return new_tag;
      }
   } else {
      return -1;
   }
}
