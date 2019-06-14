if [[ -z $1 ]]; then
	THREADS=16
else
	THREADS=$1
fi

if [[ -z $2 ]]; then
	SIZE_FACTOR=4
else
	SIZE_FACTOR=$2
fi
rm ray-trace.bmp
make
./program $THREADS $SIZE_FACTOR
xdg-open ray-trace.bmp
