#!/bin/bash

# 成绩信息文件
score_file="score.txt"

# 如果成绩信息文件不存在，则会新建
if [ ! -f "$score_file" ]; then
    touch "$score_file"
fi

# 检查学号是否唯一
check_unique_id() {
    local id=$1
    if grep -q "^$id	" "$score_file"; then
        return 0
    else
        return 1
    fi
}

# 添加学生成绩信息
add_score() {
    echo "请输入新添加学生的学号："
    read id

    # 检查学号是否唯一
    if check_unique_id "$id"; then
        echo "学号已存在，请检查后重新！"
        add_score
        return
    fi

    echo "请输入新添加学生的姓名："
    read name

    while true; do
        echo "请输入成绩（0-100）："
        read grade

        # 成绩是否在0-100内
        if [[ $grade -ge 0 && $grade -le 100 ]]; then
            break
        else
            echo "成绩应该在0到100之间，请重新输入。"
        fi
    done

    # 将信息追加到文件中
    echo -e "$id\t$name\t$grade" >> "$score_file"
    echo "新添加学生成绩信息已添加。"
}

# 删除学生成绩信息
delete_score() {
    echo "请输入要删除的学号："
    read delete_id

    grep -v "^$delete_id	" "$score_file" > "$score_file.tmp"
    mv "$score_file.tmp" "$score_file"

    echo "学号为 $delete_id 的学生的成绩信息已删除。"
}

# 查询学生成绩信息
query_score() {
    echo "请输入要查询的学号："
    read query_id

    result=$(grep "^$query_id	" "$score_file")

    if [ -z "$result" ]; then
        echo "未找到学号为 $query_id 的成绩信息。"
    else
        echo "查询结果：$result"
    fi
}

# 查询所有学生成绩信息
query_all_scores() {
    echo "所有学生成绩信息如下："
    cat "$score_file"
}

# 编辑学生成绩信息
edit_score() {
    echo "请输入要编辑的学号："
    read edit_id

    # 检查学号是否存在
    if ! check_unique_id "$edit_id"; then
        echo "学号不存在，请重新输入。"
        return
    fi

    echo "请选择要编辑的内容："
    echo "1. 编辑姓名"
    echo "2. 编辑成绩"

    read edit_choice

    case $edit_choice in
        1)
            echo "请输入新的姓名："
            read new_name
            # 更新学生姓名
            awk -v id="$edit_id" -v newName="$new_name" 'BEGIN {FS=OFS="\t"} $1 == id { $2 = newName } 1' "$score_file" > "$score_file.tmp"
            mv "$score_file.tmp" "$score_file"
            echo "姓名已更新。"
            ;;
        2)
            echo "请输入新的成绩（0-100）："
            read new_grade
            # 更新学生成绩
            awk -v id="$edit_id" -v newGrade="$new_grade" 'BEGIN {FS=OFS="\t"} $1 == id { $3 = newGrade } 1' "$score_file" > "$score_file.tmp"
            mv "$score_file.tmp" "$score_file"
            echo "成绩已更新。"
            ;;
        *)
            echo "无效的选项，请重新选择。"
            ;;
    esac
}


# 按成绩排序显示
sort_by_grade() {
    echo "请选择排序方式："
    echo "1. 升序"
    echo "2. 降序"

    read sort_choice

    case $sort_choice in
        1)
            echo "按照成绩升序排序后的学生成绩信息："
            sort -t$'\t' -k3,3n "$score_file"
            ;;
        2)
            echo "按照成绩降序排序后的学生成绩信息："
            sort -t$'\t' -k3,3nr "$score_file"
            ;;
        *)
            echo "无效的选项，请重新选择。"
            ;;
    esac
}

# 成绩统计
calculate_statistics() {
    total_count=$(wc -l < "$score_file")
    if [ "$total_count" -eq 0 ]; then
        echo "成绩单为空，无法统计。"
        return
    fi

    highest_grade=$(sort -t$'\t' -k3,3nr "$score_file" | head -n 1 | cut -f 3)
    lowest_grade=$(sort -t$'\t' -k3,3n "$score_file" | head -n 1 | cut -f 3)
    average_grade=$(awk -F'\t' '{ total += $3 } END { if (NR > 0) print total/NR }' "$score_file")

    echo "成绩统计信息："
    echo "总人数：$total_count"
    echo "最高成绩：$highest_grade"
    echo "最低成绩：$lowest_grade"
    echo "平均成绩：$average_grade"
}

# 主程序
while true; do
    echo "欢迎使用学生成绩管理系统！"
    echo "----------------2220222043"
    echo "请选择你要进行的操作："
    echo "a. 添加成绩信息"
    echo "b. 删除成绩信息"
    echo "c. 查询成绩信息"
    echo "d. 查询所有记录"
    echo "e. 编辑学生成绩信息"
    echo "f. 按成绩排序显示"
    echo "g. 成绩统计"
    echo "h. 退出程序"

    read -p "请选择(a-h): " choice

    case $choice in
        a)
            add_score
            ;;
        b)
            delete_score
            ;;
        c)
            query_score
            ;;
        d)
            query_all_scores
            ;;
        e)
            edit_score
            ;;
        f)
            sort_by_grade
            ;;
        g)
            calculate_statistics
            ;;
        h)
            echo "退出程序。"
            exit 0
            ;;
        *)
            echo "无效的选项，请重新选择。"
            ;;
    esac
done
