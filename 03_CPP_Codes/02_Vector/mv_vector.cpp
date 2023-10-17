/*
	Total lines of code = (header) 430 + (client) 101 = 531
*/

// Headers
#include	<iostream>

#include	"mv_vector.hpp"

//	Global Object

MVVector<long>* pvector_1 = NULL;
MVVector<long>* pvector_2 = NULL;


int main(void)
{
	// Code
	pvector_1 = new MVVector<long>();
	pvector_2 = new MVVector<long>();

	for( long le = 0; le < 10; ++le )
	{
		pvector_1->PushBack( (le+1) * 12 );
	}

	pvector_2->PushBackV( 10, 11, 22, 33, 44, 55, 66, 77, 88, 99, 111);

	std::cout << std::endl << std::endl;

	// std::cout << "Vector:" << std::endl;
	/*for( long le = 0; le < pvector->Size(); ++le )
	{
		std::cout 	<< "pvector[" 
					<< le
					<< "] = "
					<< (*pvector)[le]
					<< std::endl;
	}*/

	 std::cout << "Vector Using Operator << :" << std::endl << (*pvector_1);
	 std::cout << "Vector Using Operator << :" << std::endl << (*pvector_2);

	// std::cout << "Vector Using Operator using pointer << :" << std::endl << pvector;

	// std::cout << "Using Forward Traversal" << std::endl;
	// pvector->ForwardTraversal();

	// std::cout << "Using Reverse Traversal" << std::endl;
	// pvector->ReverseTraversal();

	//std::cout << "Vector Using Iterator:" << std::endl;
	//for( MVVector<long>::Iterator itr = pvector->begin(); itr != pvector->end(); ++itr ) 
	/*for( auto itr = pvector->begin(); itr != pvector->end(); ++itr ) 
	{
		std::cout << *itr << std::endl;
	}*/

	/*std::cout << std::endl << std::endl;
	std::cout << "Vector Pop Back:"<< std::endl;
	std::cout << "Popped Data = " << pvector->PopBack() << std::endl;
	std::cout << "Popped Data = " << pvector->PopBack() << std::endl;
	std::cout << "Popped Data = " << pvector->PopBack() << std::endl;
	std::cout << "Popped Data = " << pvector->PopBack() << std::endl;

	std::cout << std::endl << std::endl;
	//std::cout << "Vector:" << std::endl;
	/*for( long le = 0; le < pvector->Size(); ++le )
	{
		std::cout 	<< "pvector[" 
					<< le
					<< "] = "
					<< (*pvector)[le]
					<< std::endl;
	}*/
	
	/*std::cout << "Vector Using Operator << :" << std::endl << (*pvector);*/

	//std::cout << "Vector Using Iterator:" << std::endl;
	/*//for( MVVector<long>::Iterator itr = pvector->begin(); itr != pvector->end(); ++itr ) 
	for( auto itr = pvector->begin(); itr != pvector->end(); ++itr ) 
	{
		std::cout << *itr << std::endl;
	}*/

	pvector_1->vector_merge(pvector_2);

	std::cout << std::endl << "After Merge :" << std::endl;
	std::cout << "Vector 1 << :" << std::endl << (*pvector_1);
	std::cout << "Vector 2 << :" << std::endl << (*pvector_2);

	delete(pvector_1);
	pvector_1 = NULL;

	delete(pvector_2);
	pvector_2 = NULL;

	return(SUCCESS);

}

