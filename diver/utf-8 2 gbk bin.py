import os
import sys
 
def detect_encoding(file_path):
    """尝试用常见编码读取文件，返回文本内容和实际编码"""
    encodings = ['utf-8', 'gbk', 'gb2312', 'gb18030', 'latin-1']
    for enc in encodings:
        try:
            with open(file_path, 'r', encoding=enc) as f:
                text = f.read()
            return text, enc
        except UnicodeDecodeError:
            continue
    # 如果所有编码都失败，尝试忽略错误强制读取（用 utf-8）
    with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
        text = f.read()
        return text, 'utf-8 (with errors ignored)'

def convert_to_gbk_bin(input_path):
    if not os.path.isfile(input_path):
        print(f"错误：文件不存在 - {input_path}")
        return False

    try:
        # 自动探测编码并读取
        text, used_enc = detect_encoding(input_path)
        print(f"检测到文件编码：{used_enc}")
    except Exception as e:
        print(f"读取文件失败：{e}")
        return False

    # 编码为 GBK，忽略无法转换的字符
    gbk_bytes = text.encode('gbk', errors='ignore')
    if len(gbk_bytes) == 0 and len(text) > 0:
        print("警告：所有字符都无法用 GBK 编码，可能结果为空")

    # 生成输出文件路径（同目录，扩展名 .bin）
    base, _ = os.path.splitext(input_path)
    output_path = base + '.bin'

    try:
        with open(output_path, 'wb') as f:
            f.write(gbk_bytes)
        print(f"转换成功！")
        print(f"输出文件：{output_path}")
        print(f"文件大小：{len(gbk_bytes)} 字节")
        return True
    except PermissionError:
        print(f"错误：没有权限写入文件 - {output_path}")
        return False
    except Exception as e:
        print(f"写入文件失败：{e}")
        return False

def main():
    if len(sys.argv) > 1:
        # 命令行参数模式
        input_path = sys.argv[1]
        convert_to_gbk_bin(input_path)
    else:
        # 交互模式
        print("=== UTF-8/GBK 转 GBK 二进制文件转换工具 ===")
        print("（自动检测源文件编码）")
        while True:
            input_path = input("请输入文本文件路径（直接回车退出）：").strip()
            if not input_path:
                print("已退出。")
                break
            # 去除首尾引号
            if input_path.startswith('"') and input_path.endswith('"'):
                input_path = input_path[1:-1]
            if input_path.startswith("'") and input_path.endswith("'"):
                input_path = input_path[1:-1]
            convert_to_gbk_bin(input_path)
            print("-" * 50)

if __name__ == "__main__":
    main()
