##
 # @File: mv_dcll.s
 # @Brief: This contains implementation of Doubly Circular Linked List
 # @Author: Janhavi Sunil Khisti(janhavikhisti@gmail.com)
 # @Date: 18-06-2024
 ##

.file "mv_dcll.s"

# Constant Literals

# #define SUCCESS 0
  .equ SUCCESS, 0

# #define FAILURE 1
  .equ FAILURE, 1

# struct node
# {
#	data_t   data;		OFFSET = 0
#	p_node_t p_next;	OFFSET = 4
#	p_node_t p_prev;	OFFSET = 8
# };

#define SIZE_NODE 12
.equ SIZE_NODE, 12
.equ node_data,   0
.equ node_p_next, 4
.equ node_p_prev, 8

# struct list
#{
#	p_node_t p_head;
#	p_node_t p_tail;
#	size_t size;
#};

#define SIZE_LIST 12
.equ SIZE_LIST, 12
.equ list_p_head, 0
.equ list_p_tail, 4
.equ list_size,   8


# Section ROData
.section .rodata

 # Error Message for Out Of Memory
.msg_p_e_oom:
	.string "ERROR : Out Of Memory\n"

# Error Message for List Not Found
.msg_p_e_lnf:
	.string "ERROR : List Not Found\n"

# Error Message for Existing Data Not Found
.msg_p_e_ednf:
	.string "ERROR : Existing Data Not Found\n"

# Error Message for Index Out Of Bound
.msg_p_e_iob:
	.string "ERROR : Index Out Of Bound\n"

# Message for DCLL
.msg_p_dcll:
	.string " Doubly Circular Linked List:\n"

# Message for Start
.msg_p_start:
	.string "{START}->"

# Message for End
.msg_p_end:
	.string "{END}\n\n"

# Message for After Insert Front
.msg_p_aif:
	.string "After Insert Front:\n"

# Message for After Insert Back
.msg_p_aib:
	.string "After Insert Back:\n"

# Message for After Insert Before
.msg_p_aibf:
	.string "After Insert Before:\n"

# Message for After Insert After
.msg_p_aiaf:
	.string "After Insert After:\n"

# Message for After Insert At
.msg_p_aiat:
	.string "After Insert At:\n"

# Message for After Remove Front
.msg_p_arf:
	.string "After Remove Front:\n"

# Message for After Remove Back
.msg_p_arb:
	.string "After Remove Back:\n"

# Message for After Remove Before
.msg_p_arbf:
	.string "After Remove Before:\n"

# Message for After Remove After
.msg_p_araf:
	.string "After Remove After:\n"

# Message for After Remove At
.msg_p_arat:
	.string "After Remove At:\n"

# Message for Printdata
.msg_p_printdata:
	.string "{%d}->"

# Message for Deletedata
.msg_p_deletedata:
	.string "Deleting : %d\n"

.msg_p_here1:
	.string "Here-1\n"

# Section Data 



# Section Text
.section .text

# --------------  LIST HELPER FUNCTIONS ---------------- #

#
# FUNCTION NAME: XMALLOC
# DESCRIPTION: 	ALLOCATES THE MEMORY OF GIVEN NUMBER OF BYTES
# INPUT: 1. NO OF BYTES
# RETURN: POINTER TO THE MEMORY BLOCK ALLOCATED
#

# static void* Xmalloc(size_t no_of_bytes)
  .type Xmalloc, @function

  # Input Parameter
  .equ no_of_bytes_xmp, 8

  # Local Variable
  .equ p_xml, -4

Xmalloc:

	# Prologue
	pushl %ebp
	movl %esp, %ebp

	subl $4, %esp

	movl $0, p_xml(%ebp)

	# Xmalloc Code

	# void* p = malloc(no_of_bytes);
	pushl no_of_bytes_xmp(%ebp)
	call malloc
	addl $4, %esp

	movl %eax, p_xml(%ebp)

	# If block
	movl p_xml(%ebp), %ebx
	cmpl $0, %ebx

	jne .Xmalloc_return_address

		# True Block
		pushl $.msg_p_e_oom
		call printf
		addl $4, %esp

		pushl $FAILURE
		call exit

	.Xmalloc_return_address:
	# return(p);
	movl p_xml(%ebp), %eax

	# Epilogue
	addl $4, %esp

	movl %ebp, %esp
	popl %ebp
	ret


#
# FUNCTION NAME: LIST_GENERIC_INSERT
# DESCRIPTION: 	INSERT MID NODE BETWEEN FIRST AND LAST IN GIVEN 
#  							LIST
# INPUT: 1. POINTER TO A LIST
#  		   2. FIRST NODE
#  		   3. MID NODE ( NODE TO BE INSERTED )
#   	   4. LAST NODE
# RETURN: SUCCESS - WHEN SUCCESSFULLY INSERTED
#

  .type list_generic_insert, @function

  # Input Parameters
  .equ plist_lgip, 8
  .equ first_lgip, 12
  .equ mid_lgip,   16
  .equ last_lgip,  20

  # Local Variable 

list_generic_insert:

	# Prologue
	pushl %ebp
	movl %esp, %ebp

	# List Generic Insert Main Code

	# mid->p_next = last;
	movl last_lgip(%ebp), %edx
	movl mid_lgip(%ebp), %ebx
	movl %edx, node_p_next(%ebx)

	# mid->p_prev = first;
	movl first_lgip(%ebp), %edx
	movl mid_lgip(%ebp), %ecx
	movl %edx, node_p_prev(%ecx)

	# first->p_next = mid;
	movl mid_lgip(%ebp), %ebx
	movl first_lgip(%ebp), %edx
	movl %ebx, node_p_next(%edx)

	# last->p_prev = mid;
	movl mid_lgip(%ebp), %edx
	movl last_lgip(%ebp), %ecx
  movl %edx, node_p_prev(%ecx)

  # plist size++;
	movl plist_lgip(%ebp), %eax
	movl list_size(%eax), %edx
	incl %edx
	movl %edx, list_size(%eax)

	# plist->p_tail = plist->p_head->p_prev;
	movl	plist_lgip(%ebp), %eax
	movl	list_p_head(%eax), %eax 
	movl	node_p_prev(%eax), %edx

	movl	plist_lgip(%ebp), %eax
	movl	%edx, list_p_tail(%eax)

	# Epilogue

	# return(SUCCESS);
	movl $SUCCESS, %eax

	movl %ebp, %esp
	popl %ebp
	ret


#
# FUNCTION NAME: LIST_GENERIC_REMOVE
# DESCRIPTION: 	REMOVES THE GIVEN NODE FROM THE LIST
# INPUT: 1. POINTER TO A LIST
#   	 	 2. NODE TO BE DELETED
# RETURN: SUCCESS - DATA OF DELETED NODE
#

  .type list_generic_remove, @function

  # input parameter
  .equ plist_lgrp,  8
  .equ d_node_lgrp, 12

  # local variable
  .equ first_lgrl,          -4
  .equ last_lgrl,           -8
  .equ to_return_data_lgrl, -12

