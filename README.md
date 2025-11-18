# 🌌 Solar System Simulation — User Manual

## 1. Introduction
This application is a **solar system simulation** built with **OpenGL** and **GLSL shaders**. It visually demonstrates planetary orbits around a central star using realistic:

- Translations  
- Rotations  
- Scaling  
- Basic lighting and color effects  

Each planet orbits and rotates independently, creating an engaging and educational visual experience.

---

## 2. Requirements

### **Operating Systems**
- Windows  
- Linux  
- macOS  

### **C++ Compiler**
- **GCC 11.4.0+** or any C++ compiler with **C++11 support**

### **Required Libraries**
- **GLFW 3.3+** — Window/context management  
- **GLEW** — OpenGL extension handling  
- **GLM** — Vector and matrix math  
- **ImGui** — Optional UI controls  

---

## 3. Installation

### **Step 1: Install Dependencies**
You need to install the required libraries. Depending on your operating system, the process varies:

#### Linux (Ubuntu/Debian):
- sudo apt-get install libglfw3-dev libglew-dev libglm-dev
#### Windows:
- Download precompiled binaries from the respective library websites and follow their installation instructions.


## **Step 2: Compile the Program**

Once the dependencies are installed, navigate to the directory containing the source files (e.g., main.cpp and basic.shader) and use the following command to compile the program:

g++ main.cpp -lglfw -lGLEW -lGLM -o solar_system


Ensure your compiler supports C++11 or higher.

## **3. Running the Application**

Run the application using:

./solar_system

**Controls**

- Mouse Movement: Rotate the camera around the solar system

- Mouse Scroll: Zoom in and out

## **4. Troubleshooting**
**Black Screen**

- If the screen stays black, check the OpenGL version of your graphics card. This simulation requires at least OpenGL 3.3 support.

- Update GPU drivers if necessary.

**Missing Shader Files**

Make sure basic.shader is located in the correct directory next to the executable.

**Compilation Errors**

- Confirm all dependencies (GLFW, GLEW, GLM) are correctly installed.

- Ensure library paths and include directories are properly linked.
