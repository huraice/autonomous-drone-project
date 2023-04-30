# autonomous-drone-project

# First-phase

# HardWare Requirements 
Drone frame
BLDC Motor 1800KV/13T *4
ESC 30 A * 4
Pixhawk Flight Controller
LipoBattery
GPS Module
NodeMCU ESP8266 12-E *  2 (For tranmitter and reciver for the first phase drone Controlling)
Joystick Module
Jetson Nano
Connecting Wires (Male to Female, Female to Female)
Soldering Instruments( Solder Iron, Lead and Flux)
Dot PCB Boards

# Configuring Pixhawk 2.4.8 for ESP8266
# File loading on ESP8266
On this have two folder that containing the ino file for the transmitter and receiver. With the Arduino Software you can flash this codes on the ESP8266.

# Connections for the transmitter and Receiver
# Transmitter
After the Flashing the codes. On the transmitter side first to we connect the power supply for Joystick with common ground connection with NodeMCU 12E. There after we connect VRX and VRY pin connection of joystick to the NodeMCU's A0, D4, D3 and D0 ports.

# Receiver
On this the NodeMCU ESP8266 is connected to PIxhawks's Telecommunication Channel 1 connected as RX - TX, TX-RX configuaration. And after we fetch the connected IP Address of Reciver there after Re enter this IP on the Transmittter NodeMCU.

# Assemblinng the drone 
On this step we set up the frame work and LiPo battery battery is connected on ESC. The ESC is connected to the Pixhauk's Output Ports. There after we connected the BLDC Motor Clock wise and Anticlock wise refer the figure  *BLDC Motor Connection.jpeg*. 

# Jetson Nano
After the configuaration we start the journey with JETSON Nano. With this we can be programmable Drone into autopilot mode and it connected Telecommunicaion Port 2.
