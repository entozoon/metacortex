# BS811X_I2C
An Arduino IDE based library used for BS811X series touch key I2C communication.\
Compatible with Holtek BS8116/BS8112 touch key chips which use I2C port to send touch key status.\
BS81X serial library see [this](https://github.com/snowhalationmkii/TTP229_BS81X_Serial).

## Instruction
<img src="https://p.sda1.dev/22/f76c19cdd6ce67ed42ffd01f1fcd1108/bs81162.jpg">\
BS811X series use a two wire I2C port to send touch status.In above picture, they are PIN `17/18` (for 8116) or `13/14` (for 8112)\
First you should connect chip I2C port to Arduino I2C port.\
<img src="https://docs.arduino.cc/static/5f90596512320d9577cfa9638fdb6115/a6d36/wiring.png">\
In this project I made a little evaluation pcb board like this.\
It can pinout the chip and you can easily connect and touch pins.\
<img src="https://p.sda1.dev/22/6218041ae19225e7db8a5dd80f6f0a67/bs81163.jpg">\
Then you shall open the `examples/bs811x_read.ino`, Upload it, Check serail port monitor

## Method
- `uint16_t readKeys();`\
Read data from BS811X. Should call before processing data.
Return status of 16 keys in bitmap representation
- `bool readSetting(uint8_t * array);`\
Read setting Register from BS811X. 
Return true if the reading is accomplished.
put `21/17` bytes register data into the array
- `uint8_t setSetting();`\
Write to the setting register in BS811X. 
Return endTransmission param.
predefined in "_settings"
- `uint8_t getKey_active();`\
Return number of first pressed key.
return `0` if none key is pressed
- `bool getKey_passive(uint8_t key);`\
Return true if a key is pressed.
param key Number of a key
- `bool getKey_edge(uint8_t direction, uint8_t key) ;`\
Return true if a edge is detected.
param edge direction `1/2` ( rising|falling ), key Number of a key
- `bool begin(String chip);`\
Return true if the initialize process has been a success.
param chip type `"8116"/"8112"`

## Setting
BS811X setting is very different from TTP229. It's through writing to the setting register of BS811X.\
By default，KEY `16|12` are used for `IRQ`.So you should change the setting for  `Key Mode` to enable all  `16|12` touch keys.\
However, this operation has already been included in the method `begin` so you may need to do nothing about that.\
<img src="https://p.sda1.dev/22/347373bb7b4b73f693a3d7355c450031/bs81164.jpg">\
If you want to have your own settings, you may check this table.

## Reference
The implementation of some methods make a reference from [Alexander Kiryanenko](https://github.com/kiryanenko/TTP229).

## License
Distributed under the [MIT](https://opensource.org/license/mit) License. See LICENSE for more information.
