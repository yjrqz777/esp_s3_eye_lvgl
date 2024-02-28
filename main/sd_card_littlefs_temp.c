/* SD card and FAT filesystem example.
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

// This example uses SDMMC peripheral to communicate with SD card.

#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "driver/sdmmc_host.h"

static const char *TAG = "example";

#define MOUNT_POINT "/sdcard"

#include "esp_littlefs.h"

// ...

// esp_err_t init_littlefs() {
//     esp_littlefs_config_t config = {
//         .base_path = "/lfs",
//         .partition_label = NULL,
//         .format_if_mount_failed = true
//     };

//     esp_err_t ret = esp_littlefs_mount(&config);
//     if (ret != ESP_OK) {
//         return ret;
//     }

//     return ESP_OK;
// }


void app_main(void)
{
    esp_err_t ret;

    // Options for mounting the filesystem.
    // If format_if_mount_failed is set to true, SD card will be partitioned and
    // formatted in case when mounting fails.
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
#ifdef CONFIG_EXAMPLE_FORMAT_IF_MOUNT_FAILED
        .format_if_mount_failed = true,
#else
        .format_if_mount_failed = false,
#endif // EXAMPLE_FORMAT_IF_MOUNT_FAILED
        .max_files = 5,
        .allocation_unit_size = 16 * 1024
    };
    sdmmc_card_t card;
    const char mount_point[] = MOUNT_POINT;
    ESP_LOGI(TAG, "Initializing SD card");
    // Use settings defined above to initialize SD card and mount FAT filesystem.
    // Note: esp_vfs_fat_sdmmc/sdspi_mount is all-in-one convenience functions.
    // Please check its source code and implement error recovery when developing
    // production applications.

    ESP_LOGI(TAG, "Using SDMMC peripheral");
    sdmmc_host_t host = SDMMC_HOST_DEFAULT();

    // This initializes the slot without card detect (CD) and write protect (WP) signals.
    // Modify slot_config.gpio_cd and slot_config.gpio_wp if your board has these signals.
    sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();

    // Set bus width to use:
#ifdef CONFIG_EXAMPLE_SDMMC_BUS_WIDTH_4
    slot_config.width = 4;
#else
    slot_config.width = 1;
#endif

    // On chips where the GPIOs used for SD card can be configured, set them in
    // the slot_config structure:
#ifdef CONFIG_SOC_SDMMC_USE_GPIO_MATRIX
    slot_config.clk = CONFIG_EXAMPLE_PIN_CLK;
    slot_config.cmd = CONFIG_EXAMPLE_PIN_CMD;
    slot_config.d0 = CONFIG_EXAMPLE_PIN_D0;
#ifdef CONFIG_EXAMPLE_SDMMC_BUS_WIDTH_4
    slot_config.d1 = CONFIG_EXAMPLE_PIN_D1;
    slot_config.d2 = CONFIG_EXAMPLE_PIN_D2;
    slot_config.d3 = CONFIG_EXAMPLE_PIN_D3;
#endif  // CONFIG_EXAMPLE_SDMMC_BUS_WIDTH_4
#endif  // CONFIG_SOC_SDMMC_USE_GPIO_MATRIX

    // Enable internal pullups on enabled pins. The internal pullups
    // are insufficient however, please make sure 10k external pullups are
    // connected on the bus. This is for debug / example purpose only.
    slot_config.flags |= SDMMC_SLOT_FLAG_INTERNAL_PULLUP;

    ESP_LOGI(TAG, "Mounting filesystem");
 
    host.max_freq_khz = SDMMC_FREQ_DEFAULT;
    sdmmc_host_init();
    ret = sdmmc_host_init_slot(SDMMC_HOST_SLOT_1, &slot_config);
    
    ret = sdmmc_card_init(&host, &card);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "sdmmc_card_init Failed");
    }

    // sdmmc_host_t host = {0};



    card.host = host;
        ESP_LOGI(TAG, "Initializing LittleFS");

        esp_vfs_littlefs_conf_t conf = {
            .sdcard = &card,
            .base_path = "/littlefs",
            .partition_label = "littlefs",
            .format_if_mount_failed = true,
            .dont_mount = false,
        };

        // Use settings defined above to initialize and mount LittleFS filesystem.
        // Note: esp_vfs_littlefs_register is an all-in-one convenience function.
        // ret = esp_vfs_littlefs_register(&conf);

        // if (ret != ESP_OK)
        // {
        //         if (ret == ESP_FAIL)
        //         {
        //                 ESP_LOGE(TAG, "Failed to mount or format filesystem");
        //         }
        //         else if (ret == ESP_ERR_NOT_FOUND)
        //         {
        //                 ESP_LOGE(TAG, "Failed to find LittleFS partition");
        //         }
        //         else
        //         {
        //                 ESP_LOGE(TAG, "Failed to initialize LittleFS (%s)", esp_err_to_name(ret));
        //         }
        //         return;
        // }

        // size_t total = 0, used = 0;
        // ret = esp_littlefs_info(conf.partition_label, &total, &used);
        // if (ret != ESP_OK)
        // {
        //         ESP_LOGE(TAG, "Failed to get LittleFS partition information (%s)", esp_err_to_name(ret));
        // }
        // else
        // {
        //         ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
        // }

        // // Use POSIX and C standard library functions to work with files.
        // // First create a file.
        // ESP_LOGI(TAG, "Opening file");

        // FILE *f = fopen("/littlefs/hello.txt", "w");
        // if (f == NULL)
        // {
        //         ESP_LOGE(TAG, "Failed to open file for writing");
        //         return;
        // }
    // ret = esp_vfs_fat_sdmmc_mount(mount_point, &host, &slot_config, &mount_config, &card);

    // if (ret != ESP_OK) {
    //     if (ret == ESP_FAIL) {
    //         ESP_LOGE(TAG, "Failed to mount filesystem. "
    //                  "If you want the card to be formatted, set the EXAMPLE_FORMAT_IF_MOUNT_FAILED menuconfig option.");
    //     } else {
    //         ESP_LOGE(TAG, "Failed to initialize the card (%s). "
    //                  "Make sure SD card lines have pull-up resistors in place.", esp_err_to_name(ret));
    //     }
    //     return;
    // }
    // ESP_LOGI(TAG, "Filesystem mounted");

    // // Card has been initialized, print its properties
    // sdmmc_card_print_info(stdout, card);

    // Use POSIX and C standard library functions to work with files:

    // First create a file.
    // const char *file_hello = MOUNT_POINT"/hello.txt";

    // ESP_LOGI(TAG, "Opening file %s", file_hello);
    // FILE *f = fopen(file_hello, "w");
    // if (f == NULL) {
    //     ESP_LOGE(TAG, "Failed to open file for writing");
    //     return;
    // }
    // fprintf(f, "Hello %s!\n", card->cid.name);
    // fclose(f);
    // ESP_LOGI(TAG, "File written");

    // const char *file_foo = MOUNT_POINT"/foo.txt";

    // // Check if destination file exists before renaming
    // struct stat st;
    // if (stat(file_foo, &st) == 0) {
    //     // Delete it if it exists
    //     unlink(file_foo);
    // }

    // // Rename original file
    // ESP_LOGI(TAG, "Renaming file %s to %s", file_hello, file_foo);
    // if (rename(file_hello, file_foo) != 0) {
    //     ESP_LOGE(TAG, "Rename failed");
    //     return;
    // }

    // // Open renamed file for reading
    // ESP_LOGI(TAG, "Reading file %s", file_foo);
    // f = fopen(file_foo, "r");
    // if (f == NULL) {
    //     ESP_LOGE(TAG, "Failed to open file for reading");
    //     return;
    // }

    // // Read a line from file
    // char line[64];
    // fgets(line, sizeof(line), f);
    // fclose(f);

    // // Strip newline
    // char *pos = strchr(line, '\n');
    // if (pos) {
    //     *pos = '\0';
    // }
    // ESP_LOGI(TAG, "Read from file: '%s'", line);

    // // All done, unmount partition and disable SDMMC peripheral
    // esp_vfs_fat_sdcard_unmount(mount_point, card);
    ESP_LOGI(TAG, "Card unmounted");
}
