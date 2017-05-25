echo "-------------------------------"
cat commit_message.txt
echo "-------------------------------"
echo "commit message ok ?"
read
git commit --file=commit_message.txt
echo "press key"
read
