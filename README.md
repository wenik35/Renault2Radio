# Why?
My 2003 Renault Laguna had a TunerList head unit which only supported Radio and CD. I rather like listening to whatever bullshit comes to mind on Spotify, so i bought a cheap replacement from Amazon wich supports Bluetooth Connection, but cant interface with the original steering wheel controls. 

# What?
This project aims to build a bridge between the car and radio and maybe incorporate some more functionality further down the line. Right now, it only receives button presses via Renaults TunerList protocol and translates those to IR signals the new head unit can understand.

This repository also includes code that should theoretically be able to write to the display, at least it worked solo in Arduino IDE. However, I haven't tried it yet via PIO and so it is not implemented in the main loop.

# How?
TunerList is a custom I2C protocol used by Renault in the early 2000s to connect the head unit to the steering wheel controls and display. The head unit acts as an I2C master and periodically (~0.5s) polls the display for button presses via a Master Request (MRQ) signal. When a button is pressed, the display responds with a specific header and status byte that indicates which button was pressed. For this all to work, the radio needs to get 12V via the Radio On line, otherwise the display won't send any MRQ signals.

TunerList uses a 5V logic level on the data lines, so i'm using an Arduino Nano to listen for these MRQ signals and read the button presses. Since the new head unit came with a (rather shit) IR Remote, its fairly simple to provide input via an optocoupler. Theoretically you could also just use an IR LED, but it wanted all of the electronics to be contained in/behind the radio and not have some weird stuff poking out front.

## Protocols
### TunerList Buttons
- 0x04	0x82	0x91	0x00	0x03	Volume up press
- 0x04	0x82	0x91	0x00	0x43	Volume up hold
- 0x04	0x82	0x91	0x00	0x04	Volume down press
- 0x04	0x82	0x91	0x00	0x44	Volume down press
- 0x04	0x82	0x91	0x00	0x05	Pause
- 0x04	0x82	0x91	0x00	0x01	Source R press
- 0x04	0x82	0x91	0x00	0x02	Source L press
- 0x04	0x82	0x91	0x00	0x00	Ok (bottom button)

### IR Remote (Radio)
Protokoll: NEC
- 0x47: Back/Take Call
- 0x45: Skip/End Call
- 0x44: Volume Up
- 0x40: Volume Down
- 0x7: Mode
- 0x46: Band
- 0xD: Phone Switch
- 0x9: Play/Pause
- 0x46: Mute

# Where?
- [Renault Head Unit User Manual](https://manualmachine.com/philips/22dc27962/3253077-service-manual/): Page 4, Section C1 describes the wiring of the TunerList interface
- [This blog post](https://monorailc.at/cms/2018-03-17-autoradio-tuner-list--4-----cran-lcd.html) did most of the reverse engineering of the TunerList protocol used in this project, but it is in French and the code is not very well documented
- [Another blog post](https://hackaday.io/project/203619-renault-clio-tuner-list-adapter) describes a very similar project to mine, it's not well documented either, but it provided me with the button data and the header for writing to the display