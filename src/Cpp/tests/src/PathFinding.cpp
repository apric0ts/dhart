#include "gtest/gtest.h"

#include <memory>

#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/dijkstra_shortest_paths_no_color_map.hpp>
#include <boost/exception/exception.hpp>

#include <path_finder.h>
#include <boost_graph.h>
#include <graph.h>
#include <node.h>
#include <edge.h>
#include <path.h>

#include "pathfinder_C.h"

using namespace HF::SpatialStructures;
using namespace HF::Pathfinding;

TEST(_Pathfinding, BoostGraphCreation) {

	Graph g;
	g.addEdge(0, 1, 100);
	g.addEdge(0, 2, 50);
	g.addEdge(1, 3, 10);
	g.addEdge(2, 3, 10);

	g.Compress();
    std::unique_ptr<BoostGraph> bg = std::make_unique<BoostGraph>(BoostGraph(g));
	ASSERT_EQ(num_vertices(bg.get()->g),4);
}

TEST(_Pathfinding, SinglePath) {

	Graph g;
	g.addEdge(0, 1, 100);
	g.addEdge(0, 2, 50);
	g.addEdge(1, 3, 10);
	g.addEdge(2, 3, 10);
	g.Compress();

	//The optimal path here is 0->2->3
	std::vector<PathMember> OptimalPath = {
		{50,0},
		{10,2},
		{0,3}
	};
	Path OP(OptimalPath);

	BoostGraph* bg = new BoostGraph(g);
	Path p = FindPath(bg, 0, 3);
	delete bg;

	ASSERT_EQ(OP, p);
	
}

TEST(_Pathfinding, MultiplePaths) {

	Graph g;
	g.addEdge(0, 1, 100);
	g.addEdge(0, 2, 50);
	g.addEdge(1, 3, 10);
	g.addEdge(2, 3, 10);
	g.Compress();

	//The optimal path here is 0->2->3
	std::vector<PathMember> OptimalPath = {
		{50,0},
		{10,2},
		{0,3}
	};

	Path OP(OptimalPath);

	BoostGraph* bg = new BoostGraph(g);

	std::vector<int> start_points(100, 0);
	std::vector<int> end_points(100, 3);

	auto paths = FindPaths(bg, start_points, end_points);
	delete bg;


	for (const auto& path : paths)
		ASSERT_EQ(OP, path);
}

///
///	The following are tests for the code samples for HF::SpatialStructures::Pathfinding
///

TEST(_boostGraph, Constructor) {
	// be sure to #include "boost_graph.h", #include "node.h", #include "graph.h", and #include <vector>

	// In order to create a BoostGraph, we must first create a Graph instance first.
	// We must prepare the nodes, their edges, and the weights (distances) of each edge.

	// Create the nodes
	HF::SpatialStructures::Node node_0(1.0f, 1.0f, 2.0f);
	HF::SpatialStructures::Node node_1(2.0f, 3.0f, 4.0f, 5);
	HF::SpatialStructures::Node node_2(11.0f, 22.0f, 140.0f);

	// Create a container (vector) of nodes
	std::vector<HF::SpatialStructures::Node> nodes = { node_0, node_1, node_2 };

	// Create matrices for edges and distances, edges.size() == distances().size()
	std::vector<std::vector<int>> edges = { { 1, 2 }, { 2 }, { 1 } };
	std::vector<std::vector<float>> distances = { { 1.0f, 2.5f }, { 54.0f }, { 39.0f } };

	// Now you can create a Graph - note that nodes, edges, and distances are passed by reference
	HF::SpatialStructures::Graph graph(edges, distances, nodes);

	// Passing Graph graph to BoostGraph bg, by reference
	HF::Pathfinding::BoostGraph bg(graph);
}

