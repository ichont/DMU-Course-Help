#!bin/sh
rm -rf temp
cat linux2021Spring/20210422* | awk '{print $1}' |grep 'stu' | sort -n |uniq >> temp
cat linux2021Spring/20210429* | awk '{print $1}' |grep 'stu' | sort -n |uniq >> temp
cat linux2021Spring/20210506* | awk '{print $1}' |grep 'stu' | sort -n |uniq >> temp
cat linux2021Spring/20210513* | awk '{print $1}' |grep 'stu' | sort -n |uniq >> temp
cat linux2021Spring/20210520* | awk '{print $1}' |grep 'stu' | sort -n |uniq >> temp
cat linux2021Spring/20210527* | awk '{print $1}' |grep 'stu' | sort -n |uniq >> temp
cat linux2021Spring/20210603* | awk '{print $1}' |grep 'stu' | sort -n |uniq >> temp
for tag in $(cat temp | sort -n | uniq)
do
	num=$(grep -c $tag temp)
	echo "$tag:$num"
done
echo "stu1195:$(grep -c stu1195 temp)"
rm -rf temp
exit 0
