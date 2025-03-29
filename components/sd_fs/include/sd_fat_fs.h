/* SD card and FAT filesystem example.
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

// This example uses SDMMC peripheral to communicate with SD card.

#ifndef _SD_FAT_FS_H_
#define _SD_FAT_FS_H_

#include "sdmmc_cmd.h"

void fat_fs(void);

// sdmmc_card_t* return_sdmmc_card_t (const sdmmc_card_t* card);
// void MyTinyUSB_TEST(sdmmc_card_t *card);



#endif // _SD_FAT_FS_H_
