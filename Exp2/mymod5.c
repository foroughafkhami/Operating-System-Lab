#include<linux/init.h>
#include <linux/kernel.h> 
#include <linux/module.h> 
#include <linux/list.h>
#include <linux/string.h>
#include <linux/types.h>
#include <linux/slab.h>
int add_element(void){
	static LIST_HEAD(BirthInfo_head);
	struct BirthInfo{
		int day;
		int month;
		int year;
		char city[20];
		struct list_head list;
	};
	struct BirthInfo *student;
	student = kmalloc(sizeof(student), GFP_KERNEL);
	student->day = 17;
	student->month= 2;
	student->year = 1380;
	strcpy(student->city ,"Tehran");
	INIT_LIST_HEAD (&student-> list);
	list_add_tail(&student ->list,&BirthInfo_head);
	
	student = kmalloc(sizeof(student), GFP_KERNEL);
	student->day = 29;
	student->month= 9;
	student->year = 1378;
	strcpy(student->city ,"Tehran");
	INIT_LIST_HEAD (&student-> list);
	list_add_tail(&student ->list,&BirthInfo_head);
	
	struct BirthInfo *ptr;
	list_for_each_entry(ptr,&BirthInfo_head,list){
		printk(KERN_INFO "Data: %d/%d/%d ,%s",ptr->day,ptr->month,ptr->year,ptr->city);
	}
	return 0;
}
/* this function is called when the module is loaded*/ 
int   simple_init(void) { 
	
	printk(KERN_INFO "Loading Module\n" );  
	add_element();
	return 0; } 
/* this function is called when the module is removed*/
void simple_exit(void){ 	
	printk(KERN_INFO "Removing Module\n"); } /* Macros for registering module entry and exit points.*/  	
module_init(simple_init);	
module_exit(simple_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("simple module");
 MODULE_AUTHOR("SGG");
