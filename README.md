# Arinc429_Code
受项目特殊性，该仓库仅展示部分ARINC429航空总线数据采集卡项目代码。
***
# ARINC429航空总线数据采集卡
该项目实现了一个完整的ARINC 429航空总线数据采集系统，专为航空航天应用设计。  
系统采用三层架构设计，实现硬件驱动、中间层抽象和应用接口的完全解耦，支持DEI1016/HI3593/HI8588等多款航空总线芯片的即插即用，提供可靠的数据采集和传输能力。
***

# 项目亮点
🛠️ **​​硬件抽象架构**​​：三层设计解耦硬件操作与应用逻辑  
✈️ ​​**航空协议支持​**​：完整ARINC 429协议实现  
⚡ ​​**高性能设计​​**：寄存器级优化操作  
🔒 ​​**可靠性保障**​​：严格错误处理机制  
🔄 ​​**RTOS集成​**​：RTThread实时操作系统支持
***
# 代码框架
    
    arinc429-data-acquisition/  
    ├── Application/          # 应用层接口  
    │   ├── App_adaptor.c     # 应用层用户API实现  
    │   ├── App_adaptor.h     # 应用层头文件  
    │   ├── XXXXXX.C    
    │   └── XXXXXX.h    
    │  
    ├── Middleware/           # 中间抽象层  
    │   ├── Middle_adaptor.c  # 中间层驱动适配器  
    │   ├── Middle_adaptor.h  # 中间层适配器接口  
    │   ├── Middle_normal.c   # 中间层通用逻辑  
    │   ├── Middle_normal.h   # 中间层数据结构  
    │   ├── XXXXXX.C    
    │   └── XXXXXX.h    
    │  
    ├── Driver/               # 硬件驱动  
    │   ├── Hi3593/            
    │   ├── Hi8585/   
    │   └── DEI1016/          # DEI1016芯片驱动  
    │       ├── Driver_dei1016.c       # 驱动实现及注册  
    │       ├── Driver_dei1016.h       # 设备结构定义  
    │       └── Driver_dei1016_config.h# 硬件配置           
    │  
    └── Config/               # 全局配置    
        ├── Arinc_config.h    # 项目配置  
        └── Arinc_type.h      # 数据类型
***
# 部分核心文件说明                           
    Application/App_adaptor.c	       # 提供用户API接口，实现初始化、发送和接收功能  
    Middleware/Middle_adaptor.c	       # 硬件驱动适配器，连接应用层和驱动层  
    Driver/DEI1016/Driver_dei1016.c	   # DEI1016芯片底层驱动实现  
    Config/Arinc_type.h	               # 定义项目核心数据结构和枚举类型
***

# 作者
​​StitchLilo626​​  
邮箱: qgwei626@gmail.com  
MCU平台: STM32F429系列  
RTOS: RT-Thread 4.0+