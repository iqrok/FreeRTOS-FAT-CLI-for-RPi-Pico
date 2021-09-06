/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
 */

#ifndef _SD_CARD_H_
#define _SD_CARD_H_

#include <stdint.h>

#include "FreeRTOS.h"
/* FreeRTOS includes. */
#include <semphr.h>
//
#include "hardware/gpio.h"
//
#include "ff_headers.h"
#include "spi.h"

#ifdef __cplusplus
extern "C" {
#endif

// "Class" representing SD Cards
typedef struct {
    const char *pcName;
    spi_t *const spi;
    // Slave select is here in sd_card_t because multiple SDs can share an SPI
    uint ss_gpio;                   // Slave select for pSD SD card
    const uint card_detect_gpio;    // Card detect
    const uint card_detected_true;  // Varies with card socket
    const gpio_irq_callback_t card_detect_callback;  // Port Interrupt callback
    //TaskHandle_t card_detect_task;                   // handles card detect ISRs
    int m_Status;                                    // Card status
    uint64_t sectors;                                // Assigned dynamically
    int card_type;                                   // Assigned dynamically
    SemaphoreHandle_t mutex;  // Guard semaphore, assigned dynamically
    size_t ff_disk_count;
    FF_Disk_t **ff_disks;  // FreeRTOS+FAT "disks" using pSD device
} sd_card_t;

#define SD_BLOCK_DEVICE_ERROR_NONE 0
#define SD_BLOCK_DEVICE_ERROR_WOULD_BLOCK -5001 /*!< operation would block */
#define SD_BLOCK_DEVICE_ERROR_UNSUPPORTED -5002 /*!< unsupported operation */
#define SD_BLOCK_DEVICE_ERROR_PARAMETER -5003   /*!< invalid parameter */
#define SD_BLOCK_DEVICE_ERROR_NO_INIT -5004     /*!< uninitialized */
#define SD_BLOCK_DEVICE_ERROR_NO_DEVICE \
    -5005 /*!< device is missing or not connected */
#define SD_BLOCK_DEVICE_ERROR_WRITE_PROTECTED -5006 /*!< write protected */
#define SD_BLOCK_DEVICE_ERROR_UNUSABLE -5007        /*!< unusable card */
#define SD_BLOCK_DEVICE_ERROR_NO_RESPONSE                              \
    -5008                                 /*!< No response from device \
                                           */
#define SD_BLOCK_DEVICE_ERROR_CRC -5009   /*!< CRC error */
#define SD_BLOCK_DEVICE_ERROR_ERASE -5010 /*!< Erase error: reset/sequence */
#define SD_BLOCK_DEVICE_ERROR_WRITE \
    -5011 /*!< SPI Write error: !SPI_DATA_ACCEPTED */

/* Disk Status Bits (DSTATUS) */
enum {
    STA_NOINIT = 0x01, /* Drive not initialized */
    STA_NODISK = 0x02, /* No medium in the drive */
    STA_PROTECT = 0x04 /* Write protected */
};

bool sd_init_driver();
int sd_init_card(sd_card_t *pSD);
int sd_card_deinit(sd_card_t *pSD);
int sd_write_blocks(sd_card_t *pSD, const uint8_t *buffer,
                    uint64_t ulSectorNumber, uint32_t blockCnt);
int sd_read_blocks(sd_card_t *pSD, uint8_t *buffer, uint64_t ulSectorNumber,
                   uint32_t ulSectorCount);
bool sd_card_detect(sd_card_t *pSD);
uint64_t sd_sectors(sd_card_t *pSD);

#ifdef __cplusplus
}
#endif

#endif
/* [] END OF FILE */