list_generic_remove:

	# Prologue
	pushl %ebp
	movl %esp, %ebp

	subl $12, %esp
	movl $0, first_lgrl(%ebp)
	movl $0, last_lgrl(%ebp)

	# List Generic Remove Main Code

	# p_node_t first = d_node->p_prev;
	movl d_node_lgrp(%ebp), %edx
	movl node_p_prev(%edx), %eax
	movl %eax, first_lgrl(%ebp)

	# p_node_t last = d_node->p_next;
	movl d_node_lgrp(%ebp), %ebx
	movl node_p_next(%ebx), %ecx
	movl %ecx, last_lgrl(%ebp)

	# first->p_next = last;
	movl last_lgrl(%ebp), %edx
	movl first_lgrl(%ebp), %eax
	movl %edx, node_p_next(%eax)

	# last->p_prev = first;
	movl first_lgrl(%ebp), %ebx
	movl last_lgrl(%ebp), %eax
	movl %ebx, node_p_prev(%eax)

	# d_node->p_next = d_node->p_prev = NULL;
	movl d_node_lgrp(%ebp), %eax
	movl $0, node_p_next(%eax)

	movl d_node_lgrp(%ebp), %ebx
	movl $0, node_p_prev(%ebx)

	# data_t to_return_data = d_node->data;
	movl d_node_lgrp(%ebp), %ebx
	movl node_data(%ebx), %ecx
	movl %ecx, to_return_data_lgrl(%ebp)

	# free(d_node);
	pushl d_node_lgrp(%ebp)
	call free
	addl $4, %esp

	# plist->size--;
	movl plist_lgrp(%ebp), %eax
	movl list_size(%eax), %edx
	decl %edx

	# plist->p_tail = plist->p_head->p_prev;

	# plist->p_head->p_prev
	movl plist_lgip(%ebp), %eax
	movl list_p_head(%eax), %eax
	movl node_p_prev(%eax), %edx

	# plist->p_tail
	movl plist_lgip(%ebp), %eax
	movl %edx, list_p_tail(%eax)

	# return( to_return_data );
	movl to_return_data_lgrl(%ebp), %eax

	# Epilogue
	addl $12, %esp
	
	movl %ebp, %esp 
	popl %ebp
	ret


#
# FUNCTION NAME: CREATE_NODE
# DESCRIPTION: 	CREATES THE NEW NODE WITH GIVEN DATA
# INPUT: 1. NEW DATA
# RETURN: POINTER TO NEW NODE
#

	.type create_node, @function

	# Input Parameter
	.equ new_data_cnp, 8

	# Local Variable
	.equ pnode_cnl, -4

create_node:

	# Prologue 
	pushl %ebp
	movl %esp, %ebp

	subl $4, %esp

	movl $0, pnode_cnl(%ebp)

	# Create Node Main Code

	# p_node_t pnode = (p_node_t) Xmalloc(SIZE_NODE);
	pushl $SIZE_NODE
	call Xmalloc
	addl $4, %esp

	movl %eax, pnode_cnl(%ebp)

	# pnode->data = new_data;
	movl new_data_cnp(%ebp), %ebx
	movl pnode_cnl(%ebp), %eax
	movl %ebx,node_data(%eax)

	# pnode->p_next = pnode;
	movl pnode_cnl(%ebp), %edx
	movl pnode_cnl(%ebp), %eax
	movl %edx, node_p_next(%eax) 

	# pnode->p_prev = pnode;
	movl pnode_cnl(%ebp), %ecx
	movl pnode_cnl(%ebp), %eax
	movl %ecx, node_p_prev(%eax)

	# return(pnode);
	movl pnode_cnl(%ebp), %eax

	# Epilogue 
	addl $4, %esp

	movl %ebp, %esp
	popl %ebp
	ret


# ---------------- LIST INTERFACE FUNCTION --------------- #

#
# FUNCTION NAME: CREATE_LIST
# DESCRIPTION: 	CREATES THE NEW LIST
# INPUT: 1. VOID - NOTHING
# RETURN: POINTER TO NEW LIST CREATED
#

	.globl create_list
	.type  create_list, @function

	# Input Parameter

	# Local Variable
	.equ plist_cll, -4

create_list:

	# Prologue
	pushl %ebp
	movl %esp, %ebp

	subl $4, %esp

	movl $0, plist_cll(%ebp)

	# Create List Main Code

	# p_mv_dcll_t plist = (p_mv_dcll_t) Xmalloc(SIZE_LIST);
	pushl $SIZE_LIST
	call Xmalloc
	addl $4, %esp

	movl %eax, plist_cll(%ebp)

	# plist->p_head = create_node(NULL);
	pushl $0
	call create_node
	addl $4, %esp

	movl %eax, %edx

	movl plist_cll(%ebp), %ebx
	movl %edx, list_p_head(%ebx)

	# plist->p_tail = plist->p_head;
	movl plist_cll(%ebp), %eax
	movl list_p_head(%eax), %edx
	movl %edx, list_p_tail(%eax)

	# plist->size = 0;
	movl plist_cll(%ebp), %eax
	movl $0, list_size(%eax)

	# return(plist);
	movl plist_cll(%ebp), %eax

	# Epilogue 
	addl $4, %esp

	movl %ebp, %esp
	popl %ebp
	ret


			# ------ INSERTION FUNCTIONS ------ #

#
# FUNCTION NAME: LIST_INSERT_FRONT
# DESCRIPTION: 	INSERTS A NEW NODE WITH GIVEN DATA IN 
#								FRONT OF GIVEN LIST  				
# INPUT: 1. POINTER TO A LIST
#  		   2. NEW DATA 
# RETURN: SUCCESS - IF INSERTED SUCCESSFULLY
#  		  	FAILURE - IF UNSUCCESSFULL
#

 # extern ret_t list_insert_front(p_mv_dcll_t plist, data_t new_data)
  .globl list_insert_front
  .type  list_insert_front, @function

  # Input Parameter
  .equ plist_lifp, 	  8
  .equ new_data_lifp, 12

  # Local Variable
  .equ new_node_lifl, -4

list_insert_front:

	# Prologue
	pushl %ebp
	movl %esp, %ebp

	subl $4, %esp
	movl $0, new_node_lifl(%ebp)

	# List Insert Front Main Code

	# if( NULL == plist )
	cmpl $0, plist_lifp(%ebp)

	jne .list_present_lif

			# True Block
			pushl $.msg_p_e_lnf
			call printf
			addl $4, %esp

			movl $FAILURE, %eax

			jmp .lif_epilogue

	.list_present_lif:

		# p_node_t new_node = create_node(new_data);
		pushl new_data_lifp(%ebp)
		call create_node
		addl $4, %esp

		movl %eax, new_node_lifl(%ebp)

		# return(list_generic_insert(plist, plist->p_head, new_node, plist->p_head->p_next))
		# plist->p_head->p_next
		movl plist_lgip(%ebp), %eax
		movl list_p_head(%eax), %eax
		pushl node_p_next(%eax)

		# new_node
		pushl new_node_lifl(%ebp)

		# plist->p_head
		movl plist_lifp(%ebp), %eax
		pushl list_p_head(%eax)

		# plist
		pushl plist_lifp(%ebp)	

		call list_generic_insert
		addl $20, %esp

	# Epilogue
	.lif_epilogue: 
		addl $4, %esp

		movl %ebp, %esp
		popl %ebp
		ret


#
# FUNCTION NAME: LIST_INSERT_BACK
# DESCRIPTION: 	INSERTS A NEW NODE WITH GIVEN DATA AT 
#								THE BACK OF GIVEN LIST  				
# INPUT: 1. POINTER TO A LIST
#  		   2. NEW DATA 
# RETURN: SUCCESS - IF INSERTED SUCCESSFULLY
#  		    FAILURE - IF UNSUCCESSFULL
#

 # extern ret_t list_insert_back(p_mv_dcll_t plist, data_t new_data)
  .globl list_insert_back
  .type  list_insert_back, @function

  # Input Parameter
  .equ plist_libp, 	  8
  .equ new_data_libp, 12

  # Local Variable
  .equ new_node_libl, -4

