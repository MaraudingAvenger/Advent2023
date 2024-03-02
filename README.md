# Advent of Code 2023 in C++

I'm going to solve the Advent of Code 2023 puzzles in C++. It's probably going to be a doozy, but I'm excited to try it in C++, at least. This is also a way for me to practice my C++ skills and learn more about C++20 features. I'm not going for ultimate performance or anything, just trying to solve the puzzles in a way that's fun and interesting to me.

If there are any glaring issues with my code, please let me know! I'm always looking to improve.

## Overall structure

I've gone with a strange structure for this project because I want to be able to run the code for each day separately. I'm sure it's not the best way to do it, but I like being able to plug each day into the main as its own header file and run them all separately.

Right now `main()` scans takes a command line argument for the directory that the input files are stored in. It then scans the directory for `.txt` files and runs the appropriate day on each file (assuming the files are named `"day1.txt"`, `"day2.txt"`, etc.).

I'm sure this will change as I go, especially as I add features and functionality, but I'm happy with it for now.

## Building and running

I'm using Visual Studio and its inbuilt MSVC compiler, and using C++20 features. I'm not sure if I'm using any MSVC-specific features, but I'm not using any C++20 features that aren't supported by MSVC.

If you want to build and run this yourself, I've included the vcxproj file in the repo. You should be able to open the project in Visual Studio and build it from there. I'm not sure if it will work with other compilers, but I don't see why it wouldn't as long as they support C++20.
