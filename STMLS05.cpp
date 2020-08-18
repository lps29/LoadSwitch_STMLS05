#include "STMLS05.hpp"

LoadSwitch_STMLS05::LoadSwitch_STMLS05()
{
}

uint8_t LoadSwitch_STMLS05::enable_load(channel_t channel_x)
{
    return set_register( STMLS05_CHANNEL_ENABLE, ( get_register(STMLS05_CHANNEL_ENABLE) | ( (uint8_t)0x01 << (uint8_t)channel_x )) );
}

uint8_t LoadSwitch_STMLS05::disable_load(channel_t channel_x)
{
    return set_register( STMLS05_CHANNEL_ENABLE, ( get_register(STMLS05_CHANNEL_ENABLE) & ~( (uint8_t)0x01 << (uint8_t)channel_x) ) );
}

uint8_t LoadSwitch_STMLS05::disable_discharge(channel_t channel_x)
{
    return set_register( (uint8_t)channel_x, get_register((uint8_t)channel_x) & ~BITM_CHANNELX_SETUP_DE  );
}

uint8_t LoadSwitch_STMLS05::enable_discharge(channel_t channel_x, discharge_t discharge_x)
{
    return set_register( (uint8_t)channel_x, (get_register((uint8_t)channel_x) | BITM_CHANNELX_SETUP_DE | (uint8_t)discharge_x)  );
}

uint8_t LoadSwitch_STMLS05::disable_soft_start(channel_t channel_x)
{
    return set_register( (uint8_t)channel_x, (get_register((uint8_t)channel_x) & ~BITM_CHANNELX_SETUP_SSD)  );
}

uint8_t LoadSwitch_STMLS05::enable_soft_start(channel_t channel_x, soft_start_t ss_xms)
{
    return set_register( (uint8_t)channel_x, ( (get_register((uint8_t)channel_x) & ~BITM_CHANNELX_SETUP_SS) | ((uint8_t)ss_xms << BITP_CHANNELX_SETUP_SS) ) | BITM_CHANNELX_SETUP_SSD );
}

uint8_t LoadSwitch_STMLS05::set_register(uint8_t reg_addr, uint8_t reg_value)
{
    Wire.beginTransmission(STMLS05_ADDR);
    I2C_WRITE(reg_addr);                     // set register pointer
    I2C_WRITE(reg_value);
    return Wire.endTransmission();
}

uint8_t LoadSwitch_STMLS05::get_register(uint8_t reg_addr)
{
    Wire.beginTransmission(STMLS05_ADDR);
    I2C_WRITE( reg_addr );                    // set register pointer
    Wire.endTransmission(false);
    Wire.requestFrom(STMLS05_ADDR, 1);        // request one byte from device
    while( Wire.available() == 0 );
    return I2C_READ();
}