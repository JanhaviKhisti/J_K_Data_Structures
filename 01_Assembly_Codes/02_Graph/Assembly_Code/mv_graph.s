
# pushl $.msg_p_g_here1
# call printf
# addl $4, %esp

#****************************************#
.file "mv_graph.s"

# Constant Literal

 #define SUCCESS 0
  .equ SUCCESS, 0

 #define FAILURE 1
  .equ FAILURE, 1


# struct vertex
#{
# 	data_t vertex_data;
#	p_mv_dcll_t edges;
#
#};
#define SIZE_VERTEX (sizeof(vertex_t))

.equ vertex_data,  0
.equ vertex_edges, 4
.equ SIZE_VERTEX , 8

#struct edge
#{
#	p_vertex_t vertex;
#	size_t weight;
#};
#define SIZE_EDGE (sizeof(edge_t))

.equ edge_vertex, 0
.equ edge_weight, 4
.equ SIZE_EDGE,   8

#struct mv_graph
#{
#	p_mv_dcll_t vertices;
#	int type;
#};
#define SIZE_GRAPH (sizeof(mv_graph_t))

.equ graph_vertices, 0
.equ graph_type,     4
.equ SIZE_GRAPH,     8

# enum
# {
# 	GRAPH_NONE = 0,
# 	GRAPH_DIRECTED,
# 	GRAPH_UNDIRECTED
# };

.equ GRAPH_NONE,       0
.equ GRAPH_DIRECTED,   1
.equ GRAPH_UNDIRECTED, 2


# SECTION RODATA
.section .rodata

# Error Message for Out Of Memory
.msg_p_g_e_oom:
    .string "ERROR : Out Of Memory\n"

# Error Message for Graph Not Found To Insert Vertex
.msg_p_g_e_gnfiv:
    .string "ERROR : Graph Not Found to Insert Vertex\n"

    # Error Message for Graph Not Found 
.msg_p_g_e_gnf:
    .string "ERROR : Graph Not Found\n"

# Error Message for Data Already Exits
.msg_p_g_e_dae:
    .string "ERROR : Data Already Exists\n"

.msg_p_g_graph:
    .string "\nGRAPH:\n"

.msg_p_g_vdata:
    .string "%ld"

.msg_p_g_edata:
    .string "%ld/%lu"

.msg_p_g_start:
    .string "{START}"

.msg_p_g_bar:
    .string "\n | \n"

.msg_p_g_qb1:
    .string "{"

.msg_p_g_qb2:
    .string "}->"

.msg_p_g_end:
    .string "{END}"

.msg_p_g_here1:
    .string "HERE-1\n"

.msg_p_g_data:
    .string "%d\n"


# Section Text
.section .text

# Xmalloc Function

# static void* Xmalloc(size_t no_of_bytes)    
  .type Xmalloc_graph, @function

  # Input Parameter
  .equ no_of_bytes_xmp, 8

  # Local Variable
  .equ p_xml, -4

Xmalloc_graph:

    # Prologue 
    pushl %ebp
    movl %esp, %ebp

    # Xmalloc Main Code

    # void* p = malloc(no_of_bytes);
    pushl no_of_bytes_xmp(%ebp)
    call malloc
    addl $4, %esp

    movl %eax, p_xml(%ebp)

    # if( NULL == p )
    cmpl $0, p_xml(%ebp)

    jne .normal_execution_xmalloc

        # True Block 
        pushl $.msg_p_g_e_oom
        call printf
        addl $4, %esp

        # exit(FAILURE);
        pushl $FAILURE
        call exit 

    .normal_execution_xmalloc:

    # return(p);
    movl p_xml(%ebp), %eax

    # Epilogue
    movl %ebp, %esp
    popl %ebp
    ret



# Create Vertex Function

# static p_vertex_t create_vertex(data_t data)

  .type create_vertex, @function

  # Input Parameter 
  .equ data_cvp, 8

  # Local Variable
  .equ pvertex_cvl, -4

