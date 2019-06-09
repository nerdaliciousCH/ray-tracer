if [[ -z $1 ]]; then
	RADIUS=1
else
	RADIUS=$1
fi
echo "radius is $RADIUS"
./program $RADIUS
xdg-open ray-trace.bmp
