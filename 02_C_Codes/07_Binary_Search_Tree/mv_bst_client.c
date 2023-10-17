

// Headers
#include	<stdio.h>
#include	<stdlib.h>

#include	"mv_bst.h"

tree_t	tree = NULL;

status_t	compare_data(data_t data1, data_t data2)
{
	// Code
	if( (long long)data1 == (long long)data2 )
		return(STATUS_EQUAL);
	else if( (long long)data1 < (long long)data2 )
		return(STATUS_LESSER);
	else 
		return(STATUS_GREATER);
}

void	show_data(data_t data)
{
	// Code
	fprintf(stdout, "%lld", (long long)data);
}

void	delete_data(data_t data)
{
	// Code
	fprintf(stdout, "%lld", (long long)data);
}

int main(void)
{
	// Code

	tree = create_tree();

	mv_bst_insert(tree, (data_t)(long long)500, compare_data);
	mv_bst_insert(tree, (data_t)(long long)250, compare_data);
	mv_bst_insert(tree, (data_t)(long long)900, compare_data);
	mv_bst_insert(tree, (data_t)(long long)120, compare_data);
	mv_bst_insert(tree, (data_t)(long long)400, compare_data);
	mv_bst_insert(tree, (data_t)(long long)200, compare_data);
	mv_bst_insert(tree, (data_t)(long long)150, compare_data);
	mv_bst_insert(tree, (data_t)(long long)300, compare_data);
	mv_bst_insert(tree, (data_t)(long long)330, compare_data);
	mv_bst_insert(tree, (data_t)(long long)360, compare_data);
	mv_bst_insert(tree, (data_t)(long long)700, compare_data);
	mv_bst_insert(tree, (data_t)(long long)1000, compare_data);
	mv_bst_insert(tree, (data_t)(long long)800, compare_data);
	mv_bst_insert(tree, (data_t)(long long)750, compare_data);
	mv_bst_insert(tree, (data_t)(long long)980, compare_data);
	mv_bst_insert(tree, (data_t)(long long)930, compare_data);

/*	mv_bst_insert(tree, (data_t)(long long)100, compare_data);
	mv_bst_insert(tree, (data_t)(long long)50, compare_data);
	mv_bst_insert(tree, (data_t)(long long)400, compare_data);
	mv_bst_insert(tree, (data_t)(long long)25, compare_data);
	mv_bst_insert(tree, (data_t)(long long)75, compare_data);
	mv_bst_insert(tree, (data_t)(long long)20, compare_data);
	mv_bst_insert(tree, (data_t)(long long)10, compare_data);
	mv_bst_insert(tree, (data_t)(long long)22, compare_data);
	mv_bst_insert(tree, (data_t)(long long)150, compare_data);
	mv_bst_insert(tree, (data_t)(long long)5000, compare_data);
	mv_bst_insert(tree, (data_t)(long long)250, compare_data);
	mv_bst_insert(tree, (data_t)(long long)200, compare_data);*/


	mv_bst_inorder_recursive(tree, show_data);
	mv_bst_inorder_non_recursive(tree, show_data);

	mv_bst_preorder_recursive(tree, show_data);
	mv_bst_preorder_non_recursive(tree, show_data);
	
	mv_bst_postorder_recursive(tree, show_data);
	mv_bst_postorder_non_recursive(tree, show_data);

	delete_data( mv_bst_remove(tree, (data_t)(long long)500, compare_data) );
	printf("\n");

	mv_bst_inorder_recursive(tree, show_data);
	mv_bst_inorder_non_recursive(tree, show_data);

	mv_bst_preorder_recursive(tree, show_data);
	mv_bst_preorder_non_recursive(tree, show_data);
	
	mv_bst_postorder_recursive(tree, show_data);
	mv_bst_postorder_non_recursive(tree, show_data);

	mv_bst_destroy_non_recursive(&tree, delete_data);

	exit(SUCCESS);

}



