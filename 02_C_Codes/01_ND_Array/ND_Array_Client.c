
/**
 * @File: ND_Array_Client.c
 * @Brief: This file contains function calls to demonstrates N-Dimensional Array
 * @Author: Janhavi Sunil Khisti(janhavikhisti@gmail.com)
 * @Date: 07/06/2024 (Monday)
 */

// Headers
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "ND_Array.h"

// Constant Literals

#define NO_OF_ELEMENTS 6
#define NO_OF_1D_ARRAY 6
#define NO_OF_2D_ARRAY 6
#define NO_OF_3D_ARRAY 6
#define NO_OF_4D_ARRAY 5
#define NO_OF_5D_ARRAY 5
#define NO_OF_6D_ARRAY 4
#define NO_OF_7D_ARRAY 4
#define NO_OF_8D_ARRAY 3
#define NO_OF_9D_ARRAY 3
#define NO_OF_10D_ARRAY 2
#define NO_OF_11D_ARRAY 2
#define NO_OF_12D_ARRAY 2
#define NO_OF_13D_ARRAY 2
#define NO_OF_14D_ARRAY 2
#define NO_OF_15D_ARRAY 2


#define MAX 6

int var;

p_array_t my_4Darray = NULL;
p_array_t my_8Darray = NULL;
p_array_t my_16Darray = NULL;

