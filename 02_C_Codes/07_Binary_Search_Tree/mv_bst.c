
//  Headers
#include    <stdio.h>
#include    <stdlib.h>

#include    "mv_bst.h"
#include    "mv_dcll.h"

//  Constant Literals and Macros

#define ERROR_LOG(error_str) (fprintf(stderr, "ERROR: %s\n", error_str))

// BST Helper Functions
static  void*   Xmalloc(size_t no_of_bytes)
{
    // Code
    void* p = malloc(no_of_bytes);

    if( NULL == p )
    {
        ERROR_LOG("Out Of Memory");
        exit(FAILURE);
    }

    return(p);
}

static p_tree_node_t create_node(data_t new_data)
{
    // Code
    p_tree_node_t pnode = (p_tree_node_t)Xmalloc(SIZE_NODE);

    // Set values to members of node
    pnode->data = new_data;

    pnode->parent = NULL;
    pnode->left = NULL;
    pnode->right = NULL;

    return(pnode);
}

static p_tree_node_t locate_node(p_tree_node_t root, data_t e_data, COMPAREDATAPROC pcomparedataproc)
{
    // Code
    p_tree_node_t prunner = root;

    //  This Loop finds the data to be removed
    while( prunner )
    {
        status_t status = pcomparedataproc(e_data, prunner->data);

        if( STATUS_EQUAL == status )
            break;

        if( STATUS_LESSER == status )
        {
            prunner = prunner->left;
        }
        else
        {
            prunner = prunner->right;
        }
    }

    return(prunner);
}

static p_tree_node_t predecessor(p_tree_node_t node)
{
    // Code
    p_tree_node_t prunner = node->left;

    while( prunner->right )
        prunner = prunner->right;

    return(prunner);
}

static p_tree_node_t successor(p_tree_node_t node)
{
    // Code
    p_tree_node_t prunner = node->right;

    while( prunner->left )
        prunner = prunner->left;

    return(prunner);
}

static ret_t generic_tree_insert(tree_t tree, data_t new_data, COMPAREDATAPROC pcomparedataproc)
{
    // Code

    p_tree_node_t prunner = tree->root;

    while( 1 )
    {
        status_t status = pcomparedataproc(new_data, prunner->data);

        if( STATUS_EQUAL == status )
        {
            ERROR_LOG("Data Already Present");
            return(FAILURE);
        }

        if( STATUS_LESSER == status )
        {
            // LEFT 
            if( NULL == prunner->left )
            {
                // Add New Data to left
                prunner->left = create_node(new_data);
                prunner->left->parent = prunner;
                break;
            }
            prunner = prunner->left;
        }
        else
        {
            // RIGHT
            if( NULL == prunner->right )
            {
                // Add New Data to right
                prunner->right = create_node(new_data);
                prunner->right->parent = prunner;
                break;
            }
            prunner = prunner->right;
        }
    }

    tree->no_of_elements++;

    return(SUCCESS);
}

static data_t generic_tree_remove(tree_t tree, data_t e_data, COMPAREDATAPROC pcomparedataproc)
{
    // Code

    p_tree_node_t prunner = locate_node(tree->root, e_data, pcomparedataproc);   //  Locate the TO BE DELETED node.
    data_t to_return_data = NULL;

    if( NULL == prunner )
    {
        ERROR_LOG("Existing Data Not Found.");
        return((data_t)NULL);
    }

    // CASE 1: No Children present
    if( NULL == prunner->left   &&
        NULL == prunner->right )
    {
        to_return_data = prunner->data;
    }

    // CASE 2: prunner have LEFT CHILD
    else if( NULL != prunner->left )
    {
        p_tree_node_t p_predecessor = predecessor(prunner);

        to_return_data = prunner->data;
        prunner->data = p_predecessor->data;

        prunner = p_predecessor;
    }

    //  CASE 3: prunner have RIGHT CHILD
    else if( NULL != prunner->right )
    {
        p_tree_node_t p_successor = successor(prunner);

        to_return_data = prunner->data;
        prunner->data = p_successor->data;

        prunner = p_successor;
    }

    // Here We Do Actual REMOVING from TREE Heirarchy
    if( NULL == prunner->parent )   // This means prunner is root
    {
        tree->root = NULL;
    }
    else if( prunner == prunner->parent->left )
    {
        if( prunner->right )
            prunner->parent->left = prunner->right;
        else
            prunner->parent->left = prunner->left;
    }
    else
    {
        if( prunner->right )
            prunner->parent->right = prunner->right;
        else
            prunner->parent->right = prunner->left;
    }

    if( prunner->left )
        prunner->left->parent = prunner->parent;
    else if( prunner->right )
        prunner->right->parent = prunner->parent;

    //  Here we delete the node
    prunner->data = NULL;
    prunner->left = NULL;
    prunner->right = NULL;
    prunner->parent = NULL;
    free(prunner);
    prunner = NULL;

    tree->no_of_elements--;

    return(to_return_data);
}

