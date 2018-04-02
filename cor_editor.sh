if [ -z "$1" ]; then
	echo "Usage:\n./cor_editor.sh [.cor file]"
	exit
fi
xxd $1 > ./temp.txt
vi ./temp.txt
xxd -r ./temp.txt > $1.invalid
rm ./temp.txt
