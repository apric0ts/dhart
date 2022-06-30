
Overview
========

Welcome to DHART: Design, Humans, Analysis, and RoboTics -- A C++ package with interfaces to Python, C, and C#. 

There are a few components to the package, but the main focus is in providing fast ray-casting interfaces for python and C# for a variety of analysis and evaluation techniques.  Generally, you should be able to build a grid-like structure of the floors for a 3D model, calculate shortest paths by distance and custom metrics, and use these tools inside of a variety of programs such as Unity, Rhino, Revit, and more. 

We have extensive documentation on the API, and welcome new contributions and bug fixes. Please make sure to take a look at the contributing guide.  

Features
--------

- Python, C, C#, C++ interface
- Extract connected grid-based graphs from 3d models
- Calculate shortest path based on Distance, Energy, Visibility, and others
- Graph parsing traverses stairs and slopes
- Easily generate visibility graphs and analyze locations of environment
- Calculate view scores, percentage of view, and points of interest
- Uses Embree raytracer for fast raycasting
- Demos and instructions for integrating with Rhino 3D and Unity


Credits
-------


This repository contains work that was supported in part by the U.S.
Army Combat Capabilities Development Command (CCDC) Armaments
Center and the U.S. Army ManTech Office under Contract Delivery
Order W15QKN19F0002 - Advanced Development of Asset Protection
Technologies (ADAPT).

If you find this repo useful, please cite using the following bibtex
```
@article{schwartz2021human,
  title={Human centric accessibility graph for environment analysis},
  author={Schwartz, Mathew},
  journal={Automation in Construction},
  volume={127},
  pages={103557},
  year={2021},
  publisher={Elsevier}
}
```

There were dozens of contributors to this project over the years.  It has been led by Mathew Schwartz (NJIT) with a large part of the development by Drew Balletto. 


Getting started
===============


Installing
----------

- Requires Windows 10

Depending on your goal, you may want to download the Python or the C# release. Each one has a different process. 

When visiting the documentation page, click on Python to follow installation guide for running in a python environment or as a Python Grasshopper node for Rhino.  Click on the C# documentation for a guide on how to use the project with Unity. 


Building from Source
--------------------

This guide will describe how to retrieve the contents of this repository,
and build from source.

Please note: DHART is currently designed to run on a PC running the Windows 10
operating system.
Also note: This guide is a 'work-in-progress' and subject to change.


Git for Windows:
If you do not already have Git for Windows on your machine,
please download and install Git for Windows at https://gitforwindows.org/
Microsoft Visual Studio 2019:
https://visualstudio.microsoft.com/downloads/
You may use the Community edition.
CMake (Windows win64-x64)
https://cmake.org/download/


Once the software above is installed on your machine,
you may continue with the following:

0. Open Git Bash.
Git Bash (MINGW64) begins at ~, your home directory.
You may remain here, or navigate to a directory of your choice.
In the next step, you will clone the Analysis repository.


1. Type git clone git@github.com/cadop/dhart.git at the prompt
and hit ENTER. The Analysis repository will then be cloned to your local machine.


2. Note that the time of this writing (06/03/2020 16:19), Analysis will build
only on the UpdateCMake branch.
To switch the branch from master to UpdateCMake,
type git checkout UpdateCMake at the prompt.
You will now be on the UpdateCMake branch.


3. Open Microsoft Visual Studio 2019. After seeing the splash/welcome screen,
please click the button that reads Open a local folder.

4. When the Browse window appears, navigate to the Analysis folder
(the repository that you had cloned) on your local machine.
Then, navigate to src.
Click the Select folder button to confirm.


5. If the Solution Explorer view is not already open, you may open by
navigating to View > Solution Explorer, or alternatively,
you can also use the Ctrl + Alt + L shortcut to reveal Solution Explorer.
Here, you can examine the sources imported by Visual Studio.


6. We are now ready to build Analysis.
CMake is used to aid in the compilation process.
To build, navigate to Build > Build All,
or you may use the Ctrl + Shift + B keyboard shortcut.

You have now built the sources for Analysis.

You can find the build files in .\Analysis\src\out\build\x64-Debug
