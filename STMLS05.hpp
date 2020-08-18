#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#include <Wire.h>
// STMLS05 I2C HAL
#define I2C_READ  Wire.read  
#define I2C_WRITE Wire.write
#endif

#define STMLS05_ADDR 0x2E

// STMLS05 register definitions
#define STMLS05_CHANNEL0_SETUP (uint8_t)0x00  // settings for channel 0
#define STMLS05_CHANNEL1_SETUP (uint8_t)0x01  // settings for channel 1
#define STMLS05_CHANNEL2_SETUP (uint8_t)0x02  // settings for channel 2
#define STMLS05_CHANNEL3_SETUP (uint8_t)0x03  // settings for channel 3
#define STMLS05_CHANNEL4_SETUP (uint8_t)0x04  // settings for channel 4
#define STMLS05_CHANNEL_ENABLE (uint8_t)0x05  // channel enable/disable 

// STMLS05 soft-start (SS) bit mask (BITM) and bit position (BITP)
#define BITM_CHANNELX_SETUP_SS (uint8_t)0x07
#define BITP_CHANNELX_SETUP_SS (uint8_t)0x00

// STMLS05 soft-start disable (SSD) bit mask (BITM)
#define BITM_CHANNELX_SETUP_SSD (uint8_t)0x04

// STMLS05 discharge enable (DE) bit mask (BITM)
#define BITM_CHANNELX_SETUP_DE (uint8_t)0x08

// STMLS05 discharge type (DT) bit mask (BITM)
#define BITM_CHANNELX_SETUP_DT (uint8_t)0x10

// STMLS05 has 5 independent channels. 
typedef enum
{
    CHANNEL_0 = 0x00,
    CHANNEL_1 = 0x01,
    CHANNEL_2 = 0x02,
    CHANNEL_3 = 0x03,
    CHANNEL_4 = 0x04    
} channel_t;

// Discharge type for internal discharge circuit when channel is disabled 
typedef enum
{
    DISCHARGE_SHORT     = 0x00,   // discharge for 1.7 ms (t_dis) when channel x is disabled 
    DISCHARGE_PERMANENT = 0x01    // permanent discharge when channel x is disabled  
} discharge_t;

// Soft-start options
typedef enum
{
    SS_1MS = 0x00,  // 1ms soft-start 
    SS_2MS = 0x01,  // 2ms soft-start
    SS_4MS = 0x02,  // 3ms soft-start
    SS_8MS = 0x03   // 4ms soft-start
} soft_start_t;

class LoadSwitch_STMLS05
{
public:
    LoadSwitch_STMLS05();
    uint8_t enable_load(channel_t channel_x);
    uint8_t disable_load(channel_t channel_x);
    
    uint8_t disable_discharge(channel_t channel_x);
    uint8_t enable_discharge(channel_t channel_x, discharge_t discharge_x);
    
    uint8_t disable_soft_start(channel_t channel_x);
    uint8_t enable_soft_start(channel_t channel_x, soft_start_t ss_xms);
    
    uint8_t get_register(uint8_t reg_addr); 
    uint8_t set_register(uint8_t reg_addr, uint8_t reg_value);
};