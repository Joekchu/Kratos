# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/msaranshs/Kratos

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/msaranshs/Kratos/cmake_debug

# Include any dependencies generated for this target.
include applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/depend.make

# Include the progress variables for this target.
include applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/progress.make

# Include the compile flags for this target's objects.
include applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/flags.make

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application.cpp.o: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/flags.make
applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application.cpp.o: ../applications/GeodataProcessingApplication/geodata_processing_application.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/msaranshs/Kratos/cmake_debug/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application.cpp.o"
	cd /home/msaranshs/Kratos/cmake_debug/applications/GeodataProcessingApplication && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application.cpp.o -c /home/msaranshs/Kratos/applications/GeodataProcessingApplication/geodata_processing_application.cpp

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application.cpp.i"
	cd /home/msaranshs/Kratos/cmake_debug/applications/GeodataProcessingApplication && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/msaranshs/Kratos/applications/GeodataProcessingApplication/geodata_processing_application.cpp > CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application.cpp.i

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application.cpp.s"
	cd /home/msaranshs/Kratos/cmake_debug/applications/GeodataProcessingApplication && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/msaranshs/Kratos/applications/GeodataProcessingApplication/geodata_processing_application.cpp -o CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application.cpp.s

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application.cpp.o.requires:
.PHONY : applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application.cpp.o.requires

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application.cpp.o.provides: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application.cpp.o.requires
	$(MAKE) -f applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/build.make applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application.cpp.o.provides.build
.PHONY : applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application.cpp.o.provides

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application.cpp.o.provides.build: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application.cpp.o

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application_variables.cpp.o: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/flags.make
applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application_variables.cpp.o: ../applications/GeodataProcessingApplication/geodata_processing_application_variables.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/msaranshs/Kratos/cmake_debug/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application_variables.cpp.o"
	cd /home/msaranshs/Kratos/cmake_debug/applications/GeodataProcessingApplication && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application_variables.cpp.o -c /home/msaranshs/Kratos/applications/GeodataProcessingApplication/geodata_processing_application_variables.cpp

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application_variables.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application_variables.cpp.i"
	cd /home/msaranshs/Kratos/cmake_debug/applications/GeodataProcessingApplication && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/msaranshs/Kratos/applications/GeodataProcessingApplication/geodata_processing_application_variables.cpp > CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application_variables.cpp.i

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application_variables.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application_variables.cpp.s"
	cd /home/msaranshs/Kratos/cmake_debug/applications/GeodataProcessingApplication && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/msaranshs/Kratos/applications/GeodataProcessingApplication/geodata_processing_application_variables.cpp -o CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application_variables.cpp.s

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application_variables.cpp.o.requires:
.PHONY : applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application_variables.cpp.o.requires

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application_variables.cpp.o.provides: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application_variables.cpp.o.requires
	$(MAKE) -f applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/build.make applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application_variables.cpp.o.provides.build
.PHONY : applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application_variables.cpp.o.provides

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application_variables.cpp.o.provides.build: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application_variables.cpp.o

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/geodata_processing_python_application.cpp.o: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/flags.make
applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/geodata_processing_python_application.cpp.o: ../applications/GeodataProcessingApplication/custom_python/geodata_processing_python_application.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/msaranshs/Kratos/cmake_debug/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/geodata_processing_python_application.cpp.o"
	cd /home/msaranshs/Kratos/cmake_debug/applications/GeodataProcessingApplication && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/geodata_processing_python_application.cpp.o -c /home/msaranshs/Kratos/applications/GeodataProcessingApplication/custom_python/geodata_processing_python_application.cpp

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/geodata_processing_python_application.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/geodata_processing_python_application.cpp.i"
	cd /home/msaranshs/Kratos/cmake_debug/applications/GeodataProcessingApplication && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/msaranshs/Kratos/applications/GeodataProcessingApplication/custom_python/geodata_processing_python_application.cpp > CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/geodata_processing_python_application.cpp.i

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/geodata_processing_python_application.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/geodata_processing_python_application.cpp.s"
	cd /home/msaranshs/Kratos/cmake_debug/applications/GeodataProcessingApplication && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/msaranshs/Kratos/applications/GeodataProcessingApplication/custom_python/geodata_processing_python_application.cpp -o CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/geodata_processing_python_application.cpp.s

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/geodata_processing_python_application.cpp.o.requires:
.PHONY : applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/geodata_processing_python_application.cpp.o.requires

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/geodata_processing_python_application.cpp.o.provides: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/geodata_processing_python_application.cpp.o.requires
	$(MAKE) -f applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/build.make applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/geodata_processing_python_application.cpp.o.provides.build
