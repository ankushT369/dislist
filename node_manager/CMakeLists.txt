cmake_minimum_required(VERSION 3.10)  # Minimum required CMake version
project(dislist)                  # Define the project name and language (C)

# Add the executable and its source files
add_executable(server node_manager.c)
