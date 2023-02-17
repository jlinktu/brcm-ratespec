/*
* ISC License (ISC)
*
* Copyright 2023 Jakob Link <jlink@seemoo.de>
*
* Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include "rates.h"

void st16le(uint16_t value, uint16_t *addr)
{
    uint8_t *_addr = (uint8_t *)addr;
    _addr[0] = value & 0xff;
    _addr[1] = (value >> 8) & 0xff;
}

void st16be(uint16_t value, uint16_t *addr)
{
    uint8_t *_addr = (uint8_t *)addr;
    _addr[1] = value & 0xff;
    _addr[0] = (value >> 8) & 0xff;
}


void usage() 
{
    char *usage_str = "Print out VHT, HT and Legacy rate in Broadcom ratespec format.\n\nUsage: brcmrate [-h] [-b bandwidth] [-m mcs] [-n nss] [-l legacy Mbps]\n\n\tbandwidth:\t20(default), 40, or 80 (MHz)\n\tmcs:\t\tMCS index, see ieee 802.11 standard (HT and VHT only)\n\tnss:\t\tnumber of spatial streams (default 1, HT and VHT only)\n\tlegacy rates:\t6(default), 9, 12, 18, 24, 36, 48, or 54 (Mbps)\n";
    fprintf(stdout, "%s\n", usage_str);
}

int main(int argc, char *argv[])
{
    int c;
    int32_t bandwidth = 0;
    int32_t mcs = 0;
    int32_t nss = 1;
    int32_t legacy = 6 * 2;
    uint32_t rate = 0;
    uint32_t ratebw = RATES_BW_20MHZ;

    if(argc < 2) {
        usage();
        goto finish;
    }

    while ((c = getopt(argc, argv, "hb:m:n:l:")) != EOF) {
        switch (c) {
            case 'h':
                usage();
                goto finish;
            case 'b':
                bandwidth = atoi(optarg);
                break;
            case 'm':
                mcs = atoi(optarg);
                break;
            case 'n':
                nss = atoi(optarg);
                break;
            case 'l':
                legacy = atoi(optarg) * 2;
                break;
            default:
                fprintf(stderr, "Invalid option\n"); 
                goto finish_error;
        }
    }

    switch (bandwidth) {
        case 20:
            ratebw = RATES_BW_20MHZ;
            break;
        case 40:
            ratebw = RATES_BW_40MHZ;
            break;
        case 80:
            ratebw = RATES_BW_80MHZ;
            break;
        default:
            ratebw = RATES_BW_20MHZ;
            break;
    }

    printf("brcm ratespec\n");
    rate = ratebw | RATES_SET_VHT(mcs, nss);
    printf("vht:\t0x%04x\n", rate);
    rate = ratebw | RATES_SET_HT(mcs, nss);
    printf("ht:\t0x%04x\n", rate);
    rate = ratebw | RATES_OVERRIDE_RATE | RATES_OVERRIDE_MODE | legacy;
    printf("legacy:\t0x%04x\n", rate);

  finish:
    return 0;
  finish_error:
    return -1;
}
