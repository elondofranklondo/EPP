##!/usr/bin/env bash
cd "/home/franklondo/Desktop/EBgit/src"
cp -r "/home/franklondo/eclipse/WorkSpace/EPP/src" "/home/franklondo/Desktop/EBgit/"

mesID=' commit'
dt=$(date '+%M-%H-%d-%m-%y')
message=$dt$mesID

git checkout master
git add "$(*.cpp|*.h)"
git commit -a -m "$message"
/usr/bin/expect << EOF
set timeout 5
spawn git push origin master
expect "Username for 'https://github.com': "
send -- "elondofranklondo\r"	
expect "Password for 'https://elondofranklondo@github.com': "
send -- "Boobies!22\r"
expect eof
EOF
echo "pushed successfully"

