# Arinc429_Code
Due to project confidentiality, this repository only showcases partial code of the ARINC429 avionics data acquisition card project.
***
# ARINC429 Avionics Data Acquisition Card
This project implements a comprehensive ARINC 429 avionics data acquisition system, specifically designed for aerospace applications.  
The system adopts a three-layer architecture, achieving complete decoupling of hardware drivers, middleware abstraction, and application interfaces. It supports plug-and-play for multiple avionics bus chips such as DEI1016/HI3593/HI8588, providing reliable data acquisition and transmission capabilities.
***

# Project Highlights
🛠️ **Hardware Abstraction Architecture**: Three-layer design decouples hardware operations from application logic  
✈️ **Aviation Protocol Support**: Full ARINC 429 protocol implementation  
⚡ **High-Performance Design**: Register-level optimized operations  
🔒 **Reliability Assurance**: Rigorous error handling mechanisms  
🔄 **RTOS Integration**: RT-Thread real-time operating system support
***
# Code Structure
    
    arinc429-data-acquisition/  
    ├── Application/          # Application Layer Interfaces  
    │   ├── App_adaptor.c     # User API Implementation  
    │   ├── App_adaptor.h     # Application Layer Header  
    │   ├── XXXXXX.C    
    │   └── XXXXXX.h    
    │  
    ├── Middleware/           # Middleware Abstraction Layer  
    │   ├── Middle_adaptor.c  # Middleware Driver Adapter  
    │   ├── Middle_adaptor.h  # Middleware Adapter Interface  
    │   ├── Middle_normal.c   # Common Middleware Logic  
    │   ├── Middle_normal.h   # Middleware Data Structures  
    │   ├── XXXXXX.C    
    │   └── XXXXXX.h    
    │  
    ├── Driver/               # Hardware Drivers  
    │   ├── Hi3593/            
    │   ├── Hi8585/   
    │   └── DEI1016/          # DEI1016 Chip Driver  
    │       ├── Driver_dei1016.c       # Driver Implementation & Registration  
    │       ├── Driver_dei1016.h       # Device Structure Definitions  
    │       └── Driver_dei1016_config.h# Hardware Configuration           
    │  
    └── Config/               # Global Configuration    
        ├── Arinc_config.h    # Project Configuration  
        └── Arinc_type.h      # Data Types
***
# Core File Descriptions                           
    Application/App_adaptor.c	       # Provides user API interfaces, including initialization, transmission, and reception  
    Middleware/Middle_adaptor.c	       # Hardware driver adapter, bridges application and driver layers  
    Driver/DEI1016/Driver_dei1016.c	       # Low-level driver implementation for DEI1016 chip  
    Config/Arinc_type.h	               # Defines core data structures and enumerations for the project
***

# Author
​​StitchLilo626​​  
Email: qgwei626@gmail.com  
MCU Platform: STM32F429 Series  
RTOS: RT-Thread 4.0