.PHONY : applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/geodata_processing_python_application.cpp.o.provides

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/geodata_processing_python_application.cpp.o.provides.build: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/geodata_processing_python_application.cpp.o

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_utilities_to_python.cpp.o: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/flags.make
applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_utilities_to_python.cpp.o: ../applications/GeodataProcessingApplication/custom_python/add_custom_utilities_to_python.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/msaranshs/Kratos/cmake_debug/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_utilities_to_python.cpp.o"
	cd /home/msaranshs/Kratos/cmake_debug/applications/GeodataProcessingApplication && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_utilities_to_python.cpp.o -c /home/msaranshs/Kratos/applications/GeodataProcessingApplication/custom_python/add_custom_utilities_to_python.cpp

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_utilities_to_python.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_utilities_to_python.cpp.i"
	cd /home/msaranshs/Kratos/cmake_debug/applications/GeodataProcessingApplication && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/msaranshs/Kratos/applications/GeodataProcessingApplication/custom_python/add_custom_utilities_to_python.cpp > CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_utilities_to_python.cpp.i

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_utilities_to_python.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_utilities_to_python.cpp.s"
	cd /home/msaranshs/Kratos/cmake_debug/applications/GeodataProcessingApplication && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/msaranshs/Kratos/applications/GeodataProcessingApplication/custom_python/add_custom_utilities_to_python.cpp -o CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_utilities_to_python.cpp.s

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_utilities_to_python.cpp.o.requires:
.PHONY : applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_utilities_to_python.cpp.o.requires

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_utilities_to_python.cpp.o.provides: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_utilities_to_python.cpp.o.requires
	$(MAKE) -f applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/build.make applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_utilities_to_python.cpp.o.provides.build
.PHONY : applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_utilities_to_python.cpp.o.provides

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_utilities_to_python.cpp.o.provides.build: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_utilities_to_python.cpp.o

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_strategies_to_python.cpp.o: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/flags.make
applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_strategies_to_python.cpp.o: ../applications/GeodataProcessingApplication/custom_python/add_custom_strategies_to_python.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/msaranshs/Kratos/cmake_debug/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_strategies_to_python.cpp.o"
	cd /home/msaranshs/Kratos/cmake_debug/applications/GeodataProcessingApplication && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_strategies_to_python.cpp.o -c /home/msaranshs/Kratos/applications/GeodataProcessingApplication/custom_python/add_custom_strategies_to_python.cpp

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_strategies_to_python.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_strategies_to_python.cpp.i"
	cd /home/msaranshs/Kratos/cmake_debug/applications/GeodataProcessingApplication && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/msaranshs/Kratos/applications/GeodataProcessingApplication/custom_python/add_custom_strategies_to_python.cpp > CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_strategies_to_python.cpp.i

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_strategies_to_python.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_strategies_to_python.cpp.s"
	cd /home/msaranshs/Kratos/cmake_debug/applications/GeodataProcessingApplication && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/msaranshs/Kratos/applications/GeodataProcessingApplication/custom_python/add_custom_strategies_to_python.cpp -o CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_strategies_to_python.cpp.s

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_strategies_to_python.cpp.o.requires:
.PHONY : applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_strategies_to_python.cpp.o.requires

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_strategies_to_python.cpp.o.provides: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_strategies_to_python.cpp.o.requires
	$(MAKE) -f applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/build.make applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_strategies_to_python.cpp.o.provides.build