TEST(_boostGraph, Destructor) {
	// be sure to #include "boost_graph.h", #include "node.h", #include "graph.h", and #include <vector>

	// In order to create a BoostGraph, we must first create a Graph instance first.
	// We must prepare the nodes, their edges, and the weights (distances) of each edge.

	// Create the nodes
	HF::SpatialStructures::Node node_0(1.0f, 1.0f, 2.0f);
	HF::SpatialStructures::Node node_1(2.0f, 3.0f, 4.0f, 5);
	HF::SpatialStructures::Node node_2(11.0f, 22.0f, 140.0f);

	// Create a container (vector) of nodes
	std::vector<HF::SpatialStructures::Node> nodes = { node_0, node_1, node_2 };

	// Create matrices for edges and distances, edges.size() == distances().size()
	std::vector<std::vector<int>> edges = { { 1, 2 }, { 2 }, { 1 } };
	std::vector<std::vector<float>> distances = { { 1.0f, 2.5f }, { 54.0f }, { 39.0f } };

	// Now you can create a Graph - note that nodes, edges, and distances are passed by reference
	HF::SpatialStructures::Graph graph(edges, distances, nodes);

	// Begin scope
	{
		// Create a BoostGraph bg, from a Graph graph (passing g by reference)
		HF::Pathfinding::BoostGraph bg(graph);
	}
	// End scope

	// When bg goes out of scope, BoostGraph::~BoostGraph is called
	// An explicit call to BoostGraph::~BoostGraph is also made when
	// invoking operator delete on a (BoostGraph *)
}

TEST(_boostGraphDeleter, OperatorFunction) {
	// be sure to #include "path_finder.h", #include "boost_graph.h", 
	// #include "node.h", #include "graph.h", and #include <vector>

	// For this example, we must have a BoostGraph instance to use with BoostGraphDeleter.
	// In order to create a BoostGraph, we must first create a Graph instance first.
	// We must prepare the nodes, their edges, and the weights (distances) of each edge.

	// Create the nodes
	HF::SpatialStructures::Node node_0(1.0f, 1.0f, 2.0f);
	HF::SpatialStructures::Node node_1(2.0f, 3.0f, 4.0f, 5);
	HF::SpatialStructures::Node node_2(11.0f, 22.0f, 140.0f);

	// Create a container (vector) of nodes
	std::vector<HF::SpatialStructures::Node> nodes = { node_0, node_1, node_2 };

	// Create matrices for edges and distances, edges.size() == distances().size()
	std::vector<std::vector<int>> edges = { { 1, 2 }, { 2 }, { 1 } };
	std::vector<std::vector<float>> distances = { { 1.0f, 2.5f }, { 54.0f }, { 39.0f } };

	// Now you can create a Graph - note that nodes, edges, and distances are passed by reference
	HF::SpatialStructures::Graph graph(edges, distances, nodes);

	// Passing Graph graph to BoostGraph bg, by reference
	HF::Pathfinding::BoostGraph bg(graph);

	//
	// Read below on BoostGraphDeleter -- this is important.
	//

	// BoostGraphDeleter is needed by std::unique_ptr to destroy a BoostGraph; it is not meant to be called directly.
	// You do not want to pass the address of a stack-allocated BoostGraph to BoostGraphDeleter::operator().

	// BoostGraphDeleter's operator() calls operator delete on the (BoostGraph *) argument,
	// and passing the address of a stack-allocated BoostGraph for said argument
	// will result in undefined behavior.

	//
	// In other words, do __not__ do the following:
	//
	/* 
		This code compiles and builds, but this is an example of what NOT to do --
		so the remainder of this test is commented out.
	
	HF::Pathfinding::BoostGraphDeleter bg_deleter;

	// Create a stack-allocated BoostGraph from a HF::SpatialStructures::Graph graph
	HF::Pathfinding::BoostGraph boostGraph(graph);	// not created using operator new

	// Using a BoostGraphDeleter on the (address of a) stack-allocated BoostGraph
	bg_deleter(&boostGraph);						// calls operator delete for a (BoostGraph *)

	// The type BoostGraphDeleter is only for use with std::unique_ptr.
	// See BoostGraph::CreateBoostGraph for BoostGraphDeleter's intended use.
	*/
}