list_insert_back:

	# Prologue
	pushl %ebp
	movl %esp, %ebp

	subl $4, %esp
	movl $0, new_node_libl(%ebp)

	# List Insert Back Main Code

	# if( NULL == plist )
	cmpl $0, plist_libp(%ebp)

	jne .list_present_lib

		# True Block
		pushl $.msg_p_e_lnf
		call printf
		addl $4, %esp

		movl $FAILURE, %eax

		jmp .lib_epilogue

	.list_present_lib:

		# p_node_t new_node = create_node(new_data);
		pushl new_data_libp(%ebp)
		call create_node
		addl $4, %esp

		movl %eax, new_node_libl(%ebp)

		# return(list_generic_insert(plist, plist->p_tail, new_node, plist->p_tail->p_next))
		# plist->p_tail->p_next
		movl plist_libp(%ebp), %eax
		movl list_p_tail(%eax), %eax
		pushl node_p_next(%eax)

		# new_node
		pushl new_node_libl(%ebp)

		# plist->p_tail
		movl plist_libp(%ebp), %eax
		pushl list_p_tail(%eax)

		# plist
		pushl plist_libp(%ebp)

		call list_generic_insert
		addl $20, %esp

	# Epilogue 
	.lib_epilogue:
 
		addl $4, %esp

		movl %ebp, %esp
		popl %ebp
		ret


#
# FUNCTION NAME: LIST_INSERT_BEFORE
# DESCRIPTION: 	INSERTS A NEW NODE WITH GIVEN DATA 
#				BEFORE THE GIVEN EXISTING DATA NODE IN LIST 				
# INPUT: 1. POINTER TO A LIST
#  		   2. NEW DATA 
#  		   3. EXISTING DATA
# 		   4. POINTER TO A COMPARE DATA FUNCTION
# RETURN: SUCCESS - IF INSERTED SUCCESSFULLY
#  		    FAILURE - IF UNSUCCESSFULL
#

# extern ret_t list_insert_before(p_mv_dcll_t plist, data_t new_data, data_t e_data, COMPAREDATAPROC pcomparedataproc)
   .globl list_insert_before
   .type  list_insert_before, @function

   # Input Parameters
   .equ plist_libfp, 			8
   .equ new_data_libfp, 		12
   .equ e_data_libfp, 			16
   .equ pcomparedataproc_libfp, 20

   # Local Variable
   .equ prunner_libfl,  -4
   .equ new_node_libfl, -8

list_insert_before:

	# prologue
	pushl %ebp
	movl %esp, %ebp

	subl $8, %esp 
	movl $0, prunner_libfl(%ebp)
	movl $0, new_node_libfl(%ebp)

	# List Insert Before Main Code

	# if(NULL == plist)
	cmpl $0, plist_libfp(%ebp)

	jne .list_present_libf

		# True Block
		.libf_list_not_found:

			pushl $.msg_p_e_lnf
			call printf
			addl $4, %esp

			movl $FAILURE, %eax

			jmp .libf_epilogue

	# List insert Before Normal Execution
	.list_present_libf:

		# (0 == plist->size)
		movl	plist_libfp(%ebp), %eax
		cmpl $0, list_size(%eax)

		je .libf_list_not_found

		# p_node_t prunner = plist->p_head->p_next;
		movl plist_libfp(%ebp), %eax
		movl list_p_head(%eax), %eax
		movl node_p_next(%eax), %edx
		
		movl %edx, prunner_libfl(%ebp)

		# While loop  
		.loop_libf:

			# Condition  
			# if(SUCCESS == pcomparedataproc(prunner->data, e_data))
			pushl e_data_libfp(%ebp)

			movl prunner_libfl(%ebp), %eax
			pushl node_data(%eax)
	
			movl pcomparedataproc_libfp(%ebp), %eax
			call *%eax
			addl $8, %esp

			cmpl $SUCCESS, %eax

			je .loop_end_libf

				# prunner = prunner->p_next;
				movl prunner_libfl(%ebp), %eax
				movl node_p_next(%eax), %edx
				movl %edx, prunner_libfl(%ebp)

				# if(plist->p_head == prunner)
				movl prunner_libfl(%ebp), %edx
				movl plist_libfp(%ebp), %eax
				cmpl %edx, list_p_head(%eax)

				jne .loop_libf

					# True Block
					pushl $.msg_p_e_ednf
					call printf
					addl $4, %esp

					movl $FAILURE, %eax

					jmp .libf_epilogue

		.loop_end_libf:

		# create_node(new_data)
		pushl new_data_libfp(%ebp)
		call create_node
		addl $4, %esp 

		movl %eax, new_node_libfl(%ebp)

		# return( list_generic_insert(plist, prunner->p_prev, new_node, prunner));
		# prunner
		pushl prunner_libfl(%ebp)

		# new_node
		pushl new_node_libfl(%ebp)

		# prunner->p_prev
		movl prunner_libfl(%ebp), %eax
		pushl node_p_prev(%eax)

		# plist
		pushl plist_libfp(%ebp)

		call list_generic_insert
		addl $16, %esp

	.libf_epilogue:

		addl $8, %esp

		movl %ebp, %esp
		popl %ebp
		ret


#
# FUNCTION NAME: LIST_INSERT_AFTER
# DESCRIPTION: 	INSERTS A NEW NODE WITH GIVEN DATA 
#								AFTER THE GIVEN EXISTING DATA NODE IN LIST  				
# INPUT: 1. POINTER TO A LIST
#  		   2. NEW DATA 
#  		   3. EXISTING DATA
# 		   4. POINTER TO A COMPARE DATA FUNCTION
# RETURN: SUCCESS - IF INSERTED SUCCESSFULLY
#  		    FAILURE - IF UNSUCCESSFULL
#

# extern ret_t list_insert_after(p_mv_dcll_t plist, data_t new_data, data_t e_data, COMPAREDATAPROC pcomparedataproc)  
  .globl list_insert_after
  .type list_insert_after, @function

  # input parameter
  .equ plist_liafp,            8
  .equ new_data_liafp,         12
  .equ e_data_liafp,           16
  .equ pcomparedataproc_liafp, 20

  # local variable
  .equ prunner_liafl,  -4
  .equ new_node_liafl, -8

