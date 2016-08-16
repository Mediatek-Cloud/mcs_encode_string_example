# mcs_encode_string_example

## Usage

* copy `mcs_encode_string` to your `{SDK_Root}/project/mt7687_hdk/apps/mcs_encode_string`

* Edit the `{SDK_Root}/project/mt7687_hdk/apps/mcs_encode_string/main.c`:

```
#define deviceId "Input your deviceId"
#define deviceKey "Input your deviceKey"
#define Ssid "Input your wifi"
#define Password "Input your password"
#define host "com"

```

* build code, on your SDK_Root : `./build.sh mt7687_hdk mcs_encode_string`

* Burn .bin to your 7687 device.

## SDK version

* [3.3.1](https://cdn.mediatek.com/download_page/index.html?platform=RTOS&version=v3.3.1&filename=LinkIt_SDK_V3.3.1_public.tar.gz)