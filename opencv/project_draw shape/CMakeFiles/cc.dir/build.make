# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = "/home/cc/Desktop/opencv/project_draw shape"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/cc/Desktop/opencv/project_draw shape"

# Include any dependencies generated for this target.
include CMakeFiles/cc.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cc.dir/flags.make

CMakeFiles/cc.dir/main.cpp.o: CMakeFiles/cc.dir/flags.make
CMakeFiles/cc.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/cc/Desktop/opencv/project_draw shape/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cc.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cc.dir/main.cpp.o -c "/home/cc/Desktop/opencv/project_draw shape/main.cpp"

CMakeFiles/cc.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cc.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/cc/Desktop/opencv/project_draw shape/main.cpp" > CMakeFiles/cc.dir/main.cpp.i

CMakeFiles/cc.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cc.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/cc/Desktop/opencv/project_draw shape/main.cpp" -o CMakeFiles/cc.dir/main.cpp.s

# Object files for target cc
cc_OBJECTS = \
"CMakeFiles/cc.dir/main.cpp.o"

# External object files for target cc
cc_EXTERNAL_OBJECTS =

cc: CMakeFiles/cc.dir/main.cpp.o
cc: CMakeFiles/cc.dir/build.make
cc: /usr/local/lib/libopencv_highgui.so.4.10.0
cc: /usr/local/lib/libopencv_ml.so.4.10.0
cc: /usr/local/lib/libopencv_objdetect.so.4.10.0
cc: /usr/local/lib/libopencv_photo.so.4.10.0
cc: /usr/local/lib/libopencv_stitching.so.4.10.0
cc: /usr/local/lib/libopencv_video.so.4.10.0
cc: /usr/local/lib/libopencv_videoio.so.4.10.0
cc: /usr/local/lib/libopencv_imgcodecs.so.4.10.0
cc: /usr/local/lib/libopencv_calib3d.so.4.10.0
cc: /usr/local/lib/libopencv_dnn.so.4.10.0
cc: /usr/local/lib/libopencv_features2d.so.4.10.0
cc: /usr/local/lib/libopencv_flann.so.4.10.0
cc: /usr/local/lib/libopencv_imgproc.so.4.10.0
cc: /usr/local/lib/libopencv_core.so.4.10.0
cc: CMakeFiles/cc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/cc/Desktop/opencv/project_draw shape/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cc"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cc.dir/build: cc

.PHONY : CMakeFiles/cc.dir/build

CMakeFiles/cc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cc.dir/clean

CMakeFiles/cc.dir/depend:
	cd "/home/cc/Desktop/opencv/project_draw shape" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/cc/Desktop/opencv/project_draw shape" "/home/cc/Desktop/opencv/project_draw shape" "/home/cc/Desktop/opencv/project_draw shape" "/home/cc/Desktop/opencv/project_draw shape" "/home/cc/Desktop/opencv/project_draw shape/CMakeFiles/cc.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/cc.dir/depend