list_insert_after:

	# Prologue
	pushl %ebp
	movl %esp, %ebp

	subl $8, %esp 
	movl $0, prunner_liafl(%ebp)
	movl $0, new_node_liafl(%ebp)

	# List Insert After Main Code

	# if(NULL == plist)
	cmpl $0, plist_liafp(%ebp)

	jne .list_present_liaf

		# True Block
		.liaf_list_not_found:

			pushl $.msg_p_e_lnf
			call printf
			addl $4, %esp

			movl $FAILURE, %eax

			jmp .liaf_epilogue

	.list_present_liaf:

		# (0 == plist->size)
		movl plist_liafp(%ebp), %eax
		cmpl $0, list_size(%eax)

		je .liaf_list_not_found

		# p_node_t prunner = plist->p_head->p_next;
		movl plist_liafp(%ebp), %eax
		movl list_p_head(%eax), %eax
		movl node_p_next(%eax), %edx
		movl %edx, prunner_liafl(%ebp)

		# While Loop
		.loop_liaf:

			# Condition
			# if(SUCCESS == pcomparedataproc( prunner->data, e_data )) 
			pushl e_data_liafp(%ebp)
			movl prunner_liafl(%ebp), %eax
			pushl node_data(%eax)

			movl pcomparedataproc_liafp(%ebp), %eax
			call *%eax
			addl $8, %esp

			cmpl $SUCCESS, %eax

			je .loop_end_liaf

				# prunner = prunner-> p_next;
				movl prunner_liafl(%ebp), %eax
				movl node_p_next(%eax), %edx
				movl %edx, prunner_liafl(%ebp)

				# if(plist->p_head == prunner)
				movl prunner_liafl(%ebp), %edx
				movl plist_liafp(%ebp), %eax
				cmpl %edx, list_p_head(%eax)

				jne .loop_liaf

					pushl $.msg_p_e_ednf
					call printf
					addl $4, %esp

					movl $FAILURE, %eax
					jmp .liaf_epilogue

		.loop_end_liaf:

		# create_node(new_data)
		pushl new_data_liafp(%ebp)
		call create_node
		addl $4, %esp

		movl %eax, new_node_liafl(%ebp)

		# return( list_generic_insert(plist, prunner, new_node, prunner->p_next));
		# prunner->p_next
		movl prunner_liafl(%ebp), %eax
		pushl node_p_next(%eax)

		# new_node
		pushl new_node_liafl(%ebp)

		# prunner
		pushl prunner_liafl(%ebp)

		# plist
		pushl plist_liafp(%ebp)

		call list_generic_insert
		addl $16, %esp

	.liaf_epilogue:

		addl $8, %esp

		movl %ebp, %esp
		popl %ebp
		ret


#
# FUNCTION NAME: LIST_INSERT_AT
# DESCRIPTION: 	INSERTS A NEW NODE WITH GIVEN DATA 
#								AT THE GIVEN INDEX  				
# INPUT: 1. POINTER TO A LIST
#  		 	 2. NEW DATA 
#  		   3. INDEX
# RETURN: SUCCESS - IF INSERTED SUCCESSFULLY
#  		    FAILURE - IF UNSUCCESSFULL
#

  .globl list_insert_at
  .type list_insert_at, @function

  # input parameter
  .equ plist_liatp,    8
  .equ new_data_liatp, 12
  .equ index_liatp,    16

  # local variable
  .equ prunner_liatl,  -4
  .equ new_node_liatl, -8
  .equ le_liatl,       -12

list_insert_at:

	# Prologue 
	pushl %ebp
	movl %esp, %ebp

	subl $12, %esp 
	movl $0, prunner_liatl(%ebp)
	movl $0, new_node_liafl(%ebp)

	# List Insert At Main Code

	# Condition
	# if(NULL == plist)
	cmpl $0, plist_liatp(%ebp)
	jne .list_present_liat

			pushl $.msg_p_e_lnf
			call printf
			addl $4, %esp

			movl $FAILURE, %eax

			jmp .liat_epilogue


	.list_present_liat:

		# Condition
		# if(0 == index)
		cmpl $0, index_liatp(%ebp)
		jne .liat_index_not_zero

				# list_insert_front(plist, new_data)
				# new_data
				pushl new_data_liatp(%ebp)
				# plist
				pushl plist_liatp(%ebp)
				call list_insert_front
				addl $8, %esp

				movl $SUCCESS, %eax

				jmp .liat_epilogue


		.liat_index_not_zero:

			# Condition
			# else if(index == plist->size)
			movl index_liatp(%ebp), %ebx
			movl plist_liatp(%ebp), %eax
			movl list_size(%eax), %ecx

			cmpl %ecx, %ebx 

			jne .liat_not_last_index

				# list_insert_back(plist, new_data)
				# new_data
				pushl new_data_liatp(%ebp)
				# plist
				pushl plist_liatp(%ebp)
				call list_insert_back
				addl $8, %esp

				movl $SUCCESS, %eax

				jmp .liat_epilogue


			.liat_not_last_index:

				# Condition
				# if(index > plist->size)
				movl index_liatp(%ebp), %ebx
				movl plist_liatp(%ebp), %eax
				movl list_size(%eax), %edx

				cmpl %edx, %ebx

				jl .liat_index_not_out_of_bound

						pushl $.msg_p_e_iob
						call printf
						addl $4, %esp

						movl $FAILURE, %eax

						jmp .liat_epilogue


					.liat_index_not_out_of_bound:

					# p_node_t prunner = plist->p_head;
					movl plist_liatp(%ebp), %eax
					movl list_p_head(%eax), %ebx
					movl %ebx, prunner_liatl(%ebp)

					# Loop Initialization
					movl $0, le_liatl(%ebp)

					# For Loop
					.loop_liat:

						# Loop Condition 
						# le < index;
						movl le_liatl(%ebp), %eax
						movl index_liatp(%ebp), %ebx

						cmpl %ebx, %eax

						jge .loop_end_liat

							# Loop Body
							# prunner = prunner->p_next;
							movl prunner_liatl(%ebp), %eax
							movl node_p_next(%eax), %ebx
							movl %ebx, prunner_liatl(%ebp)

							# Increment
							incl le_liatl(%ebp)

							jmp .loop_liat

					.loop_end_liat:

					# create_node(new_data)
					pushl new_data_liafp(%ebp)
					call create_node
					addl $4, %esp

					movl %eax, new_node_liafl(%ebp)

		# return( list_generic_insert(plist, prunner, new_node, prunner->p_next));
			# prunner->p_next
			movl prunner_liatl(%ebp), %eax
			pushl node_p_next(%eax)
			
			# new_node
			pushl new_node_liatl(%ebp)

			# prunner
			pushl prunner_liatl(%ebp)

			# plist
			pushl plist_liatp(%ebp)

			call list_generic_insert
			addl $16, %esp

	.liat_epilogue:

		addl $12, %esp

		movl %ebp, %esp
		popl %ebp
		ret


			# ------- REMOVAL FUNCTIONS ------ #

#
# FUNCTION NAME: LIST_REMOVE_FRONT
# DESCRIPTION: 	REMOVES A NODE FROM FRONT OF LIST  				
# INPUT: 1. POINTER TO A LIST
# RETURN: DATA FROM REMOVED NODE - IF REMOVED SUCCESSFULLY
#  		    NULL - IF UNSUCCESSFULL
#

# extern data_t list_remove_front(p_mv_dcll_t plist)
  .globl list_remove_front
  .type list_remove_front, @function

  # input parameter
  .equ plist_lrfp, 8

  # local variable

list_remove_front:

	# prologue
	pushl %ebp
	movl %esp, %ebp

	# List Remove Front Function Main Code

	# Condition
	# if(NULL == plist)
	cmpl $0, plist_lrfp(%ebp)

	jne .list_present_lrf

		.lrf_list_not_found:

			pushl $.msg_p_e_lnf
			call printf
			addl $4, %esp

			movl $0, %eax

			jmp .lrf_epilogue

	.list_present_lrf:

		# Condition
		# (0 == plist->size)
		movl plist_lrfp(%ebp), %eax
		cmpl $0, list_size(%eax)

		jne .list_not_empty_lrf

			jmp .lrf_list_not_found


		.list_not_empty_lrf:

		# return( list_generic_remove(plist, plist->p_head->p_next) );
		movl plist_lrfp(%ebp), %eax
		movl list_p_head(%eax), %eax
		pushl node_p_next(%eax)

		pushl plist_lrfp(%ebp)
		
		call list_generic_remove
		addl $8, %esp

	.lrf_epilogue:

		movl %ebp, %esp
		popl %ebp
		ret