static void generic_inorder_recursive(p_tree_node_t node, SHOWDATAPROC pshowdataproc)
{
    // Code
    if( node->left )
        generic_inorder_recursive(node->left, pshowdataproc);

    fprintf(stdout,"{");
    pshowdataproc(node->data);
    fprintf(stdout,"}->");

    if( node->right )
        generic_inorder_recursive(node->right, pshowdataproc);
}

static void generic_preorder_recursive(p_tree_node_t node, SHOWDATAPROC pshowdataproc)
{
    // Code
    fprintf(stdout,"{");
    pshowdataproc(node->data);
    fprintf(stdout,"}->");

    if( node->left )
        generic_preorder_recursive(node->left, pshowdataproc);

    if( node->right )
        generic_preorder_recursive(node->right, pshowdataproc);
}

static void generic_postorder_recursive(p_tree_node_t node, SHOWDATAPROC pshowdataproc)
{
    // Code
    if( node->left )
        generic_postorder_recursive(node->left, pshowdataproc);

    if( node->right )
        generic_postorder_recursive(node->right, pshowdataproc);

    fprintf(stdout,"{");
    pshowdataproc(node->data);
    fprintf(stdout,"}->");
}

static void generic_postorder_delete_recursive(p_tree_node_t node, DELETEDATAPROC pdeletedataproc)
{
    // Code
    if( node->left )
        generic_postorder_delete_recursive(node->left, pdeletedataproc);

    if( node->right )
        generic_postorder_delete_recursive(node->right, pdeletedataproc);

    pdeletedataproc(node->data);
}

static int height(p_tree_node_t node)
{
    // Code
    if( NULL == node )
    {
        return(0);
    }
    else
    {
        int left_height = height(node->left);
        int right_height = height(node->right);

        if( left_height >= right_height )
            return( left_height+1 );
        else
            return( right_height+1 );
    }
}

//  PREORDER: ROOT LEFT RIGHT
static void generic_preorder_non_recursive(p_tree_node_t root, SHOWDATAPROC pshowdataproc)
{
    // Code
    
    p_mv_dcll_t stack = create_doubly_circular_list();
    p_tree_node_t prunner = root;

    mv_dcll_insert_front(stack, prunner);

    fprintf(stdout, "Tree PreOrder Iterative Traversal:\n");
    fprintf(stdout, "{START}->");
    while( !mv_dcll_empty(stack) )
    {
        while( prunner )
        {
            fprintf(stdout,"{");
            pshowdataproc(prunner->data);
            fprintf(stdout,"}->");

            if( prunner->left )
                prunner = prunner->left;
            else
                break;

            mv_dcll_insert_front(stack, prunner);
        }

        prunner = (p_tree_node_t)mv_dcll_remove_front(stack);
        prunner = prunner->right;
        
        if( prunner )
        {
            mv_dcll_insert_front(stack, prunner);
        }
    }
    fprintf(stdout, "{END}\n\n");

    mv_dcll_destroy(&stack, NULL);
    stack = NULL;
}

//  INORDER: LEFT ROOT RIGHT
static void  generic_inorder_non_recursive(p_tree_node_t root, SHOWDATAPROC pshowdataproc)
{
    // Code
    
    p_mv_dcll_t stack = create_doubly_circular_list();
    p_tree_node_t prunner = root;

    mv_dcll_insert_front(stack, prunner);

    fprintf(stdout, "Tree InOrder Iterative Traversal:\n");
    fprintf(stdout, "{START}->");
    while( !mv_dcll_empty(stack) )
    {
        while( prunner )
        {
            if( prunner->left )
                prunner = prunner->left;
            else
                break;

            mv_dcll_insert_front(stack, prunner);
        }

        prunner = (p_tree_node_t)mv_dcll_remove_front(stack);

        fprintf(stdout,"{");
        pshowdataproc(prunner->data);
        fprintf(stdout,"-");
        fprintf(stdout,"%d", height(prunner));
        fprintf(stdout,"}->");

        prunner = prunner->right;
        
        if( prunner )
        {
            mv_dcll_insert_front(stack, prunner);
        }
    }
    fprintf(stdout, "{END}\n\n");

    mv_dcll_destroy(&stack, NULL);
    stack = NULL;
}