create_vertex:

    # Prologue 
    pushl %ebp
    movl %esp, %ebp

    subl $4, %esp
    movl $0, pvertex_cvl(%ebp)

    # Create Vertex Main Code

    # p_vertex_t pvertex = (p_vertex_t)Xmalloc(SIZE_VERTEX);
    pushl $SIZE_VERTEX
    call Xmalloc_graph
    addl $4, %esp

    movl %eax, pvertex_cvl(%ebp)

    # pvertex->vertex_data = data;
    movl data_cvp(%ebp), %ebx

    movl pvertex_cvl(%ebp), %ecx
    movl %ebx, vertex_data(%ecx)

    # pvertex->edges = create_list();
    movl pvertex_cvl(%ebp), %ebx

    call create_list
    movl %eax, vertex_edges(%ebx)

    # return(pvertex);
    movl pvertex_cvl(%ebp), %eax

    # Epilogue
    addl $4, %esp

    movl %ebp, %esp
    popl %ebp
    ret 



# Create Edge Function

# static p_edge_t create_edge(p_vertex_t pvertex, size_t edge_weight)

  .type create_edge, @function

  # input parameters
  .equ pvertex_cep, 8
  .equ edge_weight_cep,  12

  # local variable
  .equ pedge_cel, -4

create_edge:

    # Prologue 
    pushl %ebp
    movl %esp, %ebp

    subl $4, %esp

    # Create Edge Main Code

    # p_edge_t pedge = (p_edge_t)Xmalloc(SIZE_EDGE);
    pushl $SIZE_EDGE
    call Xmalloc_graph
    addl $4, %esp

    movl %eax, pedge_cel(%ebp)

    # pedge->vertex = pvertex;
    movl pvertex_cep(%ebp), %ecx
    movl pedge_cel(%ebp), %ebx
    movl %ecx, edge_vertex(%ebx)

    # pedge->weight = edge_weight;
    movl edge_weight_cep(%ebp), %ecx
    movl pedge_cel(%ebp), %ebx
    movl %ecx, edge_weight(%ebx)

    # return(pedge);
    movl pedge_cel(%ebp), %eax

    # Epilogue 
    addl $4, %esp

    movl %ebp, %esp
    popl %ebp
    ret



# Locate Vertex Function 

# static p_vertex_t locate_vertex(p_mv_graph_t pgraph, data_t new_data, COMPAREPROC pcompareproc)

  .type locate_vertex, @function

  # Input Parameters
  .equ pgraph_lvp,       8
  .equ new_data_lvp,     12
  .equ pcompareproc_lvp, 16

  # Local Variables
  .equ size_lvl,    -4
  .equ le_lvl,      -8
  .equ pvertex_lvl, -12

locate_vertex:

    # Prologue 
    pushl %ebp
    movl %esp, %ebp

    subl $12, %esp

    # Locate Vertex Main Code

    # long size = list_size(pgraph->vertices);
    movl pgraph_lvp(%ebp), %eax
    pushl graph_vertices(%eax)
    call list_size_ls
    addl $4, %esp

    movl %eax, size_lvl(%ebp)

    # For Loop
    # Loop Initialization
    movl $0, le_lvl(%ebp)

    # Loop
    .loop_lvl:

        # Loop Condition
        # le < size;
        movl size_lvl(%ebp), %ebx
        movl le_lvl(%ebp), %ecx

        cmpl %ebx, %ecx

        jge .loop_end_lvl

            # Loop Body
            # p_vertex_t pvertex = list_data_at(pgraph->vertices, le);
            pushl le_lvl(%ebp)
            
            movl pgraph_lvp(%ebp), %eax
            pushl graph_vertices(%eax)
            call list_data_at
            addl $8, %esp

            movl %eax, pvertex_lvl(%ebp)

            # if( SUCCESS == pcompareproc(new_data, pvertex->vertex_data) )
            movl pvertex_lvl(%ebp), %eax
            pushl vertex_data(%eax)
            pushl new_data_lvp(%ebp)

            movl pcompareproc_lvp(%ebp), %eax
            call *%eax
            addl $8, %esp

            movl $SUCCESS, %ebx

            cmpl %ebx, %eax

            jne .loop_increment_lvl

                # return(pvertex);
                movl pvertex_lvl(%ebp), %eax
                jmp .epilogue_lvl

            .loop_increment_lvl:
                # ++le
                incl le_lvl(%ebp)

            jmp .loop_lvl

    .loop_end_lvl:
    
    # return(NULL);
    movl $0, %eax

    # Epilogue
    .epilogue_lvl:

    addl $12, %esp

    movl %ebp, %esp
    popl %ebp
    ret



# Generic Insert Directed Edge Function