#
# FUNCTION NAME: LIST_REMOVE_BACK
# DESCRIPTION: 	REMOVES A NODE FROM BACK OF LIST  				
# INPUT: 1. POINTER TO A LIST
# RETURN: DATA FROM REMOVED NODE - IF REMOVED SUCCESSFULLY
#  		    NULL - IF UNSUCCESSFULL
#

# extern data_t list_remove_back(p_mv_dcll_t plist)
  .globl list_remove_back
  .type list_remove_back, @function

  # input parameter
  .equ plist_lrbp, 8

  # local variable

list_remove_back:

	# prologue
	pushl %ebp
	movl %esp, %ebp

	# List Remove Back Function Main Code
	
	# Condition
	# (NULL == plist)
	cmpl $0, plist_lrbp(%ebp)

	jne .list_present_lrb

		.lrb_list_not_found:

			pushl $.msg_p_e_lnf
			call printf
			addl $4, %esp

			# return((data_t)NULL);
			movl $0, %eax

			jmp .lrb_epilogue

	.list_present_lrb:

		# Condition
		# (0 == plist->size)
		movl plist_lrbp(%ebp), %eax
		cmpl $0, list_size(%eax)

		jne .list_not_empty_lrb

			je .lrb_list_not_found

		.list_not_empty_lrb:

		# return( list_generic_remove(plist, plist->p_tail) );
		movl plist_lrfp(%ebp), %eax
		pushl list_p_tail(%eax)

		pushl plist_lrfp(%ebp)

		call list_generic_remove
		addl $8, %esp

	.lrb_epilogue:

		movl %ebp, %esp
		popl %ebp
		ret


#
# FUNCTION NAME: LIST_REMOVE_BEFORE
# DESCRIPTION: 	REMOVES NODE BEFORE THE GIVEN EXISTING DATA NODE IN LIST 				
# INPUT: 1. POINTER TO A LIST
#  		   2. EXISTING DATA
# 		   3. POINTER TO A COMPARE DATA FUNCTION
# RETURN: DATA FROM REMOVED NODE - IF REMOVED SUCCESSFULLY
#  		    NULL - IF UNSUCCESSFULL
#

# extern data_t list_remove_before(p_mv_dcll_t plist, data_t e_data, COMPAREDATAPROC pcomparedataproc)

  .globl list_remove_before
  .type list_remove_before, @function

  # input parameter
  .equ plist_lrbfp,            8
  .equ e_data_lrbfp,           12
  .equ pcomparedataproc_lrbfp, 16

  # local variable
  .equ prunner_lrbfl, -4

list_remove_before:
	
	# prologue
	pushl %ebp
	movl %esp, %ebp

	subl $4, %esp

	# List Remove Before Main Code

	# Condition
	# if(NULL == plist)
	cmpl $0, plist_lrbfp(%ebp)

	jne .list_present_lrbf

		.lrbf_list_not_found:

			pushl $.msg_p_e_lnf
			call printf
			addl $4, %esp

			# return((data_t)NULL);
			movl $0, %eax

			jmp .lrbf_epilogue

	.list_present_lrbf:

		# Condition
		# (0 == plist->size)
		movl plist_lrbp(%ebp), %eax
		cmpl $0, list_size(%eax)

		je .lrbf_list_not_found

		# p_node_t prunner = plist->p_head->p_next;
		movl plist_lrbfp(%ebp), %eax
		movl list_p_head(%eax), %eax
		movl node_p_next(%eax), %edx
		movl %edx, prunner_lrbfl(%ebp)

		# While Loop
		.loop_lrbf:

			# Condition
			# (SUCCESS == pcomparedataproc( prunner->data, e_data))
			pushl e_data_lrbfp(%ebp)

			movl prunner_lrbfl(%ebp), %eax
			pushl node_data(%eax)

			movl pcomparedataproc_lrbfp(%ebp), %eax
			call *%eax
			addl $8, %esp

			cmpl $SUCCESS, %eax

			je .loop_end_lrbf

				# prunner = prunner->p_next;
				movl prunner_lrbfl(%ebp), %eax
				movl node_p_next(%eax), %edx
				movl %edx, prunner_lrbfl(%ebp)

				# if(plist->p_head == prunner)
				movl prunner_lrbfl(%ebp), %edx
				movl plist_lrbfp(%ebp), %eax
				cmpl %edx, list_p_head(%eax)

				jne .loop_lrbf

					pushl $.msg_p_e_ednf
					call printf
					addl $4, %esp

					movl $0, %eax
					jmp .lrbf_epilogue

		.loop_end_lrbf:

		# return( list_generic_remove(plist, prunner->p_prev) );
		# prunner->p_prev
		movl prunner_lrbfl(%ebp), %eax
		pushl node_p_prev(%eax)

		pushl plist_lrbfp(%ebp)

		call list_generic_remove
		addl $8, %esp

	.lrbf_epilogue:

		addl $4, %esp

		movl %esp, %ebp
		popl %ebp
		ret


#
# FUNCTION NAME: LIST_REMOVE_AFTER
# DESCRIPTION: 	REMOVES NODE AFTER THE GIVEN EXISTING DATA NODE IN LIST 				
# INPUT: 1. POINTER TO A LIST
#  		   2. EXISTING DATA
# 		   3. POINTER TO A COMPARE DATA FUNCTION
# RETURN: DATA FROM REMOVED NODE - IF REMOVED SUCCESSFULLY
#  		    NULL - IF UNSUCCESSFULL
#

# extern data_t list_remove_after(p_mv_dcll_t plist, data_t e_data, COMPAREDATAPROC pcomparedataproc)

  .globl list_remove_after
  .type list_remove_after, @function

  # input parameter
  .equ plist_lrafp,            8
  .equ e_data_lrafp,           12
  .equ pcomparedataproc_lrafp, 16

  # local variable
  .equ prunner_lrafl, -4

list_remove_after:
	
	# prologue
	pushl %ebp
	movl %esp, %ebp

	subl $4, %esp

	# List Remove After Main Code

	# Condition
	# (NULL == plist)
	cmpl $0, plist_lrafp(%ebp)

	jne .lraf_list_present

		.lraf_list_not_found:

			pushl $.msg_p_e_lnf
			call printf
			addl $4, %esp

			movl $0, %eax

			jmp .lraf_epilogue

	.lraf_list_present:

		# Condition
		# (0 == plist->size)
		movl plist_lrafp(%ebp), %eax
		cmpl $0, list_size(%eax)

		je .lraf_list_not_found

		# p_node_t prunner = plist->p_head->p_next;
		movl plist_lrafp(%ebp), %eax
		movl list_p_head(%eax), %eax
		movl node_p_next(%eax), %edx

		movl %edx, prunner_lrafl(%ebp)

		# While Loop
		.loop_lraf:

			# Condition
			# (SUCCESS == pcomparedataproc( prunner->data, e_data))
			movl prunner_lrafl(%ebp), %eax
			pushl node_data(%eax)

			pushl e_data_lrafp(%ebp)

			movl pcomparedataproc_lrafp(%ebp), %eax
			call *%eax
			addl $8, %esp

			cmpl $0, %eax

			je .loop_end_lraf

			# prunner = prunner->p_next;
			movl prunner_lrafl(%ebp), %eax
			movl node_p_next(%eax), %edx
			movl %edx, prunner_lrafl(%ebp)

			# if(plist->p_head == prunner)
			movl prunner_lrafl(%ebp), %edx
			movl plist_lrafp(%ebp), %eax
			cmpl %edx, list_p_head(%eax)

			jne .loop_lraf

				pushl $.msg_p_e_ednf
				call printf
				addl $4, %esp

				movl $0, %eax

				jmp .lraf_epilogue

		.loop_end_lraf:

		# return( list_generic_remove(plist, prunner->p_next) );
		# prunner->p_next
		movl prunner_lrafl(%ebp), %eax
		pushl node_p_next(%eax)

		pushl plist_lrafp(%ebp)

		call list_generic_remove
		addl $8, %esp

	.lraf_epilogue:

		addl $4, %esp

		movl %esp, %ebp
		popl %ebp
		ret

 
