@echo "enable wifi"

adb devices

adb shell "echo "1" > /sys/devices/platform/msm_sdcc.3/polling"

adb shell insmod /system/lib/modules/dhd.ko firmware_path=/system/etc/firmware/wlan/sdio_cit.bin nvram_path=/system/etc/firmware/wlan/nvram.txt

adb shell ifconfig wlan0 up

adb shell cd /system/bin/