TEST(_pathFinding, CreateBoostGraph) {
	// be sure to #include "path_finder.h", #include "boost_graph.h",
	// #include "node.h", and #include "graph.h"

	// For this example, we must have a BoostGraph instance to use with BoostGraphDeleter.
	// In order to create a BoostGraph, we must first create a Graph instance first.
	// We must prepare the nodes, their edges, and the weights (distances) of each edge.

	// Create the nodes
	HF::SpatialStructures::Node node_0(1.0f, 1.0f, 2.0f);
	HF::SpatialStructures::Node node_1(2.0f, 3.0f, 4.0f, 5);
	HF::SpatialStructures::Node node_2(11.0f, 22.0f, 140.0f);

	// Create a container (vector) of nodes
	std::vector<HF::SpatialStructures::Node> nodes = { node_0, node_1, node_2 };

	// Create matrices for edges and distances, edges.size() == distances().size()
	std::vector<std::vector<int>> edges = { { 1, 2 }, { 2 }, { 1 } };
	std::vector<std::vector<float>> distances = { { 1.0f, 2.5f }, { 54.0f }, { 39.0f } };

	// Now you can create a Graph - note that nodes, edges, and distances are passed by reference
	HF::SpatialStructures::Graph graph(edges, distances, nodes);

	// Now we can create a smart pointer to a BoostGraph
	// Note the type of boostGraph - it is a
	//		std::unique_ptr<HF::Pathfinding::BoostGraph, HF::Pathfinding::BoostGraphDeleter>.
	// Use the auto keyword for type inference, or your choice of using statements/typedef to make
	// the use of the type described above easier.
	auto boostGraph = HF::Pathfinding::CreateBoostGraph(graph);
}


TEST(_pathFinding, FindPath) {
	// be sure to #include "path_finder.h", #include "boost_graph.h", and #include "graph.h"
	
	// Create a Graph g, and compress it.
	HF::SpatialStructures::Graph g;
	g.addEdge(0, 1, 1);
	g.addEdge(0, 2, 2);
	g.addEdge(1, 3, 3);
	g.addEdge(2, 4, 1);
	g.addEdge(3, 4, 5);
	g.Compress();

	// Create a boostGraph from g
	auto boostGraph = HF::Pathfinding::CreateBoostGraph(g);

	// Get the path from node (id 0) to node (id 3)
	HF::SpatialStructures::Path path = HF::Pathfinding::FindPath(boostGraph.get(), 0, 3);

	// Print the nodes along the shortest path
	std::cout << "Shortest path from node id 0 to node id 3:" << std::endl;
	for (auto p : path.members) {
		std::cout << p.node << std::endl;
	}
}

TEST(_pathFinding, FindPaths) {
	// be sure to #include "path_finder.h", #include "boost_graph.h", and #include "graph.h"

	// Create a Graph g, and compress it.
	HF::SpatialStructures::Graph g;
	g.addEdge(0, 1, 1);
	g.addEdge(0, 2, 2);
	g.addEdge(1, 3, 3);
	g.addEdge(2, 4, 1);
	g.addEdge(3, 4, 5);
	g.Compress();

	// Create a boostGraph from g
	auto boostGraph = HF::Pathfinding::CreateBoostGraph(g);

	// Prepare the parents and children vectors --
	// We will be searching for the shortest path from node 0 to node 3,
	// as well as the shortest path from node 0 to node 4.
	std::vector<int> parents = { 0, 0 };
	std::vector<int> children = { 3, 4 };

	std::vector<HF::SpatialStructures::Path> paths 
		= HF::Pathfinding::FindPaths(boostGraph.get(), parents, children);

	// Get the shortest paths, which are already stored in paths
	auto path_0_3 = paths[0];
	auto path_0_4 = paths[1];

	// Print the shortest path from node 0 to node 3
	std::cout << "Shortest path from node id 0 to node id 3:" << std::endl;
	for (auto p : path_0_3.members) {
		std::cout << p.node << std::endl;
	}

	// Print the shortest path from node 0 to node 4
	std::cout << "Shortest path from node id 0 to node id 4:" << std::endl;
	for (auto p : path_0_4.members) {
		std::cout << p.node << std::endl;
	}
}

