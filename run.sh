if [[ -z $1 ]]; then
	SIZE_FACTOR=4
else
	SIZE_FACTOR=$1
fi
rm ray-trace.bmp
make
./program 16 $SIZE_FACTOR
xdg-open ray-trace.bmp
