///
///	\file		cost_algorithms.h
///	\brief		Contains implementation for the <see cref="HF::SpatialStructures::CostAlgorithms">HF::SpatialStructures::CostAlgorithms</cref> namespace
///
///	\author		TBA
///	\date		03 Jul 2020
///

#include "cost_algorithms.h"
#include "graph.h"
#include "Constants.h"

#include <iostream>

using HF::SpatialStructures::IntEdge;
using HF::SpatialStructures::Graph;

bool HF::SpatialStructures::CostAlgorithms::is_perpendicular(std::array<float, 3> dir_a, std::array<float, 3> dir_b) {
    bool perpendicular = false;

    float dot_product =
        ((dir_a[0] * dir_b[0])
            + (dir_a[1] * dir_b[1])
            + (dir_a[2] * dir_b[2]));

    // Mathematically,
    // two vectors are perpendicular if their dot product is
    // equal to zero. But since it is a mortal sin to test
    // floating point numbers for equality (using operator==) --
    // we can test if the dot product of
    // vector_a and vector_b is 'close enough' to zero,
    // by determining if our dot_product calculation
    // is less than our ROUNDING_PRECISION constant.
    // (which is 0.0001)    
    perpendicular = std::abs(dot_product) < HF::SpatialStructures::ROUNDING_PRECISION;

    return perpendicular;
}

std::vector<IntEdge> HF::SpatialStructures::CostAlgorithms::CalculateCrossSlope(Graph& g) {
    // All cross slope data will be stored here and returned from this function.
    std::vector<IntEdge> result;

    // Retrieve the graph in the form of a CSR.
    CSRPtrs csr = g.GetCSRPointers();

    if (csr.AreValid() == false) {
        return result;
    }
    // csr.data[last_index] and csr.inner_indices[last_index]
    // are the final values for those buffers, respectively.
    const int last_index = csr.rows - 1;
    std::cout << "csr.nnz = " << csr.nnz << std::endl;
    std::cout << "csr.rows = " << csr.rows << std::endl;
    std::cout << "csr.cols = " << csr.cols << std::endl;
    std::cout << std::endl;

    for (int parent_id = 0; parent_id < csr.rows; parent_id++) {
        // We iterate through all parent IDs, [0, csr.rows)
        // We also retrieve all child nodes for this parent,
        // as well as all edges that extend from this parent.
        Node parent_node = g.NodeFromID(parent_id);
        std::vector<Node> children = g.GetChildren(parent_node);
        std::vector<Edge> edges = g[parent_node];

        for (Edge edge_a : edges) {
            // We iterate over all edges that extend from parent_node.
            Node child_node_a = edge_a.child;
            float edge_data_a = edge_a.score;

            std::cout << "parent " << parent_id << " has child " << child_node_a.id
                << " with data " << edge_data_a << std::endl;

            std::cout << "====== Comparing with other edges ======"
                << std::endl;

            // We must have a container to store all perpendicular edges found.
            std::vector<Edge> perpendicular_edges = GetPerpendicularEdges(parent_node, g[parent_node], child_node_a);

            std::cout << "====== End of comparing with other edges ======"
                << std::endl;

            float weight = 0.0;
            float a_z = 0.0;
            float b_z = 0.0;
            float c_z = 0.0;

            switch (perpendicular_edges.size()) {
            case 0:
                // No edges were found to be perpendicular to the edge
                // formed by node parent_node and node child_node_a.
                // The IntEdge to be created will use the existing edge data
                // of parent_node and child_node_a (edge_data_a)

                weight = edge_data_a;
                break;
            case 1:
                // One edge formed by node parent_node and one other child_node by parent_node
                // was found to be perpendicular to the edge formed by
                // node parent_node and node child_node_a.

                a_z = child_node_a.z;

                // z value of other child_node
                b_z = perpendicular_edges[0].child.z;

                // add the existing weight value to the delta of the z values
                weight = std::abs(a_z - b_z) + perpendicular_edges[0].score;
                break;
            case 2:
                // Two edges -- each formed by node parent_node and two separate
                // child node by node parent_node were found to be perpendicular to the edge
                // formed by node parent_node and node child_node_a.

                a_z = child_node_a.z;

                // z value of the first other child_node
                b_z = perpendicular_edges[0].child.z;

                // z value of the second other child_node
                c_z = perpendicular_edges[1].child.z;

                // add the existing weight value to the delta of the z values
                weight = std::abs(b_z - c_z) + perpendicular_edges[0].score;
                break;
            default:
                break;
            }

            // Create the IntEdge using child_node_a.id
            // and the cross slope value stored in weight --
            // then add it to our result container.
            IntEdge ie = { child_node_a.id, weight };
            result.push_back(ie);
        }

        std::cout << "***** ALL CHILDREN FOR THIS PARENT DONE *****\n"
            << std::endl;
    }

    return result;
}

