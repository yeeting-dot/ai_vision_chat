# CMakeList.txt: ai_vision_chat 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.10)
# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()
project ("ai_vision_chat")
# 设置 vcpkg 工具链文件
set(CMAKE_TOOLCHAIN_FILE "E:/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

find_package(OpenCV REQUIRED)
find_package(whisper CONFIG REQUIRED)
find_package(portaudio REQUIRED)
include_directories("${PROJECT_SOURCE_DIR}/head")
# 将源代码添加到此项目的可执行文件。
add_executable (ai_vision_chat "ai_vision_chat.cpp" "ai_vision_chat.h" "head/AudioTake.h" "source/AudioTask.cpp" "head/AudioTransLate.h" "head/RoundThread.h"  "source/AudioTranslate.cpp"   "head/Viewer.h" "source/Viewer.cpp" "head/Send.h" "source/Send.cpp")
set_target_properties(ai_vision_chat PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/target")

target_link_libraries(ai_vision_chat PRIVATE whisper ${OpenCV_LIBS} portaudio)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ai_vision_chat PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
