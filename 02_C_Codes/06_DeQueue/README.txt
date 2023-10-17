
Directory : 
			D:\AB_DS Batch 1\Git_Codes\AB_DS_Janhavi_Khisti\01_C_Datastructures\05_DeQueue_Version3\01_TODO_Version1
			
Files :
		1) mv_queue.h
		2) mv_queue.c
		3) mv_queue_client.c
		4) mv_dcll.h
		5) mv_dcll.c

Description :

1) mv_dequeue.h  : 
						This header files contains all the declaration of interface functions
			 			 of 'mv_dequeue'

2) mv_dequeue.c : 
	|					This Source file contains all the function definitions declared in mv_dequeue.h
	|
	|
	|_>	Updation :
					1) New function is added 
						  i.e check_deque_conditions that takes pointer to deque and ERROR CODES
						  check_deque_conditions function is specifically designed to make error handling code more redundant
						  by simply providing ERROR CODES

					2) DeQueue here is implemented using Doubly Circular Linked List, on server 
						side queue is using Doubly Circular Linked List to enque, deque, print and destory 
						data in dequeue.

3) mv_dequeue_client.c : 
						This source file contains interface function calls made 
						by client in order to manage generic data on queueue data structure and 
						therefore needs callback function as client is the only who
	  					knows how to represent data on console and in memory
    
4) mv_dcll.h  : This header files contains all the declaration of interface functions of 'mv_dcll'

5) mv_dcll.c : This Source file contains all the function definitions declared in mv_dcll.h