# static ret_t generic_insert_directed_edge(p_vertex_t pvertex1, p_vertex_t pvertex2, size_t edge_weight)

  .type generic_insert_directed_edge, @function

  # input parameters
  .equ pvertex1_gidep,    8
  .equ pvertex2_gidep,    12
  .equ edge_weight_gidep, 16

  # local variables
  .equ edge_1_gidel, -4

generic_insert_directed_edge:

    # Prologue 
    pushl %ebp
    movl %esp, %ebp

    subl $4, %esp

    # Generic Insert Directed Edge Main Code

    # p_edge_t edge_1 = create_edge(pvertex2, edge_weight);
    pushl edge_weight_gidep(%ebp)
    pushl pvertex2_gidep(%ebp)
    call create_edge
    addl $8, %esp

    movl %eax, edge_1_gidel(%ebp)

    # list_insert_back( pvertex1->edges, edge_1);
    pushl edge_1_gidel(%ebp)
    movl pvertex1_gidep(%ebp), %eax
    pushl vertex_edges(%eax)
    call list_insert_back
    addl $8, %esp

    # return(SUCCESS);
    movl $SUCCESS, %eax

    # Epilogue
    addl $4, %esp

    movl %ebp, %esp
    popl %ebp
    ret



# Generic Insert Undirected Edge Function 

# static ret_t generic_insert_undirected_edge(p_vertex_t pvertex1, p_vertex_t pvertex2, size_t edge_weight)

   .type generic_insert_undirected_edge, @function

  # Input Parameters
  .equ pvertex1_giuep,    8
  .equ pvertex2_giuep,    12
  .equ edge_weight_giuep, 16

  # Local Variables
  .equ edge_1_giuel, -4
  .equ edge_2_giuel, -8

generic_insert_undirected_edge:

    # Prologue
    pushl %ebp
    movl %esp, %ebp

    subl $8, %esp
    movl $0, edge_1_giuel(%ebp)
    movl $0, edge_2_giuel(%ebp)

    # Generic Insert Undirected Edge Main Code

    # p_edge_t edge_1 = create_edge(pvertex2, edge_weight);
    pushl edge_weight_giuep(%ebp)
    pushl pvertex2_giuep(%ebp)
    call create_edge
    addl $8, %esp

    movl %eax, edge_1_giuel(%ebp)

    # list_insert_back( pvertex1->edges, edge_1);
    pushl edge_1_giuel(%ebp)
    movl pvertex1_giuep(%ebp), %eax
    pushl vertex_edges(%eax)
    call list_insert_back
    addl $8, %esp

    # p_edge_t edge_2 = create_edge(pvertex1, edge_weight);
    pushl edge_weight_giuep(%ebp)
    movl pvertex1_giuep(%ebp), %eax
    pushl vertex_edges(%eax)
    call create_edge
    addl $8, %esp

    movl %eax, edge_2_giuel(%ebp)

    # list_insert_back( pvertex2->edges, edge_2);
    pushl edge_2_giuel(%ebp)
    movl pvertex2_giuep(%ebp), %eax
    pushl vertex_edges(%eax)
    call list_insert_back
    addl $8, %esp

    # return(SUCCESS);
    movl $SUCCESS, %eax

    # Epilogue 
    addl $8, %esp

    movl %ebp, %esp
    popl %ebp
    ret




# Delete Edge Function

# static void delete_edge(data_t data);

  .type delete_edge, @function

  # input parameter
  .equ data_dep, 8

  # local variable
  .equ pedge_del, -4

delete_edge:

    # Prologue 
    pushl %ebp
    movl %esp, %ebp

    subl $4, %esp

    # Delete Edge Main Code

    # p_edge_t pedge = (p_edge_t) data;
    movl data_dep(%ebp), %eax
    movl %eax, pedge_del(%ebp)

    # free(pedge);
    pushl pedge_del(%ebp)
    call free
    addl $4, %esp

    # pedge = NULL;
    movl $0, pedge_del(%ebp)

    # Epilogue
    addl $4, %esp

    movl %ebp, %esp
    popl %ebp
    ret



# Create Graph Function

# extern  p_mv_graph_t  create_graph(int graph_type)

  .globl create_graph
  .type  create_graph, @function

  # Input Parameter
  .equ graph_type_cgp, 8

  # Local Variable
  .equ pgraph_cgl, -4 

