### A RC Car that can be controlled through TCP Server APP of your phone

Demo video on: https://youtu.be/rDZwDA26lGA

<img width="700" src="https://user-images.githubusercontent.com/119554730/206114635-6363e92f-9335-482c-96b4-bc732f9d86d4.jpg">

# Materials Needed

### 1. An ESP8266 development board

<img width="300" src="https://user-images.githubusercontent.com/119554730/205442956-80c5409c-7379-4d29-abb5-be7ce9e91644.png">

### 2. A battery management board with battery indicator

<img width="200" src="https://user-images.githubusercontent.com/119554730/205443039-cec23a4f-ad46-43b4-96a1-922259091977.jpg">

### 3. A lithium battery

<img width="300" src="https://user-images.githubusercontent.com/119554730/205443145-4b2be562-5cf6-48f3-8122-399a5766d4bb.jpg">

### 4. A cable with a USB-A port (Cut off the interface and use a multimeter to identify the positive and negative wires)

<img width="300" src="https://user-images.githubusercontent.com/119554730/205443305-d2ed4303-4d5d-4390-a992-de1d75e767e3.png">

### 5. Two continuously rotating servos (you can choose the set with wheels)

<img width="300" src="https://user-images.githubusercontent.com/119554730/206124745-26c2fa47-4f54-4b16-a0e2-0fc1f5f1a5bc.jpg">

### 6. Two red LEDs and two white LEDs

<img width="300" src="https://user-images.githubusercontent.com/119554730/206125954-0eea4e2b-18f1-48eb-8bd1-c63db033941b.jpg"><img width="300" src="https://user-images.githubusercontent.com/119554730/206125977-2542bae7-7680-4dcd-9e96-60946bc18ea9.jpg">

# Connect these devices as shown below, install them into the case
<div align=center>
<img width="1127" src="https://user-images.githubusercontent.com/119554730/206152431-dbe4709e-2264-46e7-951b-878746586075.jpg">
</div>

#### *I didn't use a battery at that time for lack of the battery management board, instead, I used a 20000mah power bank, which gave it a super long usage time

# Software Part

### 1. Open 'RC_Car.ino' with Arduino IDE, enter the name and password of your mobile hotspot(set it to 2.4GHz because ESP8266 cannot connect to 5GHz WiFi) into the program, complie and upload it to your ESP8266

### 2. Download 'NeTorch Network Debug Assistant' APP to your phone, set the port number to '8266', back to control interface, add every button according to the picture below shows, rewrite the sent data with the pink alphabet printed on each button

<div align=center>
<img width="700" src="https://user-images.githubusercontent.com/119554730/206161660-a7b9d3f4-d6d2-41f5-9760-bc1c45cde6ed.jpeg">
</div>

### 3. Turn on the switch on top of the control interface, power on the car, wait until it connects to your mobile hotspot and you're free to enjoy your DIY RC Car!
