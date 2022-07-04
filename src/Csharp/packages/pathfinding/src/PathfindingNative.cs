
using DHARTAPI.NativeUtils;
using DHARTAPI.Exceptions;
using System;
using System.Runtime.InteropServices;
using DHARTAPI.SpatialStructures;
using System.Runtime.Serialization.Json;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Threading;
using System.Diagnostics;
using System.Security.Cryptography.X509Certificates;

namespace DHARTAPI.Pathfinding
{
	/*! \brief NativeMethods for the Pathfinding Namespace. */
	internal static class NativeMethods
	{

		// Get the DLL path from NativeConstants
		const string dll_path = NativeConstants.DLLPath;

		/*! 
            \brief Generate a path from start to end. 
           
            \param graph_ptr A pointer to a valid Graph.
            \param start The ID of the node to start at.
            \param end The ID of the node to find a path to. 
            \param cost_type The type of cost to use for generating the path. If left blank, will use
            the cost that the graph was created with. In the case of the graph generator, the default
            cost is distance. 

            \returns A CVectorAndData to the generated path
              
            \pre 1) `start_id` and `end_id` must be the X,Y,Z position of nodes that already exist in `graph`.
            \pre 2) If `cost_type` is not left as the default, then it must be the name of a valid cost already
            defined in `graph`.

            \throws KeyNotFoundException `cost_type` wasn't left as blank, and didn't
            refer to the name of any cost that already exists in the graph.
            \throws System.IndexOutOfRangeException Start or end points were not in the graph
        */
		internal static CVectorAndData C_CreatePath(IntPtr graph_ptr, int start, int end, string cost_type)
		{
			// Setup our output variable so we can use its members as reference parameters.
			CVectorAndData out_ptrs = new CVectorAndData();

			// Find the path in unmanaged code. If this returns OK, then the parameters
			// of out_ptrs will be updated with the data for the path.
			HF_STATUS res = CreatePath(
				graph_ptr,
				start,
				end,
				cost_type,
				ref out_ptrs.size,
				ref out_ptrs.vector,
				ref out_ptrs.data
			);

			// If NO_PATH is returned, that means no path exists from start to end
			// so make sure our output reflects this.
			if (res == HF_STATUS.OK)
				return out_ptrs;
			else if (res == HF_STATUS.NO_PATH)
			{
				// If NO_PATH, that just means that there is on path between start and end,
				// so just return an invalid CVectorAndData **to signal that this isn't possble
				out_ptrs.size = -1;
				out_ptrs.data = IntPtr.Zero;
				out_ptrs.vector = IntPtr.Zero;
			}
			// Throw if the cost doesn't exist.
			else if (res == HF_STATUS.NO_COST) // Cost type doesn't exist in the graph
				throw new KeyNotFoundException("cost_type " + cost_type + " is not the valid key of a cost in the graph");
			else
				// If this ever fails, something changed in the CInterface that wasn't reflected in C#
				Debug.Assert(false);
			return out_ptrs;
		}

		/*! 
            \brief  Generate a path from start to end.

            \param graph_ptr Pointer to the graph to construct paths in
            \param start Ids for the start points to generate paths from. 
            \param end Ids for the end points to generate paths to
            \param cost_type The type of cost to use for generating the path. If left blank, will use
            the cost that the graph was created with. In the case of the graph generator, the default
            cost is distance. 

            \returns 
            An array CVectorAndData for each generated paths in order from start_ids to end_ids.
            If a CVectorAndData could not be generated by a set of points, then the path at that 
            location will be invalid.

            \throws System.ArgumentException Length of `start_ids` didn't equal length of `end_ids`
            \throws KeyNotFoundException `cost_type` wasn't left as blank, and didn't
            refer to the name of any cost that already exists in the graph.
        */
		internal static CVectorAndData[] C_CreatePaths(
			IntPtr graph_ptr,
			IEnumerable<int> start,
			IEnumerable<int> end,
			string cost_type
		)
		{
			// Preallocate memory to fulfil pre-conditions
			int size = start.Count();
			int[] path_sizes = new int[size];
			IntPtr[] data = new IntPtr[size];
			IntPtr[] vectors = new IntPtr[size];


			// Call the Native funciton
			HF_STATUS res = CreatePaths(
				graph_ptr,
				start.ToArray(),
				end.ToArray(),
				cost_type,
				vectors,
				data,
				path_sizes,
				size
			);

			if (res == HF_STATUS.NO_COST)
				throw new KeyNotFoundException("Cost Type (" + cost_type + ") could not be found in the graph");

			// Read through results and fill out CVectorsAndDatas
			CVectorAndData[] out_cvads = new CVectorAndData[size];
			for (int i = 0; i < size; i++)
			{
				//Get the pointers/length of the arrays at index I
				IntPtr data_ptr = data[i];
				IntPtr vector_ptr = vectors[i];
				int node_count = path_sizes[i];

				// If the count of this path is 0, that means no path could be found
				// and both of its pointers are null, so don't try to access them at all
				if (node_count > 0)
					out_cvads[i] = new CVectorAndData(data_ptr, vector_ptr, node_count);
				// An empty CVectorAndData is our signal for a failed path.
				else
					out_cvads[i] = new CVectorAndData();

			}
			return out_cvads;
		}