.PHONY : applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_strategies_to_python.cpp.o.provides

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_strategies_to_python.cpp.o.provides.build: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_strategies_to_python.cpp.o

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/hello.cpp.o: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/flags.make
applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/hello.cpp.o: ../applications/GeodataProcessingApplication/custom_utilities/hello.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/msaranshs/Kratos/cmake_debug/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/hello.cpp.o"
	cd /home/msaranshs/Kratos/cmake_debug/applications/GeodataProcessingApplication && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/hello.cpp.o -c /home/msaranshs/Kratos/applications/GeodataProcessingApplication/custom_utilities/hello.cpp

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/hello.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/hello.cpp.i"
	cd /home/msaranshs/Kratos/cmake_debug/applications/GeodataProcessingApplication && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/msaranshs/Kratos/applications/GeodataProcessingApplication/custom_utilities/hello.cpp > CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/hello.cpp.i

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/hello.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/hello.cpp.s"
	cd /home/msaranshs/Kratos/cmake_debug/applications/GeodataProcessingApplication && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/msaranshs/Kratos/applications/GeodataProcessingApplication/custom_utilities/hello.cpp -o CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/hello.cpp.s

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/hello.cpp.o.requires:
.PHONY : applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/hello.cpp.o.requires

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/hello.cpp.o.provides: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/hello.cpp.o.requires
	$(MAKE) -f applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/build.make applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/hello.cpp.o.provides.build
.PHONY : applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/hello.cpp.o.provides

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/hello.cpp.o.provides.build: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/hello.cpp.o

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/extrusion_height_utilities.cpp.o: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/flags.make
applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/extrusion_height_utilities.cpp.o: ../applications/GeodataProcessingApplication/custom_utilities/extrusion_height_utilities.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/msaranshs/Kratos/cmake_debug/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/extrusion_height_utilities.cpp.o"
	cd /home/msaranshs/Kratos/cmake_debug/applications/GeodataProcessingApplication && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/extrusion_height_utilities.cpp.o -c /home/msaranshs/Kratos/applications/GeodataProcessingApplication/custom_utilities/extrusion_height_utilities.cpp

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/extrusion_height_utilities.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/extrusion_height_utilities.cpp.i"
	cd /home/msaranshs/Kratos/cmake_debug/applications/GeodataProcessingApplication && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/msaranshs/Kratos/applications/GeodataProcessingApplication/custom_utilities/extrusion_height_utilities.cpp > CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/extrusion_height_utilities.cpp.i

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/extrusion_height_utilities.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/extrusion_height_utilities.cpp.s"
	cd /home/msaranshs/Kratos/cmake_debug/applications/GeodataProcessingApplication && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/msaranshs/Kratos/applications/GeodataProcessingApplication/custom_utilities/extrusion_height_utilities.cpp -o CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/extrusion_height_utilities.cpp.s

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/extrusion_height_utilities.cpp.o.requires:
.PHONY : applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/extrusion_height_utilities.cpp.o.requires

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/extrusion_height_utilities.cpp.o.provides: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/extrusion_height_utilities.cpp.o.requires
	$(MAKE) -f applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/build.make applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/extrusion_height_utilities.cpp.o.provides.build
.PHONY : applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/extrusion_height_utilities.cpp.o.provides

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/extrusion_height_utilities.cpp.o.provides.build: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/extrusion_height_utilities.cpp.o

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/cleaning_utilities.cpp.o: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/flags.make
applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/cleaning_utilities.cpp.o: ../applications/GeodataProcessingApplication/custom_utilities/cleaning_utilities.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/msaranshs/Kratos/cmake_debug/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/cleaning_utilities.cpp.o"
	cd /home/msaranshs/Kratos/cmake_debug/applications/GeodataProcessingApplication && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/cleaning_utilities.cpp.o -c /home/msaranshs/Kratos/applications/GeodataProcessingApplication/custom_utilities/cleaning_utilities.cpp

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/cleaning_utilities.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/cleaning_utilities.cpp.i"
	cd /home/msaranshs/Kratos/cmake_debug/applications/GeodataProcessingApplication && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/msaranshs/Kratos/applications/GeodataProcessingApplication/custom_utilities/cleaning_utilities.cpp > CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/cleaning_utilities.cpp.i

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/cleaning_utilities.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/cleaning_utilities.cpp.s"
	cd /home/msaranshs/Kratos/cmake_debug/applications/GeodataProcessingApplication && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/msaranshs/Kratos/applications/GeodataProcessingApplication/custom_utilities/cleaning_utilities.cpp -o CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/cleaning_utilities.cpp.s

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/cleaning_utilities.cpp.o.requires:
.PHONY : applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/cleaning_utilities.cpp.o.requires

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/cleaning_utilities.cpp.o.provides: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/cleaning_utilities.cpp.o.requires
	$(MAKE) -f applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/build.make applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/cleaning_utilities.cpp.o.provides.build