std::vector<HF::SpatialStructures::Edge> HF::SpatialStructures::CostAlgorithms::GetPerpendicularEdges(HF::SpatialStructures::Node& parent_node, std::vector<Edge> edges, Node& child_node_a) {
    std::vector<HF::SpatialStructures::Edge> perpendicular_edges;

    for (Edge edge_b : edges) {
        Node child_node_b = edge_b.child;
        // We iterate over all children for parent_node,
        // and create a vector_b from parent_node and the current child,
        // child_node_b. 
        // The goal is to compare vector_a with every other
        // vector_b created by the common parent_node and its children.
        std::cout << "parent " << parent_node.id << " has child " << edge_b.child.id
            << " with data " << edge_b.score << std::endl;

        if (child_node_a == child_node_b) {
            // If child_node_b is the same as the child_node we passed in, skip it.
            std::cout << " *** SKIPPED ***" << std::endl;
        }
        else {
            float edge_data_b = edge_b.score;
            auto vector_a = parent_node.directionTo(child_node_a);
            auto vector_b = parent_node.directionTo(child_node_b);

            if (is_perpendicular(vector_a, vector_b)) {
                // If this evaluates true,
                // we construct an Edge using child_node_b and
                // edge_data_b, and save this Edge in a container.

                Edge e(child_node_b, edge_data_b);
                perpendicular_edges.push_back(e);
            }
        }
    }
    return perpendicular_edges;
}

