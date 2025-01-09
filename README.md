# DesktopManager

## Overview
DesktopManager is a software project designed for efficient desktop management and functionality. This README provides step-by-step instructions for configuring and running the program.

---

## Requirements
To run the program, ensure you have the following tools installed on your computer:

1. **CMake**
   - Check installation: `cmake --version`
   - Install via pip if missing: `pip install cmake`

2. **Ninja**
   - Check installation: `ninja --version`
   - Install via pip if missing: `pip install ninja`

### Minimum Requirements
The minimum requirements are described in the `DesktopManager/CMakeLists.txt` file. Please review it to ensure compatibility with your environment.

---

## Installation and Configuration
Follow these steps to build and run the program:

1. Navigate to the `DesktopManager/build/` directory in your terminal.

2. Run the following commands:

   ```bash
   cmake -G Ninja ..
   ninja
   ./my_program.exe
