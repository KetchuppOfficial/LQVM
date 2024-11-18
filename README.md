# LQVM - Low Quality Virtual Machine

Implementation of a simple virtual machine. I want to thank my dear friend
[Alex Romanov](https://github.com/ajlekcahdp4) for coming up with the name brilliant name of this
project.

## Requirements

The following applications and libraries have to be installed:

- CMake of version 3.21 (or higher)
- python3
- python3-venv
- pip

## How to build

### 0) Make sure you are in the root directory of the project (i.e. LQVM/)

### 1) Installing conan and other python modules this project depends on

```bash
python3 -m venv .venv
source .venv/bin/activate
pip3 install -r requirements.txt
```

### 2) Build the project

```bash
conan install . --output-folder=third_party --build=missing -s compiler.cppstd=23
cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=./third_party/conan_toolchain.cmake
cmake --build build [--target <tgt>]
```