int main(void)
{
	// Code

	/********************************************************************************************************************\

											4 Dimension Array 

	\********************************************************************************************************************/

	my_4Darray = create_array(	4,
								MAX,
								MAX,
								MAX,
								MAX);

	assert( NULL != my_4Darray );

	// Write values to 4D Array
	size_t count = 0;
	for( long index1 = 0; index1 < array_get_size_of_dimension(my_4Darray, 0); ++index1 )
		for( long index2 = 0; index2 < array_get_size_of_dimension(my_4Darray, 1); ++index2 )
			for( long index3 = 0; index3 < array_get_size_of_dimension(my_4Darray, 2); ++index3)
				for( long index4 = 0; index4 < array_get_size_of_dimension(my_4Darray, 3); ++index4)
					array_set_data(	my_4Darray, 
									(data_t)(++count), 
									index1,  
									index2, 
									index3, 
									index4);

	fprintf(stdout, "\n*************************************************************************\n");
	fprintf(stdout, "\n4D Array:\n");
	for( long index1 = 0; index1 < array_get_size_of_dimension(my_4Darray, 0); ++index1 )
		for( long index2 = 0; index2 < array_get_size_of_dimension(my_4Darray, 1); ++index2 )
			for( long index3 = 0; index3 < array_get_size_of_dimension(my_4Darray, 2); ++index3)
				for( long index4 = 0; index4 < array_get_size_of_dimension(my_4Darray, 3); ++index4)
					fprintf( stdout, 	" my_4Darray[%d][%d][%d][%d] = %lld\n", 
										index1,
										index2,
										index3,
										index4,
										(size_t)array_get_data(	my_4Darray, 
																index1, 
																index2, 
																index3, 
																index4));

	fprintf(stdout," First Element of 4D array = %lld\n", (long long)array_get_data(my_4Darray, 0, 0, 0, 0) );
	fprintf(stdout," Last Element of 4D array = %lld\n", (long long)array_get_data(my_4Darray, 5, 5, 5, 5) );

	fprintf(stdout, "\n*************************************************************************\n\n\n\n");
	array_destroy( &my_4Darray );



	/**********************************************************************************************************\
											8 Dimension Array
	\**********************************************************************************************************/

	my_8Darray = create_array(	8,
								4,
								4,
								4,
								4,
								4,
								4,
								4,
								4);
	assert( NULL != my_8Darray);

	//	Write Values to 8D array
	count = 0;
	for( long index1 = 0; index1 < array_get_size_of_dimension(my_8Darray, 0); ++index1 )
		for( long index2 = 0; index2 < array_get_size_of_dimension(my_8Darray, 1); ++index2 )
			for( long index3 = 0; index3 < array_get_size_of_dimension(my_8Darray, 2); ++index3)
				for( long index4 = 0; index4 < array_get_size_of_dimension(my_8Darray, 3); ++index4)
					for( long index5 = 0; index5 < array_get_size_of_dimension(my_8Darray, 4); ++index5)
						for( long index6 = 0; index6 < array_get_size_of_dimension(my_8Darray, 5); ++index6)
							for( long index7 = 0; index7 < array_get_size_of_dimension(my_8Darray, 6); ++index7)
								for( long index8 = 0; index8 < array_get_size_of_dimension(my_8Darray, 7); ++index8)
									array_set_data(	my_8Darray, 
													(data_t)(++count), 
													index1,  
													index2, 
													index3, 
													index4, 
													index5, 
													index6, 
													index7, 
													index8);

	fprintf(stdout, "\n*************************************************************************\n");
	fprintf(stdout, "\n8D Array:\n");
	for( long index1 = 0; index1 < array_get_size_of_dimension(my_8Darray, 0); ++index1 )
		for( long index2 = 0; index2 < array_get_size_of_dimension(my_8Darray, 1); ++index2 )
			for( long index3 = 0; index3 < array_get_size_of_dimension(my_8Darray, 2); ++index3)
				for( long index4 = 0; index4 < array_get_size_of_dimension(my_8Darray, 3); ++index4)
					for( long index5 = 0; index5 < array_get_size_of_dimension(my_8Darray, 4); ++index5)
						for( long index6 = 0; index6 < array_get_size_of_dimension(my_8Darray, 5); ++index6)
							for( long index7 = 0; index7 < array_get_size_of_dimension(my_8Darray, 6); ++index7)
								for( long index8 = 0; index8 < array_get_size_of_dimension(my_8Darray, 7); ++index8)
									fprintf( stdout, 	" my_8Darray[%d][%d][%d][%d][%d][%d][%d][%d] = %lld\n", 
										index1,
										index2,
										index3,
										index4,
										index5,
										index6,
										index7,
										index8,
										(size_t)array_get_data(	my_8Darray, 
																index1, 
																index2, 
																index3, 
																index4, 
																index5, 
																index6, 
																index7, 
																index8));

	fprintf(stdout," First Element of 8D array = %lld\n", (long long)array_get_data(my_8Darray, 0, 0, 0, 0, 0, 0, 0, 0) );
	fprintf(stdout," Last Element of 8D array = %lld\n", (long long)array_get_data(my_8Darray, 3, 3, 3, 3, 3, 3, 3, 3) );

	fprintf(stdout, "\n*************************************************************************\n\n");
	array_destroy( &my_8Darray );
					


	/**********************************************************************************************************\
											16 Dimension Array
	\**********************************************************************************************************/
	my_16Darray = create_array(	16, 
								NO_OF_15D_ARRAY, NO_OF_14D_ARRAY,
								NO_OF_13D_ARRAY, NO_OF_12D_ARRAY,
								NO_OF_11D_ARRAY, NO_OF_10D_ARRAY,
								NO_OF_9D_ARRAY, NO_OF_8D_ARRAY,
								NO_OF_7D_ARRAY, NO_OF_6D_ARRAY,
								NO_OF_5D_ARRAY, NO_OF_4D_ARRAY,
								NO_OF_3D_ARRAY, NO_OF_2D_ARRAY,
								NO_OF_1D_ARRAY, NO_OF_ELEMENTS);

	assert( NULL != my_16Darray);

	//	Write Values to 16D array
	count = 0;
	for( long index1 = 0; index1 < array_get_size_of_dimension(my_16Darray, 0); ++index1 )
		for( long index2 = 0; index2 < array_get_size_of_dimension(my_16Darray, 1); ++index2 )
			for( long index3 = 0; index3 < array_get_size_of_dimension(my_16Darray, 2); ++index3)
				for( long index4 = 0; index4 < array_get_size_of_dimension(my_16Darray, 3); ++index4)
					for( long index5 = 0; index5 < array_get_size_of_dimension(my_16Darray, 4); ++index5)
						for( long index6 = 0; index6 < array_get_size_of_dimension(my_16Darray, 5); ++index6)
							for( long index7 = 0; index7 < array_get_size_of_dimension(my_16Darray, 6); ++index7)
								for( long index8 = 0; index8 < array_get_size_of_dimension(my_16Darray, 7); ++index8)
									for( long index9 = 0; index9 < array_get_size_of_dimension(my_16Darray, 8); ++index9)
										for( long index10 = 0; index10 < array_get_size_of_dimension(my_16Darray, 9); ++index10)
											for( long index11 = 0; index11 < array_get_size_of_dimension(my_16Darray, 10); ++index11)
												for( long index12 = 0; index12 < array_get_size_of_dimension(my_16Darray, 11); ++index12)
													for( long index13 = 0; index13 < array_get_size_of_dimension(my_16Darray, 12); ++index13)
														for( long index14 = 0; index14 < array_get_size_of_dimension(my_16Darray, 13); ++index14)
															for( long index15 = 0; index15 < array_get_size_of_dimension(my_16Darray, 14); ++index15)
																for( long index16 = 0; index16 < array_get_size_of_dimension(my_16Darray, 15); ++index16)
													array_set_data(	my_16Darray, 
																	(data_t)(++count), 
																	index1,  index2, 
																	index3, index4, 
																	index5, index6, 
																	index7, index8, 
																	index9, index10, 
																	index11, index12,
																	index13, index14,
																	index15, index16);
	// Read Value
	fprintf(stdout, "\n*************************************************************************\n");
	// fprintf(stdout, "\n16D Array:\n");
	// for( long index1 = 0; index1 < array_get_size_of_dimension(my_16Darray, 0); ++index1 )
	// 	for( long index2 = 0; index2 < array_get_size_of_dimension(my_16Darray, 1); ++index2 )
	// 		for( long index3 = 0; index3 < array_get_size_of_dimension(my_16Darray, 2); ++index3)
	// 			for( long index4 = 0; index4 < array_get_size_of_dimension(my_16Darray, 3); ++index4)
	// 				for( long index5 = 0; index5 < array_get_size_of_dimension(my_16Darray, 4); ++index5)
	// 					for( long index6 = 0; index6 < array_get_size_of_dimension(my_16Darray, 5); ++index6)
	// 						for( long index7 = 0; index7 < array_get_size_of_dimension(my_16Darray, 6); ++index7)
	// 							for( long index8 = 0; index8 < array_get_size_of_dimension(my_16Darray, 7); ++index8)
	// 								for( long index9 = 0; index9 < array_get_size_of_dimension(my_16Darray, 8); ++index9)
	// 									for( long index10 = 0; index10 < array_get_size_of_dimension(my_16Darray, 9); ++index10)
	// 										for( long index11 = 0; index11 < array_get_size_of_dimension(my_16Darray, 10); ++index11)
	// 											for( long index12 = 0; index12 < array_get_size_of_dimension(my_16Darray, 11); ++index12)
	// 												for( long index13 = 0; index13 < array_get_size_of_dimension(my_16Darray, 12); ++index13)
	// 													for( long index14 = 0; index14 < array_get_size_of_dimension(my_16Darray, 13); ++index14)
	// 														for( long index15 = 0; index15 < array_get_size_of_dimension(my_16Darray, 14); ++index15)
	// 															for( long index16 = 0; index16 < array_get_size_of_dimension(my_16Darray, 15); ++index16)	
	// 												fprintf( stdout, 	" my_16Darray[%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d] = %lld\n", 
	// 																	index1, index2,
	// 																	index3, index4,
	// 																	index5, index6,
	// 																	index7, index8,
	// 																	index9, index10,
	// 																	index11, index12,
	// 																	index13, index14,
	// 																	index15, index16,
	// 																	(size_t)array_get_data(	my_16Darray, 
	// 																							index1, index2, 
	// 																							index3, index4, 
	// 																							index5, index6, 
	// 																							index7, index8, 
	// 																							index9, index10, 
	// 																							index11, index12,
	// 																							index13, index14,
	// 																							index15, index16) );
	


	fprintf(stdout," First Element of 16D array = %lld\n", (long long)array_get_data(my_16Darray, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0) );
	fprintf(stdout," Last Element of 16D array = %lld\n", (long long)array_get_data(my_16Darray, 
																		NO_OF_15D_ARRAY-1,
																		NO_OF_14D_ARRAY-1,
																		NO_OF_13D_ARRAY-1,
																		NO_OF_12D_ARRAY-1,
																		NO_OF_11D_ARRAY-1, 
																		NO_OF_10D_ARRAY-1, 
																		NO_OF_9D_ARRAY-1, 
																		NO_OF_8D_ARRAY-1, 
																		NO_OF_7D_ARRAY-1, 
																		NO_OF_6D_ARRAY-1, 
																		NO_OF_5D_ARRAY-1, 
																		NO_OF_4D_ARRAY-1, 
																		NO_OF_3D_ARRAY-1, 
																		NO_OF_2D_ARRAY-1, 
																		NO_OF_1D_ARRAY-1, 
																		NO_OF_ELEMENTS-1)); 

	fprintf(stdout, "\n*************************************************************************\n\n\n");

	printf("Please enter 0 to exit code : ");
	scanf("%d", &var);

	if( 0 == var)
	{
	// Destroy Array
	array_destroy( &my_16Darray );

	exit(SUCCESS);
	}
	else
	{
		printf("Enter 0 to exit code...\n\n");

	}
		
}
 

