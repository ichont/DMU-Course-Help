#!/bin/bash

# 出勤记录目录
RECORDS_DIR="/home/buyhorse1/records/02-softdata"

# 输出文件路径
OUTPUT_FILE="/home/soft2043/lab3/records.txt"

# 保存自己的学号
MY_USERNAME="soft2043"

# 创建一个关联数组
declare -A attendance

# 获取所有用户的列表
mapfile -t users < <(ls /home)

# 遍历目录中的所有文件
for file in "$RECORDS_DIR"/*; do
    # 提取日期
    date=$(basename "$file" | cut -c1-8)
    
    # 保留日期
    unique_dates+=("$date")

    # 日期去重
    unique_dates=($(echo "${unique_dates[@]}" | tr ' ' '\n' | sort -u | tr '\n' ' '))
done

# 遍历日期列表
for date in "${unique_dates[@]}"; do
    declare -A temp_attendance
    
    # 遍历文件
    for file in "$RECORDS_DIR"/"$date"*; do
        while IFS= read -r line; do
            # 提取USER列
            user=$(echo "$line" | awk '{print $1}')
            
            # 检查用户是否存在于用户列表中
            if [[ " ${users[*]} " == *" $user "* ]]; then
                # 添加或更新出勤记录
                if [[ -z ${temp_attendance[$user]} ]]; then
                    temp_attendance[$user]=1
                fi
            fi
        done < "$file"
    done
    
    # 合并出勤记录
    for user in "${!temp_attendance[@]}"; do
        ((attendance[$user] += temp_attendance[$user]))
    done
done

# 输出学生的出勤次数
for user in "${!attendance[@]}"; do
    echo "$user:${attendance[$user]}"
done | sort -k1 > "$OUTPUT_FILE"

# 自己的出勤记录添加到文件最后一行
my_attendance_count=${attendance[$MY_USERNAME]}
if [[ -n $my_attendance_count ]]; then
    echo "$MY_USERNAME:$my_attendance_count" >> "$OUTPUT_FILE"
fi

# 输出最终的出勤记录文件
cat "$OUTPUT_FILE"