#
# FUNCTION NAME: LIST_REMOVE_AT
# DESCRIPTION: 	REMOVES A NODE FROM A GIVEN INDEX 				
# INPUT: 1. POINTER TO A LIST
#  		   2. INDEX
# RETURN: DATA FROM REMOVED NODE - IF REMOVED SUCCESSFULLY
#  		    NULL - IF UNSUCCESSFULL
#

# extern data_t list_remove_at(p_mv_dcll_t plist, long index)

  .globl list_remove_at
  .type list_remove_at, @function

  # input parameter
  .equ plist_lratp, 8
  .equ index_lratp, 12

  # local variable
  .equ prunner_lratl, -4
  .equ le_lratl,      -8

list_remove_at:

	# Prologue
	pushl %ebp
	movl %esp, %ebp

	subl $8, %esp
	movl $0, prunner_lratl(%ebp)

	# List Remove At Main Code

	# Condition
	# if(NULL == plist)
	cmpl $0, plist_lratp(%ebp)

	jne .lrat_list_present

		.lrat_list_not_found:

			pushl $.msg_p_e_lnf
			call printf
			addl $4, %esp

			movl $0, %eax

			jmp .lrat_epilogue

	.lrat_list_present:

		# Condition
		# if(0 == index)
		cmpl $0, index_lratp(%ebp)

		jmp .lrat_index_not_zero

			# list_remove_front(plist) 
			pushl plist_lratp(%ebp)
			call list_remove_front
			addl $4, %esp

			movl $0, %eax

			jmp .lrat_epilogue

		.lrat_index_not_zero:

			# Condition
			# else if(index == plist->size)
			movl plist_lratp(%ebp), %ebx
			movl list_size(%ebx), %edx

			cmpl %edx,index_lratp(%ebp)
		
			jne .lrat_not_last_index

				# list_remove_back(plist)
				pushl plist_lratp(%ebp)
				call list_remove_back
				addl $4, %esp

				jmp .lrat_epilogue

		.lrat_not_last_index:

			# Condition
			# if(index > plist->size)
			movl index_liatp(%ebp), %edx
			movl plist_lratp(%ebp), %ebx
			movl list_size(%ebx), %eax

			cmpl %eax, %edx

			jl .lrat_index_not_out_of_bound

				.lrat_index_out_of_bound:

					pushl $.msg_p_e_iob
					call printf
					addl $4, %esp

					movl $0, %eax

					jmp .lrat_epilogue

			.lrat_index_not_out_of_bound:

				# p_node_t prunner = plist->p_head->p_next;
				movl plist_lratp(%ebp), %eax
				movl list_p_head(%eax), %eax
				movl node_p_next(%eax), %edx
				movl %edx,prunner_lratl(%ebp)

				# Loop Initialization
				movl $0, le_lratl(%ebp)

				# For Loop
				.loop_lrat:

					# Loop Condition
					# le < index;
					movl le_lratl(%ebp), %eax
					movl index_lratp(%ebp), %edx

					cmpl %edx, %eax

					jge .loop_end_lrat

						# Loop Body
						# prunner = prunner->p_next;
						movl prunner_lratl(%ebp), %eax
						movl node_p_next(%eax), %ebx
						movl %ebx, prunner_lratl(%ebp)

						# Increment
						incl le_lratl(%ebp)

						jmp .loop_lrat

				.loop_end_lrat:

				# return( list_generic_remove(plist, prunner) );

				pushl prunner_lratl(%ebp)
				pushl plist_lratp(%ebp)
				call list_generic_remove
				addl $8, %esp

	.lrat_epilogue:

		addl $8, %esp

		movl %ebp, %esp
		popl %ebp
		ret


#
# FUNCTION NAME: LIST_DATA_AT
# DESCRIPTION: 	GIVES THE DATA FROM GIVEN INDEX				
# INPUT: 1. POINTER TO A LIST
#  		   2. INDEX
# RETURN: DATA FROM REQUIRED NODE - IF FOUND SUCCESSFULLY
#  		    NULL - IF UNSUCCESSFULL
#

# extern data_t	list_data_at(p_mv_dcll_t plist, long index)

  .globl list_data_at
  .type list_data_at, @function

  # input parameter
  .equ plist_ldap, 8
  .equ index_ldap, 12

  # local variable
  .equ prunner_ldal, -4
  .equ le_ldal,      -8

list_data_at:

	# Prologue
	pushl %ebp
	movl %esp, %ebp

	subl $8, %esp
	movl $0, prunner_ldal(%ebp)

	# List Data At Main Code

	# Condition 
	# if(NULL == plist)
	cmpl $0, plist_ldap(%ebp)

	jmp .lda_list_present

		.lda_list_not_found:

			pushl $.msg_p_e_lnf
			call printf
			addl $4, %esp

			movl $0, %eax

			jmp .lda_epilogue

	.lda_list_present:

		# Condition
		# (0 == plist->size)
		movl $0, %ebx

		movl plist_ldap(%ebp), %eax
		movl list_size(%eax), %edx

		cmpl %edx, %eax

		je .lda_list_not_found
		jmp .lda_index_not_zero

		.lda_index_not_zero:

			# Condition
			# (index >= plist->size)
			movl index_ldap(%ebp), %ebx

			movl plist_ldap(%ebp), %eax
			movl list_size(%eax), %ecx

			cmpl %ecx, %ebx

			jl .lda_index_not_out_of_bound

				.lda_index_out_of_bound:

					pushl $.msg_p_e_iob
					call printf
					addl $4, %esp

					movl $0, %eax

					jmp .lda_epilogue

			.lda_index_not_out_of_bound:

				# p_node_t prunner = plist->p_head->p_next;
				movl plist_ldap(%ebp), %eax
				movl list_p_head(%eax), %eax
				movl node_p_next(%eax), %edx
				movl %edx, prunner_ldal(%ebp)

				# Initialization
				movl $0, le_ldal(%ebp)

				# For loop
				.loop_lda:

					# Condition 
					# le < index;
					movl le_ldal(%ebp), %eax
					movl index_ldap(%ebp), %edx

					cmpl %edx, %eax

					jge .loop_end_lda

						# Loop Body
						# prunner = prunner->p_next;
						movl prunner_ldal(%ebp), %eax
						movl node_p_next(%eax), %ebx
						movl %ebx, prunner_ldal(%ebp)

						# Increment
						incl le_ldal(%ebp)	

						jmp .loop_lda

				.loop_end_lda:

				# return(prunner->data);
				movl prunner_ldal(%ebp), %eax
				movl node_data(%eax), %edx
				movl %edx, %eax

	.lda_epilogue:

		addl $8, %esp

		movl %ebp, %esp
		popl %ebp
		ret


#
# FUNCTION NAME: LIST_SIZE
# DESCRIPTION: 	GIVES THE SIZE OF LIST				
# INPUT: 1. POINTER TO A LIST
# RETURN: SIZE OF LIST
#  		    FAILURE - IF LIST NOT PRESENT
#