create_graph:

    # Prologue 
    pushl %ebp
    movl %esp, %ebp

    subl $4, %esp

    # Create Graph Main Code

    # p_mv_graph_t pgraph = (p_mv_graph_t)Xmalloc(SIZE_GRAPH);
    pushl $SIZE_GRAPH
    call Xmalloc_graph
    addl $4, %esp

    movl %eax, pgraph_cgl(%ebp)

    # pgraph->vertices = create_list();
    call create_list

    movl %eax, %ebx

    movl pgraph_cgl(%ebp), %edx
    movl %ebx, graph_vertices(%edx)

    # pgraph->type = graph_type;
    movl pgraph_cgl(%ebp), %eax
    movl graph_type(%eax), %ebx

    movl graph_type_cgp(%ebp), %edx

    movl %ebx, %edx

    # return(pgraph);
    movl pgraph_cgl(%ebp), %eax

    # Epilogue
    addl $4, %esp

    movl %ebp, %esp
    popl %ebp
    ret



# Graph Insert Vertex Function

# extern ret_t mv_graph_insert_vertex(p_mv_graph_t pgraph, data_t  new_data, COMPAREPROC pcompareproc)

  .globl mv_graph_insert_vertex
  .type  mv_graph_insert_vertex, @function

  # Input Parameters
  .equ pgraph_mgivp,       8
  .equ new_data_mgivp,     12
  .equ pcompareproc_mgivp, 16

  # Local Variable
  .equ new_vertex_mgivl, -4
  .equ pvertex_mgivl,    -8

mv_graph_insert_vertex:

    # Prologue
    pushl %ebp
    movl %esp, %ebp

    subl $8, %esp

    # Graph Insert Vertex Main Code

    # if( !pgraph )
    cmpl $0, pgraph_mgivp(%ebp)
    jne .pgraph_present_mgiv

        # Error Message 
        pushl $.msg_p_g_e_gnfiv
        call printf
        addl $4, %esp

        # return(FAILURE);
        movl $FAILURE, %eax
        jmp .epilogue_mgiv

    .pgraph_present_mgiv:

    # if( !list_size(pgraph->vertices) )
    movl pgraph_mgivp(%ebp), %eax
    pushl graph_vertices(%eax)
    call list_size_ls
    addl $4, %esp

    cmpl $0, %eax

    jne .vertex_present_mgiv

        # p_vertex_t new_vertex = create_vertex(new_data);
        pushl new_data_mgivp(%ebp)
        call create_vertex
        addl $4, %esp

        movl %eax, new_vertex_mgivl(%ebp)

        # list_insert_back(pgraph->vertices, new_vertex);
        pushl new_vertex_mgivl(%ebp)
        movl pgraph_mgivp(%ebp), %eax
        pushl graph_vertices(%eax)
        call list_insert_back
        addl $8, %esp

        jmp .return_mgivp

    .vertex_present_mgiv:

    # p_vertex_t pvertex = locate_vertex(pgraph, new_data, pcompareproc);
    pushl pcompareproc_mgivp(%ebp)
    pushl new_data_mgivp(%ebp)
    pushl pgraph_mgivp(%ebp)
    call locate_vertex
    addl $12, %esp

    movl %eax, pvertex_mgivl(%ebp)

    # if( pvertex )
    cmpl $0, pvertex_mgivl(%ebp)

    je .vertex_not_present_mgiv

        # Error Message
        pushl $.msg_p_g_e_dae
        call printf
        addl $4, %esp

        # return(FAILURE);
        movl $FAILURE, %eax
        jmp .epilogue_mgiv

    .vertex_not_present_mgiv:

    # pvertex = create_vertex(new_data);
    pushl new_data_mgivp(%ebp)
    call create_vertex
    addl $4, %esp

    movl %eax, pvertex_mgivl(%ebp)

    # list_insert_back(pgraph->vertices, pvertex);
    pushl pvertex_mgivl(%ebp)
    movl pgraph_mgivp(%ebp), %eax
    pushl graph_vertices(%eax)
    call list_insert_back
    addl $8, %esp

    .return_mgivp:

    # return(SUCCESS);
    movl $SUCCESS, %eax

    # Epilogue 
    .epilogue_mgiv:

    addl $8, %esp

    movl %ebp, %esp
    popl %ebp
    ret



# Graph Show Function

