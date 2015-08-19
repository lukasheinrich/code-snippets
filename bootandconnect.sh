#!/bin/zsh
image=$1
queue=$2
hostname=$3

tmpfile=$(mktemp)
cat << EOFOUT > $tmpfile
#!/bin/sh
cd /home/analysis
cat << EOF > user_data.sh
#!/bin/zsh
export RECASTQUEUE=$queue
export RECASTPLUGINDIR=plugin_home
export RECAST_SHIP_USER=$(whoami)
export RECAST_SHIP_HOST=localhost
export RECAST_SHIP_PORT=2022
EOF
chown analysis:analysis user_data.sh
EOFOUT

echo "::::wrote user_data to $tmpfile"

nova boot --image $image --flavor m1.large --key_name openstack --poll --user_data $tmpfile $hostname 

if [[ "$(nova show $hostname|awk '/status/{print $4}')" != "ACTIVE" ]];then
  echo "apparently ERROR in booting instance. exit."
  exit 1
fi

#sleep a bit to let ssh come up
sleep 60

echo "done booting up $hostname. connecting."
./connect.sh $hostname

echo "connected!"   