# extern	size_t	list_size(p_mv_dcll_t plist)
  
  .globl list_size_ls
  .type list_size_ls, @function

  # input parameter
  .equ plist_lszp, 8

  # local parameter

list_size_ls:

	# Prologue
	pushl %ebp
	movl %esp, %ebp

	# List Size Main Code

	# Condition 
	# if(NULL == plist)
	cmpl $0, plist_lszp(%ebp)

	jne .list_present_lsz

		.lsz_list_not_found:

			pushl $.msg_p_e_lnf
			call printf
			addl $4, %esp

			movl $0, %eax

			jmp .lsz_epilogue

	.list_present_lsz:

		# return(plist->size);
		movl plist_lszp(%ebp), %eax
		movl list_size(%eax), %ebx

		movl %ebx, %eax 

	.lsz_epilogue:

		movl %ebp, %esp
		popl %ebp
		ret


#
# FUNCTION NAME: LIST_SHOW
# DESCRIPTION: 	PRINTS THE GIVEN LIST'S DATA 			
# INPUT: 1. POINTER TO A LIST
#  		   2. POINTER TO A PRINT FUNCTION 
# RETURN: SUCCESS - IF PRINTED SUCCESSFULLY
#  		    FAILURE - IF UNSUCCESSFULL
#

	.globl list_show
	.type  list_show, @function

	# Input Parameter
	.equ plist_lsp, 8
	.equ pprintdataproc_lsp, 12

	# Local Variable 
	.equ prunner_lsl, -4	

list_show:

	# Prologue 
	pushl %ebp
	movl %esp, %ebp

	subl $4, %esp

	movl $0, prunner_lsl(%ebp)

	# List Show Main Code

	cmpl $0, plist_lsp(%ebp)

	jne .list_present_ls

		# True Block
		pushl $.msg_p_e_lnf
		call printf
		addl $4, %esp

		movl $FAILURE, %eax

		jmp .ls_epilogue

	.list_present_ls:

		pushl $.msg_p_dcll
		call printf
		addl $4, %esp

		pushl $.msg_p_start
		call printf
		addl $4, %esp

		# For Loop
		# Loop Initialization
		# p_node_t prunner = plist->p_head->p_next;
		movl plist_lsp(%ebp), %eax
		movl list_p_head(%eax), %eax
		movl node_p_next(%eax), %edx

		movl %edx, prunner_lsl(%ebp)

		# Loop
		.loop_ls:

			# Loop Condition
			# prunner != plist->p_head;
			movl plist_lsp(%ebp), %eax
			movl list_p_head(%eax), %ebx

			cmpl %ebx, prunner_lsl(%ebp)

			je .loop_end_ls

				# True Block
				# pprintdataproc( prunner->data );
				movl prunner_lsl(%ebp), %eax
				pushl node_data(%eax)
				movl pprintdataproc_lsp(%ebp), %eax
				call *%eax
				addl $4, %esp

				# prunner = prunner->p_next;
				movl prunner_lsl(%ebp), %eax
				movl node_p_next(%eax), %ebx

				movl %ebx, prunner_lsl(%ebp)

				jmp .loop_ls

			.loop_end_ls:

			pushl $.msg_p_end
			call printf
			addl $4, %esp

			movl $SUCCESS, %eax

		# Epilogue
		.ls_epilogue:
		addl $4, %esp

		movl %ebp, %esp
		popl %ebp
		ret


#
# FUNCTION NAME: LIST_DESTROY
# DESCRIPTION: 	DESTROYS THE LIST		
# INPUT: 1. POINTER TO POINTER A LIST
#   	   2. POINTER TO DELETE PRINT FUNCTION
# RETURN: SUCCESS - IF DESTROYED SUCCESSFULLY
#  		    FAILURE - IF UNSUCCESSFUL
#

# extern ret_t list_destroy( pp_mv_dcll_t pplist,  DELETEDATAPROC pdeletedataproc)

  .globl list_destroy
  .type list_destroy, @function

  # input parameter
  .equ pplist_ldp,          8
  .equ pdeletedataproc_ldp, 12

  # local parameter
  .equ prunner_ldl,      -4
  .equ plist_ldl,        -8
  .equ prunner_next_ldl, -12

list_destroy:

	# Prologue
	pushl %ebp
	movl %esp, %ebp 

	subl $12, %esp
	movl $0, prunner_ldl(%esp)
	movl $0, plist_ldl(%esp)
	movl $0, prunner_next_ldl(%esp)

	# List Destroy Main Code

	# Condition 
	# if(NULL == pplist)
	cmpl $0, pplist_ldp(%ebp)

	jmp .pplist_present_ld

		.ld_list_not_found:

			pushl $.msg_p_e_lnf
			call printf
			addl $4, %esp

			movl $FAILURE, %eax

			jmp .ld_epilogue

	.pplist_present_ld:

		# p_mv_dcll_t plist = *pplist;
		movl pplist_ldp(%ebp), %eax
		movl (%eax), %eax
		movl %eax, plist_ldl(%ebp)

		# Condition
		# if(NULL == plist)
		cmpl $0, plist_ldl(%ebp)

		jne .plist_present_ld

			jmp .ld_list_not_found

		.plist_present_ld:

			# Loop Initialize
			# p_node_t prunner = plist->p_head;
			movl plist_ldl(%ebp), %eax
			movl list_p_head(%eax), %eax
			movl node_p_next(%eax), %edx
			movl %edx, prunner_ldl(%ebp)

			# For Loop
			.loop_ld:

				# Loop Condition
				movl  prunner_ldl(%ebp), %eax
				movl plist_ldl(%ebp), %ebx
				movl list_p_head(%ebx), %ecx

				cmpl %eax, %ecx

				je .loop_end_ld 

					# Loop Body
					# p_node_t prunner_next = prunner->p_next;
					movl prunner_ldl(%ebp), %ebx
					movl node_p_next(%ebx), %ecx
					movl %ecx, prunner_next_ldl(%ebp)

					# pdeletedataproc(prunner->data);
					movl prunner_ldl(%ebp), %eax
					pushl node_data(%eax)

					movl pdeletedataproc_ldp(%ebp), %eax
					call *%eax
					addl $4, %esp

					# prunner->data = NULL;
					movl prunner_ldl(%ebp), %eax
					movl $0, node_data(%eax)

					# free(prunner);
					pushl prunner_ldl(%ebp)
					call free
					addl $4, %esp

					# prunner = prunner_next;
					movl prunner_next_ldl(%ebp), %edx
					movl %edx, prunner_ldl(%ebp)

					jmp .loop_ld
			
			.loop_end_ld:

			# Condition
			# if(plist->p_head)
			movl plist_ldl(%ebp), %eax
			movl list_p_head(%eax), %edx

			movl $0, %ebx

			cmpl %edx, %ebx

			je .phead_not_present
	
				# free(plist->p_head);
				movl plist_ldl(%ebp), %eax
				pushl list_p_head(%eax)
				call free
				addl $4, %esp

				# plist->p_head = NULL;
				movl plist_ldl(%ebp), %eax
				movl $0, list_p_head(%eax)

			.phead_not_present:

				cmpl $0, plist_ldl(%ebp) 

				je .plist_not_present
				
					# free(plist);
					pushl plist_ldl(%ebp)
					call free
					addl $4, %esp

					# plist = NULL;
					movl $0, plist_ldl(%ebp)	 

			.plist_not_present:

					# *pplist = NULL;
					movl pplist_ldp(%ebp), %eax
					movl $0, (%eax)

				# return(SUCCESS);
				movl $SUCCESS, %ebx
				movl %ebx, %eax

	.ld_epilogue:

		addl $12, %esp

		movl %esp, %ebp
		popl %ebp
		ret