# extern    ret_t   mv_graph_show(p_mv_graph_t pgraph, SHOWVERTEXDATAPROC pshowvertexdataproc, SHOWEDGEDATAPROC pshowedgedataproc)

  .globl mv_graph_show 
  .type  mv_graph_show, @function                     

  # Input Parameters
  .equ pgraph_gsp,              8
  .equ pshowvertexdataproc_gsp, 12
  .equ pshowedgedataproc_gsp,   16

  # Local Variables
  .equ pvertex_gsl,       -4
  .equ vertices_size_gsl, -8
  .equ edges_size_gsl,    -12
  .equ pedge_gsl,         -16
  .equ ole_gsl,           -20
  .equ ile_gsl,           -24

mv_graph_show:

    # Prologue 
    pushl %ebp
    movl %esp, %ebp

    subl $24, %esp
    # Graph Show Main Code

    # if(cond1: !pgraph ||)
    cmpl $0, pgraph_gsp(%ebp)

    jne .pgraph_present_gs

        .graph_not_found_gs:

        # Error Message 
        pushl $.msg_p_g_e_gnf
        call printf
        addl $4, %esp

        # return(FAILURE);
        movl $FAILURE, %eax
        jmp .epilogue_gs

    .pgraph_present_gs:

    # if(cond2: !list_size(pgraph->vertices)
    movl pgraph_gsp(%ebp), %eax
    pushl graph_vertices(%eax)
    call list_size_ls
    addl $4, %esp

    cmpl $0, %eax

    je .graph_not_found_gs

    # long vertices_size = list_size(pgraph->vertices);
    movl pgraph_gsp(%ebp), %eax
    pushl graph_vertices(%eax)
    call list_size_ls
    addl $4, %esp

    movl %eax, vertices_size_gsl(%ebp)

    # print "Graph"
    pushl $.msg_p_g_graph
    call printf
    addl $4, %esp

    # print "Start"
    pushl $.msg_p_g_start
    call printf
    addl $4, %esp

    # print "\n | \n"
    pushl $.msg_p_g_bar
    call printf
    addl $4, %esp

    # For Loop
    # Loop Initialization
    movl $0, ole_gsl(%ebp)

    # Outer Loop
    .loop_ole_gs:

        # Loop Condition
        # ole < vertices_size;
        movl vertices_size_gsl(%ebp), %ebx
        movl ole_gsl(%ebp), %eax

        cmpl %eax, %ebx

        jge .loop_end_ole_gs

            # Loop Body
            # p_vertex_t pvertex = list_data_at(pgraph->vertices, ole);
            pushl ole_gsl(%ebp)
            movl pgraph_gsp(%ebp), %eax
            pushl graph_vertices(%eax)
            call list_data_at
            addl $8, %esp

            movl %eax, pvertex_gsl(%ebp)

            # print "{"
            pushl $.msg_p_g_qb1
            call printf
            addl $4, %esp

            # pshowvertexdataproc( pvertex->vertex_data );
            movl pvertex_gsl(%ebp), %ebx
            pushl vertex_data(%ebx)
            movl pshowvertexdataproc_gsp(%ebp), %eax
            call *%eax
            addl $4, %esp

            # print "}"
            pushl $.msg_p_g_qb2
            call printf
            addl $4, %esp

            # long edges_size = list_size(pvertex->edges);
            movl pvertex_gsl(%ebp), %eax 
            pushl vertex_edges(%eax)
            call list_size_ls
            addl $4, %esp

            movl %eax, edges_size_gsl(%ebp)

            # Inner Loop 
            # Loop Initialization
            movl $0, ile_gsl(%ebp)

            # Loop
            .loop_ile_gs:

                # Loop Condition
                # ile < edges_size;
                movl edges_size_gsl(%ebp), %ebx
                movl ile_gsl(%ebp), %eax

                cmpl %eax, %ebx

                jge .loop_end_ile_gs

                    # Loop Body
                    # p_edge_t pedge = list_data_at(pvertex->edges, ile);
                    pushl ile_gsl(%ebp)
                    movl pvertex_gsl(%ebp), %eax
                    pushl vertex_edges(%eax)
                    call list_data_at
                    addl $8, %esp

                    movl %eax, pedge_gsl(%ebp)

                    # print "{"
                    pushl $.msg_p_g_qb1
                    call printf
                    addl $4, %esp

                    # pshowedgedataproc(pedge->vertex->vertex_data, pedge->weight);
                    movl pedge_gsl(%ebp), %eax
                    pushl edge_weight(%eax)

                    movl pedge_gsl(%ebp), %eax
                    movl edge_vertex(%eax),%eax
                    pushl vertex_data(%eax)

                    movl pshowedgedataproc_gsp(%ebp), %eax
                    call *%eax
                    addl $8, %esp

                    # print "}"
                    pushl $.msg_p_g_qb2
                    call printf
                    addl $4, %esp

                # Increment ile
                # ++ ile 
                incl ile_gsl(%ebp)
                jmp .loop_ile_gs

            .loop_end_ile_gs:

            # print "End"
            pushl $.msg_p_g_end
            call printf
            addl $4, %esp

            # print "\n | \n"
            pushl $.msg_p_g_bar
            call printf
            addl $4, %esp

        # Increment ole
        incl ole_gsl(%ebp)
        jmp .loop_ole_gs

    .loop_end_ole_gs:

    # print "End"
    pushl $.msg_p_g_end
    call printf
    addl $4, %esp

    # return(SUCCESS);
    movl $SUCCESS, %eax

    # Epilogue 
    .epilogue_gs:

    addl $24, %esp

    movl %ebp, %esp
    popl %ebp
    ret