/*
OLD VERSION
std::vector<IntEdge> HF::SpatialStructures::CostAlgorithms::CalculateCrossSlope(Graph& g) {

    for (int parent_id = 0; parent_id < csr.rows; parent_id++) {
        // We iterate through all parent IDs, [0, csr.rows)

        // Tests if we are at the last parent ID, needed for row_end_index
        bool at_last_parent = parent_id == last_index;

        // The starting index for csr.data and csr.inner_indices
        // for the edge data/child IDs belonging to the current parent ID
        int curr_row_index = csr.outer_indices[parent_id];

        // The starting index for csr.data and csr.inner_indices
        // for the edge data/child IDs belonging to the next parent ID
        int next_row_index = csr.outer_indices[parent_id + 1];

        // If at_last_parent
        //      csr.nnz, count of non-zero values
        //      (size of csr.data and csr.inner_indices buffer)
        // Else
        //      next_row_index - offset for the next parent ID
        const int row_end_index = at_last_parent ? csr.nnz : next_row_index;

        if (row_end_index < csr.nnz) {
            std::cout << "***** data_pos = " << csr.data[curr_row_index] << "\t"
                << "row_end = " << csr.data[row_end_index] << " *****"
                << std::endl;
        }
        else {
            std::cout << "***** data_pos = " << csr.data[curr_row_index] << "\t"
                << "row_end = "
                << "null"
                << " *****" << std::endl;
        }

        // We retrieve parent_node, using parent_id, from g
        // (the parent node for this row in the CSR).
        Node parent_node = g.NodeFromID(parent_id);

        // We must have a container to store all perpendicular edges found.
        std::vector<Edge> perpendicular_edges;

        for (int i = curr_row_index; i < row_end_index; i++) {
            // We iterate through all edges/child IDs for the current parent_id.
            // i is our current position within csr.data/csr.inner_indices

            // Retrieve the current child ID
            int child_id_a = csr.inner_indices[i];

            // Retrieve the edge data formed by parent_id and child_id_a.
            const float edge_data_a = csr.data[i];

            // Retrieve the current child node from g, using child_id_a.
            Node child_node_a = g.NodeFromID(child_id_a);

            // Calculate the vector from parent_node to child_node_a.
            // We will denote this as vector_a.
            auto vector_a = parent_node.directionTo(child_node_a);

            std::cout << "parent " << parent_id << " has child " << child_id_a
                << " with data " << csr.data[i] << std::endl;

            std::cout << "====== Comparing with other edges ======"
                << std::endl;

            for (int k = curr_row_index; k < row_end_index; k++) {
                // We iterate through all edges/child IDs for the current
                // parent ID, to compare the edge formed by parent_id and
                // child_a_id -- to every other edge formed
                // by parent_id and its other children.

                // Retrieve the current child ID for the comparison
                int child_id_b = csr.inner_indices[k];

                std::cout << "parent " << parent_id << " has child "
                    << child_id_b << " with data " << csr.data[k];

                if (child_id_a == child_id_b) {
                    // We skip the child ID that we are currently on from the
                    // upper-level iteration.
                    std::cout << " *** SKIPPED ***" << std::endl;
                }
                else {
                    std::cout << std::endl;

                    // Retrieve the current child node from g, using child_id_b.
                    Node child_node_b = g.NodeFromID(child_id_b);

                    // Calculate the vector from parent_node to child_node_b.
                    // We will denote this as vector_b.
                    auto vector_b = parent_node.directionTo(child_node_b);

                    // Calculate the dot product of vector_a and vector_b.
                    // indices {0, 1, 2} are {x, y, z}.
                    float dot_product =
                    ((vector_a[0] * vector_b[0])
                    + (vector_a[1] * vector_b[1])
                    + (vector_a[2] * vector_b[2]));

                    // Mathematically,
                    // two vectors are perpendicular if their dot product is
                    // equal to zero. But since it is a mortal sin to test
                    // floating point numbers for equality --
                    // we can test if the dot product of
                    // vector_a and vector_b is 'close enough' to zero,
                    // by determining if our dot_product calculation
                    // is less than our ROUNDING_PRECISION constant.
                    // (which is 0.0001)
                    if (std::abs(dot_product) < HF::SpatialStructures::ROUNDING_PRECISION) {
                        // If this evaluates true,
                        // we construct an Edge using child_node_b and
                        // edge_data_b, and save this Edge in a container.
                        const float edge_data_b = csr.data[k];

                        Edge e(child_node_b, edge_data_b);
                        perpendicular_edges.push_back(e);
                    }
                }
            }

            std::cout << "====== End of comparing with other edges ======"
                << std::endl;

            float weight = 0.0;
            float a_z = 0.0;
            float b_z = 0.0;
            float c_z = 0.0;

            switch (perpendicular_edges.size()) {
            case 0:
                // No edges were found to be perpendicular to the edge
                // formed by node parent_id and node child_id_a.
                // The IntEdge to be created will use the existing edge data
                // of parent_id and child_id_b.

                weight = edge_data_a;
                break;
            case 1:
                // One edge formed by node parent_id and one node child_id_b
                // was found to be perpendicular to the edge formed by
                // node parent_id and node child_id_a.

                a_z = child_node_a.z;

                // z value of node_id_b
                b_z = perpendicular_edges[0].child.z;

                // add the existing weight value to the delta of the z values
                weight = std::abs(a_z - b_z) + perpendicular_edges[0].score;
                break;
            case 2:
                // Two edges -- each formed by node_parent_id and two separate
                // node child_id_b's were found to be perpendicular to the edge
                // formed by node parent_id and node child_a_id.

                a_z = child_node_a.z;

                // z value of the first node_id_b
                b_z = perpendicular_edges[0].child.z;

                // z value of the second node_id_b
                c_z = perpendicular_edges[1].child.z;

                // add the existing weight value to the delta of the z values
                weight = std::abs(b_z - c_z) + perpendicular_edges[0].score;
                break;
            default:
                break;
            }

            // Create the IntEdge using child_id_a
            // and the cross slope value stored in weight --
            // then add it to our result container.
            IntEdge ie = { child_id_a, weight };
            result.push_back(ie);
        }

        std::cout << "***** ALL CHILDREN FOR THIS PARENT DONE *****\n"
            << std::endl;
    }

    // The container of IntEdge will be ordered
    // according to the CSR -- all edges will be laid out consecutively.

    // For example:
    //      IntEdge for parent id 0 begin at result[csr.outer_indices[0]]
    //      IntEdge for parent id 0 end at   result[csr.outer_indices[1]]
    //      IntEdge for parent id 1 begin at result[csr.outer_indices[1]]
    //      IntEdge for parent id 2 end at   result[csr.outer_indices[2]]

    return result;
    */
