# Motivation
My 2003 Renault Laguna had a TunerList head unit which only supported Radio and CD. I rather like listening to whatever bullshit comes to mind on Spotify, so i bought a cheap replacement from Amazon wich supports Bluetooth Connection, but cant interface with the original steering wheel controls.

# Solution
This project aims to fix that and maybe incorporate some more functionality further down the line. Right now, it only connects to the dashboard screen (see [User Manual](https://manualmachine.com/philips/22dc27962/3253077-service-manual/) Page 4, Section C1) which sends button data through a custom I2C protocol (see [this blog post](https://monorailc.at/cms/2018-03-17-autoradio-tuner-list--4-----cran-lcd.html)) and translates that to IR signals that the new head unit can understand.

# Protocols
## Tuner List Buttons
Source: https://hackaday.io/project/203619-renault-clio-tuner-list-adapter
- 0x04	0x82	0x91	0x00	0x03	Volume up press
- 0x04	0x82	0x91	0x00	0x43	Volume up hold
- 0x04	0x82	0x91	0x00	0x04	Volume down press
- 0x04	0x82	0x91	0x00	0x44	Volume down press
- 0x04	0x82	0x91	0x00	0x05	Pause
- 0x04	0x82	0x91	0x00	0x01	Source R press
- 0x04	0x82	0x91	0x00	0x02	Source L press
- 0x04	0x82	0x91	0x00	0x00	Ok (bottom button)

## IR Remote (Radio)
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