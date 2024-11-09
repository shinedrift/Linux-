# data_generator/generate_variable_size_files.py

import os
import struct
import random
from pathlib import Path

# 参数设置
num_files = 25000
total_size_gb = 32
total_size_bytes = total_size_gb * (1 << 30)
output_dir = Path("input")

# 创建输出目录
output_dir.mkdir(parents=True, exist_ok=True)

file_sizes = []
remaining_size = total_size_bytes

# 分配文件大小
for i in range(num_files - 1):
    file_size = random.randint(1024 * 50, min(remaining_size // 2, 1024 ** 3))  # 从50KB到1GB不等
    file_sizes.append(file_size)
    remaining_size -= file_size

file_sizes.append(remaining_size)

def generate_random_data_file(file_path, file_size):
    with open(file_path, "wb") as f:
        num_elements = file_size // 8
        for _ in range(num_elements):
            num = random.randint(-(1 << 63), (1 << 63) - 1)
            f.write(struct.pack("q", num))

for i, file_size in enumerate(file_sizes):
    file_path = output_dir / f"data_{i}.bin"
    print(f"生成文件: {file_path}，大小 {file_size // (1024):,} KB")
    generate_random_data_file(file_path, file_size)

print("所有文件生成完毕。")
