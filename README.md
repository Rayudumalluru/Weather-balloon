# Low-Cost Weather Balloon Payload System

Ever wondered what happens high up in the atmosphere? This project brings weather balloon technology down to earth—literally! We've built a demonstrative weather balloon payload that monitors atmospheric and environmental conditions using IoT technology. Powered by an ESP32 microcontroller paired with smart sensors, our system collects real-time environmental data and transmits it wirelessly for monitoring and analysis.

## What Does It Measure?

Our payload keeps tabs on:

 **Temperature** – From the ground to the sky
 **Humidity** – Moisture levels in the air
 **Atmospheric Pressure** – How the air pressure changes with altitude
 **Air Pollution Levels** – What's really floating around up there

## The Brains Behind the System

We've integrated two key sensors to make this happen:

- **BME280 Sensor** – A powerhouse for measuring temperature, humidity, and atmospheric pressure all at once
- **MQ-135 Gas Sensor** – Your air quality watchdog, detecting pollutants and harmful gases

The lightweight Li-Po powered payload is strapped to a helium balloon to mimic a real weather balloon. The ESP32 processes all the sensor data and beams it wirelessly through WiFi to a monitoring dashboard where you can see what's happening in real-time.

##  What Makes This Cool?

- Real-time monitoring of environmental conditions
- Wireless WiFi-enabled data transmission
- Incredibly lightweight for balloon deployment
- Budget-friendly design that doesn't sacrifice functionality
- Complete atmospheric and pollution tracking
- Built to grow—add GPS, LoRa, or cloud integration later

##  What We're Using

**Microcontroller & Development:**
- ESP32 DevKit V1
- Arduino IDE
- Embedded C / C++
- IoT wireless communication

**Hardware You'll Need:**
- ESP32 DevKit V1
- BME280 Sensor
- MQ135 Gas Sensor
- Li-Po Battery
- TP4056 Charging Module
- MT3608 Boost Converter
- Helium Balloon

##  Where's This Useful?

- Weather monitoring and forecasting support
- Environmental research and monitoring
- Air quality tracking and analysis
- Educational demonstrations and learning
- IoT research and innovation projects

##  What's Next?

We're planning some exciting upgrades:

- **GPS Integration** – Track altitude and location in real-time
- **LoRa Communication** – Send data over long distances without WiFi
- **Cloud Data Logging** – Store historical data in the cloud
- **Mobile App** – Monitor your balloon from your phone
- **Solar Power** – Never worry about battery life again

##  The Big Picture

Our goal is simple: create an affordable, compact atmospheric monitoring platform inspired by professional weather balloons used by meteorologists and environmental scientists worldwide. We're making advanced environmental monitoring accessible to everyone—from students to researchers.

---

Ready to launch into the atmosphere? Let's go!