//  POSTORDER: LEFT RIGHT RIGHT
static void generic_postorder_non_recursive(p_tree_node_t root, SHOWDATAPROC pshowdataproc)
{
    // Code
    
    p_mv_dcll_t stack = create_doubly_circular_list();
    p_tree_node_t prunner = root;

    if( prunner->right )
        mv_dcll_insert_front(stack, prunner->right);
    
    mv_dcll_insert_front(stack, prunner);

    prunner = prunner->left;  

    fprintf(stdout, "Tree PostOrder Iterative Traversal:\n");
    fprintf(stdout, "{START}->");
    while( !mv_dcll_empty(stack) )
    {
        while( prunner )
        {
            if( prunner->right )
                mv_dcll_insert_front(stack, prunner->right);
            
            mv_dcll_insert_front(stack, prunner);

            prunner = prunner->left;            
        }

        prunner = mv_dcll_remove_front(stack);

        if( !mv_dcll_empty(stack) && mv_dcll_get_head(stack) == prunner->right )
        {
            p_tree_node_t temp = mv_dcll_remove_front(stack);
            mv_dcll_insert_front(stack, prunner);
            prunner = temp;
        }
        else
        {
            fprintf(stdout,"{");
            pshowdataproc(prunner->data);
            fprintf(stdout,"}->");
            prunner = NULL;
        }
    }
    fprintf(stdout, "{END}\n\n");

    mv_dcll_destroy(&stack, NULL);
    stack = NULL;
}

static void generic_postorder_delete_iterative(p_tree_node_t root, DELETEDATAPROC pdeletedataproc)
{
    // Code
    
    p_mv_dcll_t stack = create_doubly_circular_list();
    p_tree_node_t prunner = root;

    if( prunner->right )
        mv_dcll_insert_front(stack, prunner->right);
    
    mv_dcll_insert_front(stack, prunner);

    prunner = prunner->left;  

    while( !mv_dcll_empty(stack) )
    {
        while( prunner )
        {
            if( prunner->right )
                mv_dcll_insert_front(stack, prunner->right);
            
            mv_dcll_insert_front(stack, prunner);

            prunner = prunner->left;            
        }

        prunner = mv_dcll_remove_front(stack);

        if( !mv_dcll_empty(stack) && mv_dcll_get_head(stack) == prunner->right )
        {
            p_tree_node_t temp = mv_dcll_remove_front(stack);
            mv_dcll_insert_front(stack, prunner);
            prunner = temp;
        }
        else
        {
            fprintf(stdout, "Deleting: ");
            pdeletedataproc(prunner->data);
            fprintf(stdout,"\n");
            free(prunner);
            prunner = NULL;
        }
    }

    mv_dcll_destroy(&stack, NULL);
    stack = NULL;
}

// BST Interface Functions
extern	tree_t 	create_tree()
{
    // Code
    tree_t tree = (tree_t)Xmalloc(SIZE_TREE);

    tree->root = NULL;
    tree->no_of_elements = 0;

    return(tree);
}

//	Tree Insert Function
extern ret_t mv_bst_insert(tree_t tree, data_t new_data, COMPAREDATAPROC pcomparedataproc)
{
    // Code

    if( NULL == tree )
    {
        ERROR_LOG("Tree Not Found.");
        return(FAILURE);
    }

    if( NULL == pcomparedataproc )
    {
        ERROR_LOG("Compare callback function must be provided.");
        return(FAILURE);
    }

    if( NULL == tree->root )
    {
        tree->root = create_node(new_data);
        tree->no_of_elements++;
    }
    else
    {
        return( generic_tree_insert(tree, new_data, pcomparedataproc) );
    }

    return(SUCCESS);
}

//	Tree Remove Function
extern data_t mv_bst_remove(tree_t tree, data_t data, COMPAREDATAPROC pcomparedataproc)
{
    //  Code

    if( NULL == tree    ||
        NULL == tree->root )
    {
        ERROR_LOG("Tree Not Found.");
        return((data_t)NULL);
    }

    if( NULL == pcomparedataproc )
    {
        ERROR_LOG("Compare callback must be provided.");
        return((data_t)NULL);
    }

    return( generic_tree_remove(tree, data, pcomparedataproc) );
}

