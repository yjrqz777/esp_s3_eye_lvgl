# -*- coding: utf-8 -*-
import json
import re

def json2arry(json_file):
    with open(json_file, 'r') as f:
        data = json.load(f)
    # 1. 生成JSON字符串（紧凑模式）
    json_str = json.dumps(data, ensure_ascii=False)  # 保留非ASCII字符

    # 2. 转义双引号和反斜杠（适应C字符串）
    c_str = json_str.replace('\\', '\\\\').replace('"', '\\"')

    # 3. 添加C语言字符串定义
    c_code = f'const char *json_data = "{c_str}";'

    print(c_code)

    # 生成C语言代码

    with open('json_data.c', 'w') as f:
        f.write(c_code)

    return c_code


if __name__ == '__main__':
    json_file = 'rlottie.json'
    data = json2arry(json_file)

    print(data)