TEST(_pathFinding, FindAllPaths) {
	// NOTE: HF::Pathfinding::FindAllPaths is not implemented yet.

	// be sure to #include "path_finder.h", #include "boost_graph.h", and #include "graph.h"

	// Create a Graph g, and compress it.
	HF::SpatialStructures::Graph g;
	g.addEdge(0, 1, 1);
	g.addEdge(0, 2, 2);
	g.addEdge(1, 3, 3);
	g.addEdge(2, 4, 1);
	g.addEdge(3, 4, 5);
	g.Compress();

	// Create a boostGraph from g
	auto boostGraph = HF::Pathfinding::CreateBoostGraph(g);

	// Cannot test this just yet -- FindAllPaths is yet to be implemented
	// Get the path from node (id 0) to node (id 4)
	// auto all_paths = HF::Pathfinding::FindAllPaths(boostGraph.get(), 0, 4);

	// all_paths will contain all shortest paths for [node 0, node 4]
}

/* This appears to always corrupt the heap when deallocating paths
   due to differing compiler options between google test and humanfactors.
TEST(_pathFinding, InsertPathsIntoArray) {
	// be sure to #include "path_finder.h", #include "boost_graph.h", and #include "graph.h"

	// Create a Graph g, and compress it.
	HF::SpatialStructures::Graph g;
	g.addEdge(0, 1, 1);
	g.addEdge(0, 2, 2);
	g.addEdge(1, 3, 3);
	g.addEdge(2, 4, 1);
	g.addEdge(3, 4, 5);
	g.Compress();

	// Create a boostGraph from g
	auto boostGraph = HF::Pathfinding::CreateBoostGraph(g);

	// Prepare the parents and children vectors --
	// We will be searching for the shortest path from node 0 to node 3,
	// as well as the shortest path from node 0 to node 4.
	std::vector<int> parents = { 0, 0 };
	std::vector<int> children = { 3, 4 };

	// Create smart pointers to hold Path, PathMember and sizes
	const int MAX_SIZE = 2;

	HF::SpatialStructures::Path** path_ptrs = new Path*;
	HF::SpatialStructures::PathMember** path_members_ptrs = new PathMember*;
	int* out_sizes = new int[2];

	//std::unique_ptr<HF::SpatialStructures::Path[]> result_paths(new Path[MAX_SIZE]);
	//std::unique_ptr<HF::SpatialStructures::PathMember[]> result_path_members(new PathMember[MAX_SIZE]);
	//std::unique_ptr<int[]> result_sizes(new int[MAX_SIZE]);

	// Retrieve raw pointers so their addresses can be passed to InsertPathsIntoArray
	//HF::SpatialStructures::Path* ppath = result_paths.get();
	//HF::SpatialStructures::PathMember* pmembers = result_path_members.get();
	//int* psizes = result_sizes.get();

	// Use InsertPathsIntoArray
	HF::Pathfinding::InsertPathsIntoArray(boostGraph.get(), parents, children, path_ptrs, path_members_ptrs, out_sizes);

	// Delete paths
	if (path_ptrs[0])
		delete (path_ptrs)[0];
	if (path_ptrs[1])
		delete (path_ptrs)[1];
	delete[2] path_ptrs;

	delete[2] out_sizes;

}
*/

namespace CInterfaceTests {
	TEST(_PathfinderCInterface, CreatePath) {
		// Requires #include "pathfinder_C.h", #include "graph.h", #include "path.h", #include "path_finder.h"

		// Create a Graph g, and compress it.
		HF::SpatialStructures::Graph g;
		g.addEdge(0, 1, 1);
		g.addEdge(0, 2, 2);
		g.addEdge(1, 3, 3);
		g.addEdge(2, 4, 1);
		g.addEdge(3, 4, 5);
		g.Compress();

		// Create a boostGraph from g
		auto boostGraph = HF::Pathfinding::CreateBoostGraph(g);

		// Prepare parameters for CreatePath
		HF::SpatialStructures::Path* out_path = nullptr;
		HF::SpatialStructures::PathMember* out_path_member = nullptr;
		int out_size = -1;

		CreatePath(&g, 0, 4, &out_size, &out_path, &out_path_member);

		// Use out_path, out_path_member

		// Remember to free resources when finished
		DestroyPath(out_path);

		// At this point, out_path_member has also been destroyed, so we set this to nullptr
		out_path_member = nullptr;
	}

