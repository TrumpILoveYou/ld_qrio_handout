channel_d=2
qemu_pid=$(ps -ef | grep qemu | grep "channel $channel_d" | grep -v grep | awk '{printf "%s ", $2}' )
if [ "$qemu_pid" == "" ]
then
	echo "qemu already closed"
else
	echo $qemu_pid
	kill -9 $qemu_pid
fi

rio_pid=$(ps -ef | grep rio | grep "channel $channel_d" | grep -v grep | awk '{printf "%s ", $2}' )
if [ "$rio_pid" == "" ]
then
	echo "rio already closed"
else
	echo $rio_pid
	kill -9 $rio_pid
fi
rm -rf $HOME/qr/$channel_d
