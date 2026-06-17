#基于stm32c8t6和w25q64 norflash

#通过sscom串口(串口使用gbk编码)发送向w25q64写入一整本书，用环形缓冲区缓冲，每256字节分包并延时10ms，留给写入flash的时间


##环境
keil+vscode

##使用方法
通过.py脚本把文件转成gbk编码的bin文件

在sscom选择256字节延时10ms

在串口发送bin文件 