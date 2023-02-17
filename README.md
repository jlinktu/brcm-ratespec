# brcm-ratespec
Print Broadcom Wi-Fi firmware ratespec from bandwidth, MCS index, and number of spatial streams or legacy rate.

#### Usage
```
Usage: brcmrate [-h] [-b bandwidth] [-m mcs] [-n nss] [-l legacy Mbps]

        bandwidth:      20(default), 40, or 80 (MHz)
        mcs:            MCS index, see ieee 802.11 standard (HT and VHT only)
        nss:            number of spatial streams (default 1, HT and VHT only)
        legacy rates:   6(default), 9, 12, 18, 24, 36, 48, or 54 (Mbps)
```

#### Example
```
$ ./brcmrate -b 80 -m 3 -n 4 -l 36
brcm ratespec
vht:    0xc2030043
ht:     0xc1030023
legacy: 0xc0030048
```
