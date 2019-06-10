if [[ -z $1 ]]; then
	RADIUS=2
else
	RADIUS=$1
fi

if [[ -z $2 ]]; then
	DEPTH=5
else
	DEPTH=$2
fi

if [[ -z $3 ]]; then
	SAMPLES=1
else 
	SAMPLES=$3
fi

echo "radius is $RADIUS"
echo "depth is $DEPTH"
echo "samples is $SAMPLES"

./program $RADIUS $DEPTH $SAMPLES
xdg-open ray-trace.bmp
