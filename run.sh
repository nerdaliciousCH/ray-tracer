if [[ -z $1 ]]; then
	THREADS=16
else
	THREADS=$1
fi

./program $THREADS
xdg-open ray-trace.bmp
