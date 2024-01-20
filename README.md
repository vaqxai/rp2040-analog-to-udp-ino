# "A WiFi-Enabled Voltmeter"
Converts analog signals to UDP packets and sends them 'en masse to the first connected host over the AP the device produces.

This is the also a second attempt at creating this, [the first](https://github.com/vaqxai/rp2040-analog-to-udp) was in Rust. It was far more complicated, convoluted and advanced. Had me write two supporting libraries for it. But it doesn't work. Produces hard faults I can't diagnose. This one works however.