		/*!
            \brief Generate all to all paths in C++.
        
            \param graph_ptr A pointer to the graph to generate paths in. 
            \param graph_size The number of nodes in the the grpah pointed to by `graph_ptr`. 
            \param cost_type Type of cost to use for path generation. If left blank will use the
                              default cost of the graph
            
            \returns
            An array of CVectorAndData with a length equal to the number of nodes in `g` squared. Paths will
            be returned in order starting with all paths from node 0, then all paths from node 1, etc.
            If a path could not be generated between a set of nodes, then CVectorAndData at that index
            will be invalid.

            \pre If `cost_type` is not left as the default, then it must be the name of a valid cost already
            defined in `graph`.

            \throws KeyNotFoundException `cost_type` wasn't left as blank, and didn't
                     refer to the name of any cost that already exists in `graph`.
        */
		internal static CVectorAndData[] C_AllToAllPaths(IntPtr graph_ptr, int graph_size, string cost_type)
		{

			// Setup variables to fulfill our preconditions
			int num_paths = graph_size * graph_size; // Will return n^2 nodes
			IntPtr[] data = new IntPtr[num_paths];
			IntPtr[] vectors = new IntPtr[num_paths];
			int size = num_paths;
			int[] path_sizes = new int[size];

			// Call the Native function, populating our arrays
			HF_STATUS res = CreateAllToAllPaths(
				graph_ptr,
				cost_type,
				vectors,
				data,
				path_sizes,
				size
			);

			// Throw if the cost couldn't be found
			if (res == HF_STATUS.NO_COST)
				throw new KeyNotFoundException("Cost Type (" + cost_type + ") could not be found in the graph");

			// Read through results and fill output CVectorsAndDatas
			CVectorAndData[] out_cvads = new CVectorAndData[size];
			for (int i = 0; i < size; i++)
			{
				// Get the pointers and size of the vector at index i
				IntPtr data_ptr = data[i];
				IntPtr vector_ptr = vectors[i];
				int node_count = path_sizes[i];

				// If the count of this path is 0, that means no path could be found
				// and both of its pointers are null, so don't try to access them at all
				// and instead put an invalid CVectorAndData at that index
				if (node_count > 0)
					out_cvads[i] = new CVectorAndData(data_ptr, vector_ptr, node_count);
				// An empty CVector and data is invalid.
				else
					out_cvads[i] = new CVectorAndData();

			}
			return out_cvads;

		}

		/*! \brief Calculate Predecessor and Distance Matricies for a graph in C++
         
            \param graph_ptr Pointer to a graph to calculate predeessor and distance matricies for
            \param out_dist Output parameter for the distance matrix
            \param out_predecessor Output parameter for the predecessor matrix.
            \param cost_type Type of cost to use for the distance and predecessor
                             matricies. If left blank will use the default cost of 
                             the graph.

            \throws KeyNotFoundException If cost_type isn't left to the default, and
                                         does not match the key of any cost that already
                                         exists in the graph.
        

            \post out_dist and out_predecessor are updated to contain pointers to the distance predecessor
            matricies for `g`.
           */
		public static void C_GeneratePredecessorAndDistanceMatricies(
			IntPtr graph_ptr,
			ref CVectorAndData out_dist,
			ref CVectorAndData out_predecessor,
			string cost_type
		)
		{
			// Just call the C++ function, it should update everything else. 
			HF_STATUS res = CalculateDistanceAndPredecessor(
				graph_ptr,
				cost_type,
				ref out_dist.vector,
				ref out_dist.data,
				ref out_predecessor.vector,
				ref out_predecessor.data
			);

			if (res == HF_STATUS.NO_COST)
				throw new KeyNotFoundException("Cost type " + cost_type + " could not be found in the graph");

			Debug.Assert(res == HF_STATUS.OK);


			Debug.Assert(out_dist.data != IntPtr.Zero);
			Debug.Assert(out_dist.vector != IntPtr.Zero);
		}

		/*! \brief Free the memory allocated by a path.
			
			\param path_ptr Pointer to the path to free.
		*/
		internal static void C_DestroyPath(IntPtr path_ptr) => DestroyPath(path_ptr);

		[DllImport(dll_path)]
		private static extern HF_STATUS DestroyPath(IntPtr path_ptr);
		[DllImport(dll_path)]
		private static extern HF_STATUS CreatePath(
			IntPtr graph_ptr,
			int start,
			int end,
			string cost_type,
			ref int out_size,
			ref IntPtr out_path,
			ref IntPtr out_data
		);

		[DllImport(dll_path)]
		private static extern HF_STATUS CreatePaths(
			IntPtr graph_ptr,
			[In] int[] start,
			[In] int[] end,
			string cost_type,
			[Out] IntPtr[] out_path_ptr_holder,
			[Out] IntPtr[] out_path_member_ptr_holder,
			[Out] int[] out_sizes,
			int num_paths
		);

		[DllImport(dll_path)]
		private static extern HF_STATUS CreateAllToAllPaths(
			IntPtr graph_ptr,
			string cost_type,
			[Out] IntPtr[] out_path_ptr_holder,
			[Out] IntPtr[] out_path_member_ptr_holder,
			[Out] int[] out_sizes,
			int num_paths
		);

		[DllImport(dll_path)]
		private static extern HF_STATUS CalculateDistanceAndPredecessor(
			IntPtr g,
			string cost_name,
			ref IntPtr out_distance_vector,
			ref IntPtr out_distance_data,
			ref IntPtr out_pred_vector,
			ref IntPtr out_pred_data
		);

	}
}
