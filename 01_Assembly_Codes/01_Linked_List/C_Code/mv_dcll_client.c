
/**
 * File   : mv_dcll_client.c
 * Brief  : Contains client side C code for DCLL 
 * Author : Janhavi Khisti(janhavikhisti@gmail.com)
 * Date   : 02/02/2023
 */

#include	<stdio.h>
#include	<stdlib.h>

#include	"mv_dcll.h"


p_mv_dcll_t	plist = NULL;

ret_t	compareproc(data_t data1, data_t data2)
{
	if( (long long)data1 == (long long)data2 )
		return(SUCCESS);

	return(FAILURE);
}

void printdata(data_t data)
{
	fprintf(stdout, "{%lld}->", (long long)data);
}

void deletedata(data_t data)
{
	fprintf(stdout, "Deleting : %lld\n", (long long)data);
}

int main(void)
{
	// Code

	plist = create_list();

	// Insert Front
	for( long le = 0; le < 20; ++le )
	{
		list_insert_front(plist, (data_t)(long long) ((le+1) * 4) );
	}

	fprintf(stdout, "\nAfter insert front:\n");
	list_show(plist, printdata);

	// Insert Back
	for( long le = 0; le < 20; ++le )
	{
		list_insert_back(plist, (data_t)(long long) ((le+1) * 23) );
	}

	fprintf(stdout, "\nAfter insert back:\n");
	list_show(plist, printdata);

	list_insert_before(plist, (data_t)(long long)1234, (data_t)(long long)4, compareproc);
	// list_insert_before(plist, (data_t)(long long)5678, (data_t)(long long)138, compareproc);
	// list_insert_before(plist, (data_t)(long long)9999, (data_t)(long long)322, compareproc);
	// list_insert_before(plist, (data_t)(long long)2222, (data_t)(long long)460, compareproc);
	// list_insert_before(plist, (data_t)(long long)5555, (data_t)(long long)6666, compareproc);

	fprintf(stdout, "\nAfter insert before:\n");
	list_show(plist, printdata);

	list_insert_after(plist, (data_t)(long long)4321, (data_t)(long long)1234, compareproc);
	// list_insert_after(plist, (data_t)(long long)8765, (data_t)(long long)5678, compareproc);
	// list_insert_after(plist, (data_t)(long long)1111, (data_t)(long long)9999, compareproc);
	// list_insert_after(plist, (data_t)(long long)5555, (data_t)(long long)2222, compareproc);
	// list_insert_after(plist, (data_t)(long long)3333, (data_t)(long long)6666, compareproc);

	fprintf(stdout, "\nAfter insert after:\n");
	list_show(plist, printdata);

	list_insert_at(plist, (data_t)(long long)5555, 0);
	// list_insert_at(plist, (data_t)(long long)4444, 15);
	// list_insert_at(plist, (data_t)(long long)1616, 22);
	// list_insert_at(plist, (data_t)(long long)2323, 99);
	// list_insert_at(plist, (data_t)(long long)6767, 4);

	fprintf(stdout, "\nAfter insert at:\n");
	list_show(plist, printdata);

	//	Remove HW

	// Remove Front 
	list_remove_front(plist);

	fprintf(stdout, "\nAfter remove front:\n");
	list_show(plist, printdata);


	// Remove Back
	list_remove_back(plist);

	fprintf(stdout, "\nAfter remove back:\n");
	list_show(plist, printdata);


	// Remove Before
	list_remove_before(plist,(data_t)(long long) 5, compareproc);

	fprintf(stdout, "\nAfter remove before:\n");
	list_show(plist, printdata);


	// Remove After
	list_remove_after(plist, (data_t)(long long) 7, compareproc);

	fprintf(stdout, "\nAfter remove after:\n");
	list_show(plist, printdata);


	// Remove At
	list_remove_at(plist, 5);

	fprintf(stdout, "\nAfter remove at:\n");
	list_show(plist, printdata);


	// Data at
	fprintf(stdout, "\nData at:\n");
	printdata(list_data_at(plist, 8));


	// list size
	fprintf(stdout, "\nList Size:\n");
	printdata(list_size(plist));


	list_destroy(&plist, deletedata);

	exit(SUCCESS);
}

