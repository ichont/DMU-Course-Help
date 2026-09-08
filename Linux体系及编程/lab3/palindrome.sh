#!/bin/bash

# 脚本功能：计算从 1 到给定正整数 n 之间的回文数，并输出这些回文数以及总数。

# 获取用户输入的参数 n
n=$1

# 检查是否提供了参数 n
if [ -z "$n" ]; then
    echo "请提供一个正整数作为参数。"
    echo "用法示例：./script.sh 100"
    exit 1
fi

# 检查参数 n 是否为正整数
case $n in 
	''|*[!0-9]*|*[-.]*[[:space:]]*)
		echo "输入的不是正整数，请重新输入。"
		exit 1
		;;
esac

# 用于统计回文数的计数器初始化
palindrome_count=0

# 遍历从 1 到 n 的整数
for ((i=1; i<=n; i++)); do
    # 将整数 i 转换为字符串，以便后续处理
    str_i=$i

    # 使用 rev 命令反转字符串
    rev_str=$(echo "$str_i" | rev)

    # 比较原始字符串和反转后的字符串是否相同
    if [ "$str_i" == "$rev_str" ]; then
        # 如果是回文数，增加计数器，并打印该回文数
        ((palindrome_count++))
        echo "发现回文数: $i"
    fi
done

# 输出找到的回文数的总数
echo "总共找到 $palindrome_count 个回文数。"

# 额外功能：将结果保存到文件中
# 获取当前日期作为文件名的一部分，格式为 YYYYMMDD
current_date=$(date +%Y%m%d)
# 定义结果文件的名称，包含日期和计数信息
result_file="result2.txt"
# 将回文数列表和总数写入结果文件
{
    echo "回文数列表："
    for ((i=1; i<=n; i++)); do
        str_i=$i
        rev_str=$(echo "$str_i" | rev)
        if [ "$str_i" == "$rev_str" ]; then
            echo "$i"
        fi
    done
    echo "总共找到 $palindrome_count 个回文数。"
} > "$result_file"
echo "结果已保存到文件：$result_file"