#
# FUNCTION NAME: MV_PRINTDATA ( CALLBACK FUNCTIONS )
# DESCRIPTION: 	PRINTS THE INPUT DATA
# INPUT: 1. DATA_CPL
# RETURN: VOID
#


  .globl printdata
  .type printdata, @function

  # input parameter
  .equ data_pdp, 8

printdata:

	# Prologue
	pushl %ebp
	movl %esp, %ebp

	#  Printdata Main Code
	pushl data_pdp(%ebp)
	pushl $.msg_p_printdata	
	call printf
	addl $8, %esp

	# Epilogue
	movl %ebp, %esp
	popl %ebp
	ret


#
# FUNCTION NAME: MV_COMPARE_PROC ( CALLBACK FUNCTIONS )
# DESCRIPTION: 	COMPARE TWO INPUT DATA ARE EQUAL OR NOT
# INPUT: 1. DATA1_CPL
# 		 2. DATA2_CPL
# RETURN: 0(SUCCESS) IF SAME
# 		  1(FAILURE) IF DIFFERENT
#

# ret_t	compareproc(data_t data1, data_t data2)

   .globl compareproc 
   .type compareproc, @function
 
   # input parameters
   .equ data1_cp, 8
   .equ data2_cp, 12

compareproc:

	# Prologue
	pushl %ebp
	movl %esp, %ebp

	# Compareproc Main Code

	# condition
	# (long long)data1 == (long long)data2
	movl data1_cp(%ebp), %eax
	movl data2_cp(%ebp), %edx

	cmpl %eax, %edx

	jne .cp_return_failure

		movl $SUCCESS, %eax

		jmp .cp_epilogue

	.cp_return_failure:

		movl $FAILURE, %eax

	# Epilogue 
	.cp_epilogue:

		movl %ebp, %esp
		popl %ebp
		ret


#
# FUNCTION NAME: MV_DELETEDATA ( CALLBACK FUNCTION )
# DESCRIPTION: 	PRINTS THE INPUT DATA
# INPUT: 1. DATA_CPL
# RETURN: VOID
#

# void deletedata(data_t data)

  .globl deletedata
  .type deletedata, @function

  # input parameter
  .equ data_ddp, 8

deletedata:

	# prologue
	pushl %ebp
	movl %esp, %ebp

	# Deletedata Main Code
	pushl data_ddp(%ebp)
	pushl $.msg_p_deletedata
	call printf
	addl $8, %esp

	# Epilogue
	movl %ebp, %esp
	popl %ebp
	ret

#--------------------------------------------------------------------------------#
#
# FUNCTION NAME: _START ( ENTRY POINT FUNCTION )
# DESCRIPTION: 	ENTRY POINT FUNCTION, ALL MANIPULATION WILL BE DONE 
#  							HERE
# INPUT: VOID
# RETURN: EXIT - SUCCESS
#

# Main Function 
  .globl _start
  .type _start, @function 

  # input parameter

  # local variable
  .equ plist_ml, -4
  .equ le_ml, -8

_start:

	# Prologue
	pushl %ebp
	movl %esp, %ebp

	# _start Main Code

	subl $8, %esp

	call create_list

	movl %eax, plist_ml(%ebp)

		# Insert Front

		# Loop Initialization
		movl $0, le_ml(%ebp)

		.loop_main_lif:

			# Loop Condition
			cmpl $20, le_ml(%ebp)

			jge .loop_end_lif

				# Loop Body
				movl le_ml(%ebp), %eax
				addl $1, %eax
				pushl %eax
				pushl plist_ml(%ebp)
				call list_insert_front
				addl $8, %esp

				# Increment
				incl le_ml(%ebp)

				jmp .loop_main_lif

		.loop_end_lif:

		pushl $.msg_p_aif
		call printf
		addl $4, %esp

		pushl $printdata
		pushl plist_ml(%ebp)
		call list_show
		addl $8, %esp


		# Insert Back

		# Loop Initialization
		movl $0, le_ml(%ebp)

		.loop_main_lib:

			# Loop Condition
			cmpl $10, le_ml(%ebp)

			jge .loop_end_lib

				# Loop Body
				movl le_ml(%ebp), %eax
				addl $1, %eax
				imull $5, %eax
				pushl %eax

				pushl plist_ml(%ebp)
				call list_insert_back
				addl $8, %esp

				# Increment	
				incl le_ml(%ebp)

				jmp .loop_main_lib

		.loop_end_lib: 

		pushl $.msg_p_aib
		call printf
		addl $4, %esp

		pushl $printdata
		pushl plist_ml(%ebp)
		call list_show
		addl $8, %esp


		# Insert Before 

		pushl $compareproc
		pushl $4
		pushl $1234
		pushl plist_ml(%ebp)

		call list_insert_before
		addl $16, %esp


		pushl $.msg_p_aibf
		call printf
		addl $4, %esp

		pushl $printdata
		pushl plist_ml(%ebp)
		call list_show
		addl $8, %esp


		# Insert After

		pushl $compareproc
		pushl $7
		pushl $4321
		pushl plist_ml(%ebp)
		
		call list_insert_after
		addl $16, %esp

		pushl $.msg_p_aiaf
		call printf
		addl $4, %esp

		pushl $printdata
		pushl plist_ml(%ebp)
		call list_show
		addl $8, %esp

		# Insert At

		pushl $2
		pushl $5555
		pushl plist_ml(%ebp)
		call list_insert_at
		addl $12, %esp

		pushl $.msg_p_aiat
		call printf
		addl $4, %esp

		pushl $printdata
		pushl plist_ml(%ebp)
		call list_show
		addl $8, %esp


		# Remove Front

		pushl plist_ml(%ebp)
		call list_remove_front
		addl $4, %esp

		pushl $.msg_p_arf
		call printf
		addl $4, %esp

		pushl $printdata
		pushl plist_ml(%ebp)
		call list_show
		addl $8, %esp

		# Remove Back

		pushl plist_ml(%ebp)
		call list_remove_back
		addl $4, %esp

		pushl $.msg_p_arb
		call printf
		addl $4, %esp

		pushl $printdata
		pushl plist_ml(%ebp)
		call list_show
		addl $8, %esp

		# Remove Before

		pushl $compareproc
		pushl $17
		pushl plist_ml(%ebp)
		call list_remove_before
		addl $12, %esp 

		pushl $.msg_p_arbf
		call printf
		addl $4, %esp

		pushl $printdata
		pushl plist_ml(%ebp)
		call list_show
		addl $8, %esp


		# Remove After

		pushl $compareproc
		pushl $5
		pushl plist_ml(%ebp)
		call list_remove_after
		addl $12, %esp 

		pushl $.msg_p_araf
		call printf
		addl $4, %esp

		pushl $printdata
		pushl plist_ml(%ebp)
		call list_show
		addl $8, %esp


		# Remove At

		pushl $5
		pushl plist_ml(%ebp)
		call list_remove_at
		addl $8, %esp

		pushl $.msg_p_arat
		call printf
		addl $4, %esp

		pushl $printdata
		pushl plist_ml(%ebp)
		call list_show
		addl $8, %esp


		# List Destroy

		pushl $deletedata
		leal plist_ml(%ebp), %ecx
		pushl %ecx
		call list_destroy
		addl $8, %esp


	# Epilogue 
	addl $8, %esp

	pushl $0
	call exit

