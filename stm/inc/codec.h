#include "stm32h7xx_hal.h"


/**************************************************************************************************
* WM8731 sound chip register addresses
**************************************************************************************************/
#define WM8731_ADDRESS              0x34       // WM8731 chip address on I2C bus
#define WM8731_REG_LLINE_IN         0x00       // Left Channel Line Input Volume Control
#define WM8731_REG_RLINE_IN         0x01       // Right Channel Line Input Volume Control
#define WM8731_REG_LHPHONE_OUT      0x02       // Left Channel Headphone Output Volume Control
#define WM8731_REG_RHPHONE_OUT      0x03       // Right Channel Headphone Output Volume Control
#define WM8731_REG_ANALOG_PATH      0x04       // Analog Audio Path Control
#define WM8731_REG_DIGITAL_PATH     0x05      // Digital Audio Path Control
#define WM8731_REG_PDOWN_CTRL       0x06       // Power Down Control Register
#define WM8731_REG_DIGITAL_IF       0x07       // Digital Audio Interface Format
#define WM8731_REG_SAMPLING_CTRL    0x08       // Sampling Control Register
#define WM8731_REG_ACTIVE_CTRL      0x09       // Active Control
#define WM8731_REG_RESET            0x0F       // Reset register

/**************************************************************************************************
* WM8731 sound chip constants (for default set up)
**************************************************************************************************/
#define WM8731_left_lineIn         0x0180     // Mic settings: Enable mute, Enable simultaneous load to left and right channels
#define WM8731_Right_lineIn        0x0180     // Mic settings: Enable mute, Enable simultaneous load to left and right channels
#define WM8731_Left_hp             0x01F0     // Headphone settings : -9dB output
#define WM8731_Right_hp            0x01F0     // Headphone settings : -9dB output
#define WM8731_AnalogAudio         0xD0       // DAC Select
#define WM8731_DigitalAudio        0x06
#define WM8731_power               0x00       // Disable Power down
#define WM8731_DAIF                0x43       // Enable Master Mode and 32bit data
#define WM8731_Sampling            0x23       // 44100Hz
#define WM8731_Activate            0x01       // Module is ON
#define WM8731_Deactivate          0x00       // Module is OFF
#define WM8731_Reset               0x00       // Reset value

enum CODEC_INPUT_INTERFACE {UNKNOWN, MODE_JACK_IN, MODE_LINE_IN};

#define GAIN_OUT_DECREMENT_VALUE	3
#define GAIN_OUT_MAX_VALUE			6
#define GAIN_OUT_MIN_VALUE			-6
#define GAIN_OUT_NUMBER_OF_STEPS    5

#define GAIN_LINE_IN_DECREMENT_VALUE	3
#define GAIN_LINE_IN_MAX_VALUE			12
#define GAIN_LINE_IN_MIN_VALUE			0
#define GAIN_LINE_IN_NUMBER_OF_STEPS    5

void codec_init(int mode);
void codec_send_cmd(uint16_t address, uint16_t cmd);
void codec_set_20db_mic_boost(uint8_t enable);
void codec_set_line_in_gain(int8_t gain);
void codec_set_out_gain(int8_t gain);
