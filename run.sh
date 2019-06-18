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

if [[ -z $3 ]]; then
	RANDOM_SAMPLES=10
else
	RANDOM_SAMPLES=$3
fi
rm ray-trace.bmp
make
./program $THREADS $SIZE_FACTOR $RANDOM_SAMPLES
xdg-open ray-trace.bmp
