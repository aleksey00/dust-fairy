
const int pressureInput = A1; //select the analog input pin for the pressure transducer
// const int pressureZero = 102.4; //analog reading of pressure transducer at 0psi
const int pressureZero = 98.6; //analog reading of pressure transducer at 0psi
const int pressureMax = 921.6; //analog reading of pressure transducer at 100psi
const int pressuretransducermaxPSI = 300; //psi value of transducer being used
const int baudRate = 9600; //constant integer to set the baud rate for serial monitor
// const int sensorreadDelay = 250; //constant integer to set the sensor read delay in milliseconds
const int sensorreadDelay = 100; //constant integer to set the sensor read delay in milliseconds
float pressureValue = 0; //variable to store the value coming from the pressure transducer
