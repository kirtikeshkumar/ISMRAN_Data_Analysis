# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization/build

# Include any dependencies generated for this target.
include CMakeFiles/Test_DirListing.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Test_DirListing.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Test_DirListing.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Test_DirListing.dir/flags.make

CMakeFiles/Test_DirListing.dir/test/core/Test_DirListing.cpp.o: CMakeFiles/Test_DirListing.dir/flags.make
CMakeFiles/Test_DirListing.dir/test/core/Test_DirListing.cpp.o: /media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization/test/core/Test_DirListing.cpp
CMakeFiles/Test_DirListing.dir/test/core/Test_DirListing.cpp.o: CMakeFiles/Test_DirListing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Test_DirListing.dir/test/core/Test_DirListing.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Test_DirListing.dir/test/core/Test_DirListing.cpp.o -MF CMakeFiles/Test_DirListing.dir/test/core/Test_DirListing.cpp.o.d -o CMakeFiles/Test_DirListing.dir/test/core/Test_DirListing.cpp.o -c /media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization/test/core/Test_DirListing.cpp

CMakeFiles/Test_DirListing.dir/test/core/Test_DirListing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Test_DirListing.dir/test/core/Test_DirListing.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization/test/core/Test_DirListing.cpp > CMakeFiles/Test_DirListing.dir/test/core/Test_DirListing.cpp.i

CMakeFiles/Test_DirListing.dir/test/core/Test_DirListing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Test_DirListing.dir/test/core/Test_DirListing.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization/test/core/Test_DirListing.cpp -o CMakeFiles/Test_DirListing.dir/test/core/Test_DirListing.cpp.s

# Object files for target Test_DirListing
Test_DirListing_OBJECTS = \
"CMakeFiles/Test_DirListing.dir/test/core/Test_DirListing.cpp.o"

# External object files for target Test_DirListing
Test_DirListing_EXTERNAL_OBJECTS =

Test_DirListing: CMakeFiles/Test_DirListing.dir/test/core/Test_DirListing.cpp.o
Test_DirListing: CMakeFiles/Test_DirListing.dir/build.make
Test_DirListing: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libCore.so
Test_DirListing: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libImt.so
Test_DirListing: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libRIO.so
Test_DirListing: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libNet.so
Test_DirListing: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libHist.so
Test_DirListing: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libGraf.so
Test_DirListing: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libGraf3d.so
Test_DirListing: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libGpad.so
Test_DirListing: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libROOTDataFrame.so
Test_DirListing: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libTree.so
Test_DirListing: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libTreePlayer.so
Test_DirListing: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libRint.so
Test_DirListing: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libPostscript.so
Test_DirListing: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libMatrix.so
Test_DirListing: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libPhysics.so
Test_DirListing: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libMathCore.so
Test_DirListing: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libThread.so
Test_DirListing: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libMultiProc.so
Test_DirListing: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libROOTVecOps.so
Test_DirListing: CMakeFiles/Test_DirListing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Test_DirListing"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Test_DirListing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Test_DirListing.dir/build: Test_DirListing
.PHONY : CMakeFiles/Test_DirListing.dir/build

CMakeFiles/Test_DirListing.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Test_DirListing.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Test_DirListing.dir/clean

CMakeFiles/Test_DirListing.dir/depend:
	cd /media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization /media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization /media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization/build /media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization/build /media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization/build/CMakeFiles/Test_DirListing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Test_DirListing.dir/depend

