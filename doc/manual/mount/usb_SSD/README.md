## usb diskのMountPointを指定する方法

1. 対象のデバイスを接続
1. コマンド:[```lsblk```]を使い、マウントされているデバイスパスを確認
1. コマンド:[```blkid```]を使い、先ほど調べたデバイスの**UUID**と**type**をメモする
1. ファイル「```/etc/fstab```」に下記のように**UUID**と**デバイスパス**、**type**を指定する

```text
#UUID=<調べたUUID>      <指定したいパス>    <blkidで表示されたtype>   defaults        0 0
UUID=FE68C3EE68C3A42D       /mnt/ssd    ntfs   defaults        0 0
```
