# mcs_encode_string_example

## Usage

* copy `config/project/mt7687_hdk/mcs_encode_string` to your `{SDK_Root}/config/project/mt7687_hdk/`

* copy `project/mt7687_hdk/apps/mcs_encode_string` to your `{SDK_Root}/config/project/mt7687_hdk/mcs_encode_string`

* build code, on your SDK_Root : `./build.sh mt7687_hdk iot_sdk`

* Burn .bin to your 7687 device.

* Open your debug window, and type this:

``` bash

nvram set STA Ssid mcs
nvram set STA Password 12345678
nvram set common deviceId 123123123
nvram set common deviceKey 456456456


# mcs is your wifi ssid
# 12345678 is your wifi password
# 123123123 is your mcs deviceId
# 456456456 is your mcs deviceKey

```
* Reboot 7687

* If you want to disabale/enable smart connection feature, go to `{SDK_Root}/mt7687_hdk/apps/mcs_encode_string/GCC/feature.mk` and change the `MTK_SMARTCONNECT_HDK = y` line.

## SDK version

* 3.1.0
