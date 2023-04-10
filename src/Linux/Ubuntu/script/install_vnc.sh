#!/bin/bash
echo "==================================="
echo "install_vnc.sh"
echo "==================================="
cd `dirname $0`
# -----------------------------------------------
mkdir -p file
echo -e \
"[Unit]\n\
Description=TigerVNC (Remote access)\n\
After=syslog.target\n\
After=network.target remote-fs.target nss-lookup.target\n\
After=x11-common.service\n\
After=network-online.target\n\n\
[Service]\n\
Type=forking\n\
User=$USER\n\
ExecStart=/bin/sh -c 'sleep 10 && /usr/bin/x0vncserver -display :0 -rfbport 5900 -passwordfile /etc/tigervnc.passwd &'\n\
ExecStop=/bin/kill -TERM \$MAINPID\n\
ExecReload=/bin/kill -HUP \$MAINPID\n\
KillMode=control-group\n\
Restart=on-failure\n\n\
[Install]\n\
WantedBy=multi-user.target" > file/tigervnc.service

# -----------------------------------------------
sudo apt autoremove -y
sudo apt update
sudo apt upgrade -y
# -----------------------------------------------
sudo apt install -y tigervnc-common tigervnc-standalone-server tigervnc-scraping-server
sudo vncpasswd /etc/tigervnc.passwd
sudo chmod 644 /etc/tigervnc.passwd

# -----------------------------------------------
sudo cp file/tigervnc.service /lib/systemd/system/tigervnc.service
# firewall-cmd --add-service=vnc-server
# firewall-cmd --runtime-to-permanent

sudo systemctl daemon-reload
#sudo systemctl list-unit-files --type=service | grep tigervnc
sudo systemctl enable tigervnc
sudo systemctl start tigervnc
# -----------------------------------------------
sudo systemctl status tigervnc
# sudo systemctl disable tigervnc
# sudo systemctl start tigervnc
# sudo systemctl restart tigervnc
# sudo systemctl stop tigervnc
