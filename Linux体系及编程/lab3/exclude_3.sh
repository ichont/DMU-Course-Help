#!/bin/bash

n=$1

# 是否有n值
if [ -z "$n" ]; then
    echo "请提供一个正整数作为参数。"
    exit 1
fi

# 是否为正整数
if ! [[ "$n" =~ ^[0-9]+$ ]]; then
    echo "输入的不是正整数，请重新输入。"
    exit 1
fi

# 遍历
for ((i=1; i<=n; i++)); do
    # 检查是否包含3或3的倍数
    if ! [[ "$i" =~ 3 ]] && (( i % 3 != 0 )); then
        echo "$i"
    fi
done