	TEST(_PathfinderCInterface, CreatePaths) {
		// Requires #include "pathfinder_C.h", #include "graph.h", #include "path.h", #include "path_finder.h"

		// Create a Graph g, and compress it.
		HF::SpatialStructures::Graph g;
		g.addEdge(0, 1, 1);
		g.addEdge(0, 2, 2);
		g.addEdge(1, 3, 3);
		g.addEdge(2, 4, 1);
		g.addEdge(3, 4, 5);
		g.Compress();

		// Create a boostGraph from g
		auto boostGraph = HF::Pathfinding::CreateBoostGraph(g);

		// Prepare starting and ending nodes
		int start_nodes[] = { 0 };
		int end_nodes[] = { 4 };

		// Prepare parameters for CreatePaths
		HF::SpatialStructures::Path* out_path = nullptr;
		HF::SpatialStructures::PathMember* out_path_member = nullptr;
		int out_size = -1;
		const int path_size = 5;

		// Sizes of paths
		const int MAX_SIZE = 16;
		int out_sizes[MAX_SIZE];

		CreatePaths(&g, start_nodes, end_nodes, &out_path, &out_path_member, out_sizes, path_size);

		// Use out_path, out_path_member

		// Remember to free resources when finished
		DestroyPath(out_path);

		// At this point, out_path_member has also been destroyed, so we set this to nullptr
		out_path_member = nullptr;
	}

	TEST(_PathfinderCInterface, GetPathInfo) {
		// Requires #include "pathfinder_C.h", #include "path.h"

		// Requires #include "pathfinder_C.h", #include "graph.h", #include "path.h", #include "path_finder.h"

		// Create a Graph g, and compress it.
		HF::SpatialStructures::Graph g;
		g.addEdge(0, 1, 1);
		g.addEdge(0, 2, 2);
		g.addEdge(1, 3, 3);
		g.addEdge(2, 4, 1);
		g.addEdge(3, 4, 5);
		g.Compress();

		// Create a boostGraph from g
		auto boostGraph = HF::Pathfinding::CreateBoostGraph(g);

		HF::SpatialStructures::Path* out_path = nullptr;
		HF::SpatialStructures::PathMember* out_path_member = nullptr;
		int out_size = -1;

		CreatePath(&g, 0, 4, &out_size, &out_path, &out_path_member);

		// Get out_path's info, store results in out_path_member and out_size
		GetPathInfo(out_path, &out_path_member, &out_size);

		// Remember to free resources when finished
		DestroyPath(out_path);

		// At this point, out_path_member has also been destroyed, so we set this to nullptr
		out_path_member = nullptr;
	}

	TEST(_PathfinderCInterface, DestroyPath) {
		// Requires #include "pathfinder_C.h", #include "graph.h", #include "path.h", #include "path_finder.h"

		// Create a Graph g, and compress it.
		HF::SpatialStructures::Graph g;
		g.addEdge(0, 1, 1);
		g.addEdge(0, 2, 2);
		g.addEdge(1, 3, 3);
		g.addEdge(2, 4, 1);
		g.addEdge(3, 4, 5);
		g.Compress();

		// Create a boostGraph from g
		auto boostGraph = HF::Pathfinding::CreateBoostGraph(g);

		HF::SpatialStructures::Path* out_path = nullptr;
		HF::SpatialStructures::PathMember* out_path_member = nullptr;
		int out_size = -1;

		CreatePath(&g, 0, 4, &out_size, &out_path, &out_path_member);

		// Use out_path, out_path_member

		// Remember to free resources when finished
		DestroyPath(out_path);

		// At this point, out_path_member has also been destroyed, so we set this to nullptr
		out_path_member = nullptr;
	}
}