extern void mv_bst_inorder_recursive(tree_t tree, SHOWDATAPROC pshowdataproc)
{
    //   Code
    if( NULL == tree ||
        NULL == tree->root )
    {
        ERROR_LOG("Tree Not Found.");
        return;
    }

    if( NULL == pshowdataproc )
    {
        ERROR_LOG("Showdata callback must be provided.");
        return;
    }

    fprintf(stdout, "Tree InOrder Traversal:\n");

    fprintf(stdout,"{START}->");
    generic_inorder_recursive(tree->root, pshowdataproc);
    fprintf(stdout,"{END}");

    fprintf(stdout, "\n\n");
}

extern void mv_bst_preorder_recursive(tree_t tree, SHOWDATAPROC pshowdataproc)
{
    //   Code
    if( NULL == tree ||
        NULL == tree->root )
    {
        ERROR_LOG("Tree Not Found.");
        return;
    }

    if( NULL == pshowdataproc )
    {
        ERROR_LOG("Showdata callback must be provided.");
        return;
    }

    fprintf(stdout, "Tree PreOrder Traversal:\n");
    
    fprintf(stdout,"{START}->");
    generic_preorder_recursive(tree->root, pshowdataproc);
    fprintf(stdout,"{END}");
 
    fprintf(stdout, "\n\n");
}

extern void mv_bst_postorder_recursive(tree_t tree, SHOWDATAPROC pshowdataproc)
{
    //   Code
    if( NULL == tree ||
        NULL == tree->root )
    {
        ERROR_LOG("Tree Not Found.");
        return;
    }

    if( NULL == pshowdataproc )
    {
        ERROR_LOG("Showdata callback must be provided.");
        return;
    }

    fprintf(stdout, "Tree PostOrder Traversal:\n");
    
    fprintf(stdout,"{START}->");
    generic_postorder_recursive(tree->root, pshowdataproc);
    fprintf(stdout,"{END}");

    fprintf(stdout, "\n\n");
}

extern void mv_bst_inorder_non_recursive(tree_t tree, SHOWDATAPROC pshowdataproc)
{
    // Code
    if( NULL == tree ||
        NULL == tree->root )
    {
        ERROR_LOG("Tree Not Found.");
        return;
    }

    if( NULL == pshowdataproc )
    {
        ERROR_LOG("Showdata callback must be provided.");
        return;
    }

    generic_inorder_non_recursive(tree->root, pshowdataproc);
}

extern void mv_bst_preorder_non_recursive(tree_t tree, SHOWDATAPROC pshowdataproc)
{
    // Code
    if( NULL == tree ||
        NULL == tree->root )
    {
        ERROR_LOG("Tree Not Found.");
        return;
    }

    if( NULL == pshowdataproc )
    {
        ERROR_LOG("Showdata callback must be provided.");
        return;
    }

    generic_preorder_non_recursive(tree->root, pshowdataproc);
}

extern void mv_bst_postorder_non_recursive(tree_t tree, SHOWDATAPROC pshowdataproc)
{
    // Code
    if( NULL == tree ||
        NULL == tree->root )
    {
        ERROR_LOG("Tree Not Found.");
        return;
    }

    if( NULL == pshowdataproc )
    {
        ERROR_LOG("Showdata callback must be provided.");
        return;
    }

    generic_postorder_non_recursive(tree->root, pshowdataproc);
}

extern void mv_bst_destroy_recursive(p_tree_t ptree, DELETEDATAPROC pdeletedataproc)
{
    //   Code
    if( NULL == ptree ||
        NULL == *ptree ||
        NULL == (*ptree)->root )
    {
        ERROR_LOG("Tree Not Found.");
        return;
    }

    if( NULL == pdeletedataproc )
    {
        ERROR_LOG("DeleteData callback must be provided.");
        return;
    }

    fprintf(stdout, "Tree Destroying:\n");
    
    generic_postorder_delete_recursive((*ptree)->root, pdeletedataproc);

    fprintf(stdout, "\n\n");

    free(*ptree);
    *ptree = NULL;
}

extern void mv_bst_destroy_non_recursive(p_tree_t ptree, DELETEDATAPROC pdeletedataproc)
{
    //   Code
    if( NULL == ptree ||
        NULL == *ptree ||
        NULL == (*ptree)->root )
    {
        ERROR_LOG("Tree Not Found.");
        return;
    }

    if( NULL == pdeletedataproc )
    {
        ERROR_LOG("DeleteData callback must be provided.");
        return;
    }

    fprintf(stdout, "Tree Destroying:\n");
    
    generic_postorder_delete_iterative((*ptree)->root, pdeletedataproc);

    fprintf(stdout, "\n\n");

    free(*ptree);
    *ptree = NULL;
}


