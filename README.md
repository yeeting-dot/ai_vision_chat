# ai_vision_chat
七牛云——6月12日选题——Ai视觉助手
> demo示例：通过网盘分享的文件，提取码: kvam:[ai视觉助手.mp4](https://pan.baidu.com/s/1yYprAENax5Ewo_ig7BmVVA?pwd=kvam)
## 引用库
库的管理方式——通过vcpkg安装并通过```vcpkg integrate install```命令继承到visualstudio，还需再CmakePreset.json的x64-debug中设置cmake构建文件路径
1. opencv库【摄像头捕捉】
2. portaudio库【音频采集】
3. whisper库【语音转录】
4. [外部资源，语音转录本地模型](https://huggingface.co/ggerganov/whisper.cpp/blob/main/ggml-small.bin)

> 库安装后需要放置在Resources文件夹下

## 主要数据结构
RoundThread:抽象类，用于实例化各类缓冲区，是生产-消费模型的主要数据结构

VoiceMess: Struct结构体，存储音频数据，作为生产者将资源给RoundThread<VoiceMess>

RoundThread<std::string>: 实例化文本缓冲区，当声音在portAudio处理中被转换为文本的时候写入此缓冲区；Viewer类读取该缓冲区

SendObject：Struct结构体，存储单条可发送给api大模型的数据，存储单条语音和摄像头截取快照【后续仍需将图片转换为base-64】

RoundThread<SendObject>: 实例化SendObject缓冲区，有Viewer捕捉摄像头数据写入，由Send类读出并通过窗口显示图片和文本

## 主要架构
多线程并行 + 循环处理 + 回调执行

## 流程图示

~~~mermaid
graph LR
VoiceTake["音频采集"]
VoiceMessCache["音频信息缓存"]
AudioTranslate["音频翻译"]
TextCache["文本缓存"]
Viewer["摄像头采集"]
SendObjectCache["图像 + 文本缓存"]
Send["发送Http（暂时为显示）"]

VoiceTake--write-->VoiceMessCache
AudioTranslate--read-->VoiceMessCache
AudioTranslate--write-->TextCache
Viewer--read-->TextCache
Viewer--write-->SendObjectCache
Send--read-->SendObjectCache
Send--show-->Show["窗口显示图像和文本"]
~~~
