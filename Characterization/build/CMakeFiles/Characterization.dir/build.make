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
include CMakeFiles/Characterization.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Characterization.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Characterization.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Characterization.dir/flags.make

CMakeFiles/Characterization.dir/src/CharacterizationFileReader.cpp.o: CMakeFiles/Characterization.dir/flags.make
CMakeFiles/Characterization.dir/src/CharacterizationFileReader.cpp.o: /media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization/src/CharacterizationFileReader.cpp
CMakeFiles/Characterization.dir/src/CharacterizationFileReader.cpp.o: CMakeFiles/Characterization.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Characterization.dir/src/CharacterizationFileReader.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Characterization.dir/src/CharacterizationFileReader.cpp.o -MF CMakeFiles/Characterization.dir/src/CharacterizationFileReader.cpp.o.d -o CMakeFiles/Characterization.dir/src/CharacterizationFileReader.cpp.o -c /media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization/src/CharacterizationFileReader.cpp

CMakeFiles/Characterization.dir/src/CharacterizationFileReader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Characterization.dir/src/CharacterizationFileReader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization/src/CharacterizationFileReader.cpp > CMakeFiles/Characterization.dir/src/CharacterizationFileReader.cpp.i

CMakeFiles/Characterization.dir/src/CharacterizationFileReader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Characterization.dir/src/CharacterizationFileReader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization/src/CharacterizationFileReader.cpp -o CMakeFiles/Characterization.dir/src/CharacterizationFileReader.cpp.s

CMakeFiles/Characterization.dir/src/Helpers.cpp.o: CMakeFiles/Characterization.dir/flags.make
CMakeFiles/Characterization.dir/src/Helpers.cpp.o: /media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization/src/Helpers.cpp
CMakeFiles/Characterization.dir/src/Helpers.cpp.o: CMakeFiles/Characterization.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Characterization.dir/src/Helpers.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Characterization.dir/src/Helpers.cpp.o -MF CMakeFiles/Characterization.dir/src/Helpers.cpp.o.d -o CMakeFiles/Characterization.dir/src/Helpers.cpp.o -c /media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization/src/Helpers.cpp

CMakeFiles/Characterization.dir/src/Helpers.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Characterization.dir/src/Helpers.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization/src/Helpers.cpp > CMakeFiles/Characterization.dir/src/Helpers.cpp.i

CMakeFiles/Characterization.dir/src/Helpers.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Characterization.dir/src/Helpers.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization/src/Helpers.cpp -o CMakeFiles/Characterization.dir/src/Helpers.cpp.s

# Object files for target Characterization
Characterization_OBJECTS = \
"CMakeFiles/Characterization.dir/src/CharacterizationFileReader.cpp.o" \
"CMakeFiles/Characterization.dir/src/Helpers.cpp.o"

# External object files for target Characterization
Characterization_EXTERNAL_OBJECTS =

libCharacterization.so: CMakeFiles/Characterization.dir/src/CharacterizationFileReader.cpp.o
libCharacterization.so: CMakeFiles/Characterization.dir/src/Helpers.cpp.o
libCharacterization.so: CMakeFiles/Characterization.dir/build.make
libCharacterization.so: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libCore.so
libCharacterization.so: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libImt.so
libCharacterization.so: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libRIO.so
libCharacterization.so: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libNet.so
libCharacterization.so: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libHist.so
libCharacterization.so: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libGraf.so
libCharacterization.so: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libGraf3d.so
libCharacterization.so: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libGpad.so
libCharacterization.so: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libROOTDataFrame.so
libCharacterization.so: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libTree.so
libCharacterization.so: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libTreePlayer.so
libCharacterization.so: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libRint.so
libCharacterization.so: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libPostscript.so
libCharacterization.so: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libMatrix.so
libCharacterization.so: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libPhysics.so
libCharacterization.so: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libMathCore.so
libCharacterization.so: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libThread.so
libCharacterization.so: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libMultiProc.so
libCharacterization.so: /home/kirtikesh/Softwares/root_6.28.00/install/lib/libROOTVecOps.so
libCharacterization.so: CMakeFiles/Characterization.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library libCharacterization.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Characterization.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Characterization.dir/build: libCharacterization.so
.PHONY : CMakeFiles/Characterization.dir/build

CMakeFiles/Characterization.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Characterization.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Characterization.dir/clean

CMakeFiles/Characterization.dir/depend:
	cd /media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization /media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization /media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization/build /media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization/build /media/kirtikesh/Kirtikesh_4TB/ISMRAN/ISMRAN_Data_Analysis/Characterization/build/CMakeFiles/Characterization.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Characterization.dir/depend
