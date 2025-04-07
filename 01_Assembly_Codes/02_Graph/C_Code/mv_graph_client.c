

#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>

#include	"mv_graph.h"


p_mv_graph_t	pgraph = NULL;

ret_t	compare_vertex(data_t data1, data_t data2)
{
	// Code
	if( (long long)data1 == (long long)data2 )
		return(SUCCESS);

	return(FAILURE);
}


void	show_vertex(data_t data)
{
	// Code
	
	fprintf(stdout, "%lld", (long long)data);
}


void	show_edge(data_t data, size_t weight)
{
	// Code
	
	fprintf(stdout, "%lld/%lu", (long long)data, weight);
}

int main(void)
{
	// Code

	srand(time(0));

	pgraph = create_graph(GRAPH_UNDIRECTED);

	for( long le = 1; le <= 10; ++le  )
	{
		mv_graph_insert_vertex(pgraph, (data_t)(long long)(le*10), compare_vertex);
	}

	mv_graph_show(pgraph, show_vertex, show_edge);

	mv_graph_insert_vertex(pgraph, (data_t)(long long)(10), compare_vertex);
	mv_graph_insert_vertex(pgraph, (data_t)(long long)(50), compare_vertex);
	mv_graph_insert_vertex(pgraph, (data_t)(long long)(100), compare_vertex);
	mv_graph_insert_vertex(pgraph, (data_t)(long long)(110), compare_vertex);
	mv_graph_insert_vertex(pgraph, (data_t)(long long)(150), compare_vertex);
	mv_graph_insert_vertex(pgraph, (data_t)(long long)(250), compare_vertex);

	mv_graph_show(pgraph, show_vertex, show_edge);

	mv_graph_remove_vertex(pgraph, (data_t)(long long)(50), compare_vertex);
	mv_graph_remove_vertex(pgraph, (data_t)(long long)(90), compare_vertex);
	mv_graph_remove_vertex(pgraph, (data_t)(long long)(20), compare_vertex);
	mv_graph_remove_vertex(pgraph, (data_t)(long long)(110), compare_vertex);

	mv_graph_show(pgraph, show_vertex, show_edge);

	long no_of_edges = 1 + rand() % 50;

	for( long le = 0; le < no_of_edges; ++le )
	{

		long long v1 = 1 + rand() % 25;
		v1 *= 10;

		long long v2 = 1 + rand() % 25;
		v2 *= 10;

		mv_graph_insert_edge(pgraph, (data_t)(long long)(v1), (data_t)(long long)(v2), 1, compare_vertex);
	}

	mv_graph_show(pgraph, show_vertex, show_edge);

	long long remove_vertex = 0;

	remove_vertex = (long long)mv_graph_remove_vertex(pgraph, (data_t)(long long)(50), compare_vertex);
	fprintf(stdout, "\nRemoved Vertex = %lld\n", remove_vertex);

	remove_vertex = (long long)mv_graph_remove_vertex(pgraph, (data_t)(long long)(90), compare_vertex);
	fprintf(stdout, "\nRemoved Vertex = %lld\n", remove_vertex);

	remove_vertex = (long long)mv_graph_remove_vertex(pgraph, (data_t)(long long)(20), compare_vertex);
	fprintf(stdout, "\nRemoved Vertex = %lld\n", remove_vertex);
	
	remove_vertex = (long long)mv_graph_remove_vertex(pgraph, (data_t)(long long)(110), compare_vertex);
	fprintf(stdout, "\nRemoved Vertex = %lld\n", remove_vertex);

	mv_graph_show(pgraph, show_vertex, show_edge);

	exit(SUCCESS);
}

