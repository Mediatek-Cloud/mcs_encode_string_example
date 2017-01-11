# mcs_encode_string_example

## Usage

* copy `mcs_encode_string` to your `{SDK_Root}/project/mt7687_hdk/apps/mcs_encode_string`

* Edit the `{SDK_Root}/project/mt7687_hdk/apps/mcs_encode_string/inc/mcs.h`:

```
#define deviceId "Input your deviceId"
#define deviceKey "Input your deviceKey"
#define host "com"

```

* Edit the `{SDK_Root}/project/mt7687_hdk/apps/mcs_encode_string/src/main.c`:

```
// find line 56
#define SSID "Input your wifi ssid"
#define PASSWORD "Input your wifi password"

// find line 65
#define ENCODE_MD5_CHANNEL "encodeByMD5"
#define DECODE_MD5_CHANNEL "decodeByMD5"

```

* build code, on your SDK_Root : `./build.sh mt7687_hdk mcs_encode_string bl`

* Use flash tool to download `flash_download.ini` & `mt7687_bootloader.bin` & `mcs_pwm.bin` & `WIFI_RAM_CODE_MT76X7_in_flash.bin` to your 7687 device. (These files will see in the `{SDK_Root}/out/mt7687_hdk/mcs_pwm` path)

## SDK version

* 4.1.0