.PHONY : applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/cleaning_utilities.cpp.o.provides

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/cleaning_utilities.cpp.o.provides.build: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/cleaning_utilities.cpp.o

# Object files for target KratosGeodataProcessingApplication
KratosGeodataProcessingApplication_OBJECTS = \
"CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application.cpp.o" \
"CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application_variables.cpp.o" \
"CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/geodata_processing_python_application.cpp.o" \
"CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_utilities_to_python.cpp.o" \
"CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_strategies_to_python.cpp.o" \
"CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/hello.cpp.o" \
"CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/extrusion_height_utilities.cpp.o" \
"CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/cleaning_utilities.cpp.o"

# External object files for target KratosGeodataProcessingApplication
KratosGeodataProcessingApplication_EXTERNAL_OBJECTS =

applications/GeodataProcessingApplication/KratosGeodataProcessingApplication.cpython-34m.so: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application.cpp.o
applications/GeodataProcessingApplication/KratosGeodataProcessingApplication.cpython-34m.so: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application_variables.cpp.o
applications/GeodataProcessingApplication/KratosGeodataProcessingApplication.cpython-34m.so: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/geodata_processing_python_application.cpp.o
applications/GeodataProcessingApplication/KratosGeodataProcessingApplication.cpython-34m.so: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_utilities_to_python.cpp.o
applications/GeodataProcessingApplication/KratosGeodataProcessingApplication.cpython-34m.so: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_strategies_to_python.cpp.o
applications/GeodataProcessingApplication/KratosGeodataProcessingApplication.cpython-34m.so: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/hello.cpp.o
applications/GeodataProcessingApplication/KratosGeodataProcessingApplication.cpython-34m.so: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/extrusion_height_utilities.cpp.o
applications/GeodataProcessingApplication/KratosGeodataProcessingApplication.cpython-34m.so: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/cleaning_utilities.cpp.o
applications/GeodataProcessingApplication/KratosGeodataProcessingApplication.cpython-34m.so: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/build.make
applications/GeodataProcessingApplication/KratosGeodataProcessingApplication.cpython-34m.so: kratos/libKratosCore.so
applications/GeodataProcessingApplication/KratosGeodataProcessingApplication.cpython-34m.so: external_libraries/gidpost/libgidpost.a
applications/GeodataProcessingApplication/KratosGeodataProcessingApplication.cpython-34m.so: /usr/lib/x86_64-linux-gnu/libz.so
applications/GeodataProcessingApplication/KratosGeodataProcessingApplication.cpython-34m.so: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared module KratosGeodataProcessingApplication.cpython-34m.so"
	cd /home/msaranshs/Kratos/cmake_debug/applications/GeodataProcessingApplication && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/KratosGeodataProcessingApplication.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/build: applications/GeodataProcessingApplication/KratosGeodataProcessingApplication.cpython-34m.so
.PHONY : applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/build

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/requires: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application.cpp.o.requires
applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/requires: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/geodata_processing_application_variables.cpp.o.requires
applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/requires: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/geodata_processing_python_application.cpp.o.requires
applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/requires: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_utilities_to_python.cpp.o.requires
applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/requires: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_python/add_custom_strategies_to_python.cpp.o.requires
applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/requires: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/hello.cpp.o.requires
applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/requires: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/extrusion_height_utilities.cpp.o.requires
applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/requires: applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/custom_utilities/cleaning_utilities.cpp.o.requires
.PHONY : applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/requires

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/clean:
	cd /home/msaranshs/Kratos/cmake_debug/applications/GeodataProcessingApplication && $(CMAKE_COMMAND) -P CMakeFiles/KratosGeodataProcessingApplication.dir/cmake_clean.cmake
.PHONY : applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/clean

applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/depend:
	cd /home/msaranshs/Kratos/cmake_debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/msaranshs/Kratos /home/msaranshs/Kratos/applications/GeodataProcessingApplication /home/msaranshs/Kratos/cmake_debug /home/msaranshs/Kratos/cmake_debug/applications/GeodataProcessingApplication /home/msaranshs/Kratos/cmake_debug/applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : applications/GeodataProcessingApplication/CMakeFiles/KratosGeodataProcessingApplication.dir/depend

