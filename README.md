# RC Car
## Thomas Knickerbocker
### For: MPLABX IDE

## Files: 
- newxc8_header: contains macros including pin#s for peripherals
- car: Contains up PWM, light, and motor control for the vehicle
- I2C: Sets up & communicates via I2C with joystick & LCD display
- rtc: sets up periodic interrupts
- printing: print statements that output via putty & xquartz when the project is run (utilizes USART2)

## Design Pictures:
![Pictures of RC Car](./img/Aerial_View.jpg.png "Aerial View")
![Pictures of RC Car](./img/Side_View.jpg.png "Side View")
![Pictures of RC Car](./img/Controller_View.jpg.png "Controller View")
![Pictures of RC Car](./img/Underneath_View.jpg.png "Underneath View")

## Parts List:

| Part Model name | Manufacturer | PowerReq | Vendor | Link | Quantity | Price (circa May 2024) | Notes |
|-----------------|--------------|----------|--------|------|----------|------------------------|-------|
| AVR-BLE DEVELOPMENT BOARD | Microchip | 3.3v | Microchip | [Link](https://www.microchip.com/en-us/development-tool/dt100111) | 1 | $45 | Completely Replacable |
| 110090263 | Seeed Technology Co., Ltd | 3.3v-12v | Digikey | [Link](https://www.digikey.com/en/products/detail/seeed-technology-co-ltd/110090263/10290284) | 1 | $7.68 | Can always 3D print an encasing on top of this |
| FIT0096 | DFRobot | 5V | Digikey | [Link](https://www.digikey.com/en/products/detail/dfrobot/FIT0096/7597069) | 2 | $5.80 | Just a breadboard. Second one not necessary, only recommended. |
| SparkFun Qwiic Joystick | SparkFun | 3.3v | SparkFun | [Link](https://www.sparkfun.com/products/15168) | 1 | $11.50 | Overpriced. Can be replaced w/ buttons or BLE |
| PART 4 DIGIT 7 SEGMENT DISPLAY | Gearbox Labs | 3.3v | Digikey | [Link](https://www.digikey.com/en/products/detail/gearbox-labs/PART-4-DIGIT-7-SEGMENT-DISPLAY/16161106) | 1 | $1.50 | Great part, great deal |
| DRV8835 Dual Motor Driver Carrier | Polulu | 0-11v | Polulu | [Link](https://www.pololu.com/product/2135) | 2 | ~$10.00 |  |
| Through-Hole Speaker | Digikey | Max 0.5W | - | [Link](https://www.sparkfun.com/products/20660) | 1 | $2.95 |  |
| Minidodoca arduino Power Supply 3.3V 5V MB102 Solderless Breadboard Power Supply Module with 9V Battery Clip +4pcs Alligator Clip Test Lead+25pcs 5 Colors LED+12pcs 0.22-470uf capacitors+ Dupont 3pcs Power Supply Module kit | Minidodoca | 5v | Amazon | [Link](https://shorturl.at/lqKW8) | 1 | $9.99 | Overkill; All we’re really looking for here is a power supply, cables, and some LEDs |


