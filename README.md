Internet of Stranger Things (IosT)
This project, initially developed by ACM members at McNeese State University, is a creative implementation inspired by the "Stranger Things" series, blending the iconic wall of lights with modern IoT (Internet of Things) technology. I have remodified the original design using an ESP32 WROOM, introducing two enhanced versions that leverage wireless connectivity and intuitive interactivity.

Version 1: Serial Monitor Interaction
In the first version of this remodified project, the ESP32 WROOM is programmed to light up the alphabet on the board corresponding to the letters typed into the serial monitor. The ESP32 acts as a controller, interpreting the letters and illuminating the respective light, giving a direct interface for user input. This version is ideal for local demonstrations where a simple yet responsive display is required. The use of the serial monitor makes it easy to interface with the device via USB, allowing for seamless control and interaction.

Version 2: Wireless Web-Based Interaction
The second version takes a step further by connecting the ESP32 WROOM to the internet, transforming it into a web host. Users can wirelessly interact with the alphabet lights through a web browser. The ESP32 creates a local server, which hosts a webpage where letters can be typed. The system wirelessly triggers the lights on the board corresponding to the letters entered in the browser, enabling a dynamic and immersive experience. This version demonstrates the ESP32’s capability to serve web pages and handle real-time input/output operations over a network, making it perfect for IoT-based applications.

Both versions of the project highlight the versatility of ESP32 WROOM in handling input/output operations, web hosting, and wireless communications. This remodified project not only showcases the technical capabilities of IoT devices but also creates a fun and interactive experience inspired by pop culture.

For this project Adafruit Neopixel lights were used. So, please make sure to install the neopixel library first before using the code.
Power Rating for Neopixel lights = 5v DC (Other details can be found in the Adrafruit official website documentation)

Demo: https://www.youtube.com/watch?v=avIp73Ixm1g
