cmake_minimum_required(VERSION 3.16)
project(SnakeGame VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 设置调试选项
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

# 设置Qt路径
set(CMAKE_PREFIX_PATH "G:/Qt/6.9.0/mingw_64")

# 查找Qt包
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Multimedia)

# 设置包含目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${Qt6Core_INCLUDE_DIRS}
    ${Qt6Gui_INCLUDE_DIRS}
    ${Qt6Widgets_INCLUDE_DIRS}
    ${Qt6Multimedia_INCLUDE_DIRS}
)

# 添加源文件
set(SOURCES
    src/main.cpp
    src/snakegame.cpp
    src/gamerenderer.cpp
    src/snake.cpp
    src/food.cpp
    src/menuwindow.cpp
    src/soundmanager.cpp
    resources.qrc
)

# 添加头文件
set(HEADERS
    include/snakegame.h
    include/gamerenderer.h
    include/snake.h
    include/food.h
    include/menuwindow.h
    include/soundmanager.h
)

# 创建可执行文件
add_executable(SnakeGame WIN32 ${SOURCES} ${HEADERS})

# 链接Qt库
target_link_libraries(SnakeGame PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Multimedia
)

# 设置包含目录
target_include_directories(SnakeGame PRIVATE include)

# 设置输出目录
set_target_properties(SnakeGame PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# 安装规则
install(TARGETS SnakeGame
    RUNTIME DESTINATION bin
)

# 部署Qt依赖项
if(WIN32)
    add_custom_command(TARGET SnakeGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:Qt6::Core>
            $<TARGET_FILE:Qt6::Gui>
            $<TARGET_FILE:Qt6::Widgets>
            $<TARGET_FILE:Qt6::Multimedia>
            $<TARGET_FILE_DIR:SnakeGame>
    )
    
    # 复制平台插件
    add_custom_command(TARGET SnakeGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
            $<TARGET_FILE_DIR:SnakeGame>/platforms
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:Qt6::QWindowsIntegrationPlugin>
            $<TARGET_FILE_DIR:SnakeGame>/platforms
    )
endif() 