# Compare Vertex Function

# ret_t compare_vertex(data_t data1, data_t data2)

  .globl compare_vertex
  .type  compare_vertex, @function

  # Input Parameters
  .equ data1_cv, 8
  .equ data2_cv, 12

  # Local Variable

compare_vertex:

    # Prologue
    pushl %ebp
    movl %esp, %ebp

    # Compare Vertex Main Code

    # if( (long long)data1 == (long long)data2 )
    movl data1_cv(%ebp), %ebx
    movl data2_cv(%ebp), %ecx

    cmpl %ecx, %ebx

    jne .return_cv

        # return(SUCCESS);
        movl $SUCCESS, %eax
        jmp .cv_epilogue

    .return_cv:

        # return(FAILURE);
        movl $FAILURE, %eax

    # Epilogue 
    .cv_epilogue:

    movl %ebp, %esp
    popl %ebp
    ret



# Show Vertex Function

# void  show_vertex(data_t data)

  .globl show_vertex
  .type show_vertex, @function

  # Input Parameter
  .equ data_sv, 8

  # Local Variable

show_vertex:

    # Prologue
    pushl %ebp
    movl %esp, %ebp

    # Show Vertex Main Code

    pushl data_sv(%ebp)
    pushl $.msg_p_g_vdata
    call printf
    addl $8, %esp

    # Epilogue
    movl %ebp, %esp
    popl %ebp
    ret



# Show Edge Function

# void  show_edge(data_t data, size_t weight)

    .globl show_edge
    .type show_edge, @function

    # Input Parameters
    .equ data_se,   8
    .equ weight_se, 12

    # Local Variable

show_edge:

    # Prologue
    pushl %ebp
    movl %esp, %ebp

    # Show Edge Main Code

    pushl weight_se(%ebp)
    pushl data_se(%ebp)
    pushl $.msg_p_g_edata
    call printf
    addl $12, %esp

    # Epilogue
    movl %ebp, %esp
    popl %ebp
    ret



# Main Function

    .globl _start_graph
    .type _start_graph, @function

    # input parameter

    # local variable
    .equ pgraph_ml, -4
    .equ le_ml, -8

_start_graph:
    
    # Prologue
    pushl %ebp
    movl %esp, %ebp

    subl $8, %esp

    # Main Code

    movl $0, pgraph_ml(%ebp)

    # pgraph = create_graph(GRAPH_UNDIRECTED);
    pushl $GRAPH_UNDIRECTED
    call create_graph
    addl $4, %esp

    movl %eax, pgraph_ml(%ebp)

    # Graph Insert Vertex

    # mv_graph_insert_vertex(pgraph, (data_t)(long long)(50), compare_vertex);
    pushl $compare_vertex
    pushl $50
    pushl pgraph_ml(%ebp)
    call mv_graph_insert_vertex
    addl $12, %esp

    # mv_graph_show(pgraph, show_vertex, show_edge);
    # pushl show_edge(%ebp)
    # pushl show_vertex(%ebp)
    # pushl pgraph_ml(%ebp)
    # call mv_graph_show
    # addl $12, %esp

    # Epilogue
    addl $8, %esp

    pushl $0
    call exit
