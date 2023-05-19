/*
 @licstart  The following is the entire license notice for the JavaScript code in this file.

 The MIT License (MIT)

 Copyright (C) 1997-2020 by Dimitri van Heesch

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute,
 sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 @licend  The above is the entire license notice for the JavaScript code in this file
*/
var NAVTREE =
[
  [ "DHART", "index.html", [
    [ "DHART C# Documentation", "index.html", [
      [ "Getting Started", "index.html#autotoc_md77", null ]
    ] ],
    [ "Setting Up a Unity Project for DHART", "_unity_project_setup.html", [
      [ "Before we begin", "_unity_project_setup.html#autotoc_md0", [
        [ "Prerequisites", "_unity_project_setup.html#autotoc_md1", null ]
      ] ],
      [ "Adding DHART to Editor Path", "_unity_project_setup.html#autotoc_md2", null ],
      [ "Creating a new project", "_unity_project_setup.html#autotoc_md3", null ],
      [ "Importing the DHART Library", "_unity_project_setup.html#autotoc_md4", null ],
      [ "Verifying Unity can reference DHARTAPI", "_unity_project_setup.html#autotoc_md5", null ],
      [ "Conclusion", "_unity_project_setup.html#autotoc_md6", null ]
    ] ],
    [ "Using the RayTracer", "_using_the_raytracer.html", [
      [ "Intro", "_using_the_raytracer.html#autotoc_md7", null ],
      [ "Writing the Script", "_using_the_raytracer.html#autotoc_md8", [
        [ "Using Declarations", "_using_the_raytracer.html#autotoc_md9", null ],
        [ "Creating a Plane", "_using_the_raytracer.html#autotoc_md10", null ],
        [ "Casting a Ray", "_using_the_raytracer.html#autotoc_md11", null ],
        [ "Wrapping Up", "_using_the_raytracer.html#autotoc_md12", null ]
      ] ],
      [ "Testing", "_using_the_raytracer.html#autotoc_md13", [
        [ "Adding the script to the camera", "_using_the_raytracer.html#autotoc_md14", null ],
        [ "Executing the Script", "_using_the_raytracer.html#autotoc_md15", null ]
      ] ],
      [ "Conclusion", "_using_the_raytracer.html#autotoc_md16", null ]
    ] ],
    [ "Using the Graph Generator", "_generating_a_graph.html", [
      [ "Intro", "_generating_a_graph.html#autotoc_md17", [
        [ "Conceptual Overview", "_generating_a_graph.html#autotoc_md18", null ]
      ] ],
      [ "Simple Graph Generation", "_generating_a_graph.html#autotoc_md19", [
        [ "Using Declarations", "_generating_a_graph.html#autotoc_md20", null ],
        [ "Creating the Plane", "_generating_a_graph.html#autotoc_md21", null ],
        [ "Generating the Graph", "_generating_a_graph.html#autotoc_md22", null ],
        [ "Retrieving a list of nodes", "_generating_a_graph.html#autotoc_md23", null ],
        [ "Save and Test", "_generating_a_graph.html#autotoc_md24", null ]
      ] ],
      [ "Handling cases where a Graph could not be generated", "_generating_a_graph.html#autotoc_md25", [
        [ "Checking for success", "_generating_a_graph.html#autotoc_md26", null ],
        [ "Testing", "_generating_a_graph.html#autotoc_md27", null ]
      ] ],
      [ "Conclusion", "_generating_a_graph.html#autotoc_md28", null ]
    ] ],
    [ "Reading a Mesh From Unity", "_mesh_from_unity.html", [
      [ "Intro", "_mesh_from_unity.html#autotoc_md29", null ],
      [ "Scene Setup", "_mesh_from_unity.html#autotoc_md30", [
        [ "Creating the Plane", "_mesh_from_unity.html#autotoc_md31", null ],
        [ "Resetting the Plane's Position", "_mesh_from_unity.html#autotoc_md32", null ]
      ] ],
      [ "Writing the Script", "_mesh_from_unity.html#autotoc_md33", [
        [ "Setup for Adding References Through The Unity Inspector", "_mesh_from_unity.html#autotoc_md34", null ],
        [ "Getting a Reference to the Mesh Held by a Specific GameObject", "_mesh_from_unity.html#autotoc_md35", [
          [ "Background on GameObjects and Components", "_mesh_from_unity.html#autotoc_md36", null ],
          [ "In Practice", "_mesh_from_unity.html#autotoc_md37", null ]
        ] ],
        [ "Getting the Vertices and Triangles", "_mesh_from_unity.html#autotoc_md38", null ],
        [ "Transforming the Mesh From Y-Up to Z-Up", "_mesh_from_unity.html#autotoc_md39", null ],
        [ "Choose code From Previous Tutorial to Verify Results", "_mesh_from_unity.html#autotoc_md40", [
          [ "Graph Generator", "_mesh_from_unity.html#autotoc_md41", null ],
          [ "Ray Tracer", "_mesh_from_unity.html#autotoc_md42", null ]
        ] ]
      ] ],
      [ "Testing the Script", "_mesh_from_unity.html#autotoc_md43", [
        [ "Adding References to Properties Through the Unity Inspector", "_mesh_from_unity.html#autotoc_md44", null ],
        [ "Comparing Output", "_mesh_from_unity.html#autotoc_md45", null ]
      ] ],
      [ "Conclusion", "_mesh_from_unity.html#autotoc_md46", null ]
    ] ],
    [ "Reading an Imported Mesh within Unity", "_unity_imported_mesh.html", [
      [ "Intro", "_unity_imported_mesh.html#autotoc_md47", null ],
      [ "Scene Setup", "_unity_imported_mesh.html#autotoc_md48", null ],
      [ "Helper Functions", "_unity_imported_mesh.html#autotoc_md49", null ],
      [ "Loading the Mesh for DHART", "_unity_imported_mesh.html#autotoc_md50", [
        [ "Script Setup", "_unity_imported_mesh.html#autotoc_md51", null ],
        [ "Mesh Extraction", "_unity_imported_mesh.html#autotoc_md52", null ],
        [ "Mesh Parsing", "_unity_imported_mesh.html#autotoc_md53", null ]
      ] ],
      [ "Testing BVH", "_unity_imported_mesh.html#autotoc_md54", null ],
      [ "Assigning the Mesh and Running", "_unity_imported_mesh.html#autotoc_md55", null ]
    ] ],
    [ "Visualizing DHART Data in Unity", "_unity_graph_visualization.html", [
      [ "Intro", "_unity_graph_visualization.html#autotoc_md56", null ],
      [ "Node Visualizer", "_unity_graph_visualization.html#autotoc_md57", [
        [ "Setting the Particle Property", "_unity_graph_visualization.html#autotoc_md58", null ]
      ] ],
      [ "Generating a Graph", "_unity_graph_visualization.html#autotoc_md59", [
        [ "Helper Scripts", "_unity_graph_visualization.html#autotoc_md60", null ]
      ] ]
    ] ],
    [ "DHART", "md_src__csharp_docs_markdown_mainpage.html", [
      [ "C# Documentation", "md_src__csharp_docs_markdown_mainpage.html#autotoc_md62", [
        [ "Getting Started", "md_src__csharp_docs_markdown_mainpage.html#autotoc_md63", null ]
      ] ],
      [ "Documentation", "md_src__csharp_docs_markdown_mainpage.html#autotoc_md64", null ]
    ] ],
    [ "Unity Tutorial Index", "_unity_tutorials.html", null ],
    [ "Using the C# DLL in a Visual Studio Project", "_v_s_tutorial.html", [
      [ "Intro", "_v_s_tutorial.html#autotoc_md65", [
        [ "Prerequisites", "_v_s_tutorial.html#autotoc_md66", null ]
      ] ],
      [ "Creating the project", "_v_s_tutorial.html#autotoc_md67", null ],
      [ "Adding A Reference To DHART", "_v_s_tutorial.html#autotoc_md68", null ],
      [ "Adding Native Dependencies", "_v_s_tutorial.html#autotoc_md69", null ],
      [ "Ensuring Files are Properly Placed in the Output Directory", "_v_s_tutorial.html#autotoc_md70", null ],
      [ "Testing the Interface", "_v_s_tutorial.html#autotoc_md71", [
        [ "Create a Console Project", "_v_s_tutorial.html#autotoc_md72", null ],
        [ "Writing Sample Code", "_v_s_tutorial.html#autotoc_md73", null ],
        [ "Adding a reference to the library from the Console App", "_v_s_tutorial.html#autotoc_md74", null ],
        [ "Writing And Executing the Command Line Application", "_v_s_tutorial.html#autotoc_md75", null ]
      ] ]
    ] ],
    [ "Todo List", "todo.html", null ],
    [ "Packages", "namespaces.html", [
      [ "Package List", "namespaces.html", "namespaces_dup" ],
      [ "Package Members", "namespacemembers.html", [
        [ "All", "namespacemembers.html", null ],
        [ "Enumerations", "namespacemembers_enum.html", null ]
      ] ]
    ] ],
    [ "Classes", "annotated.html", [
      [ "Class List", "annotated.html", "annotated_dup" ],
      [ "Class Index", "classes.html", null ],
      [ "Class Hierarchy", "hierarchy.html", "hierarchy" ],
      [ "Class Members", "functions.html", [
        [ "All", "functions.html", null ],
        [ "Functions", "functions_func.html", null ],
        [ "Variables", "functions_vars.html", null ],
        [ "Properties", "functions_prop.html", null ]
      ] ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"_generating_a_graph.html",
"class_d_h_a_r_t_a_p_i_1_1_spatial_structures_1_1_graph.html#a13b0b3988013b8efe3bc3bb9501de9f7"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';