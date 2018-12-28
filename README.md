

## Custom basic Serial Port Communication for Java

# Usage 

<code>
  
// create port
  
SerialPort port = new SerialPort();

// port settings

port.setBaudRate(9600);

port.setDataBits(8);

port.setParity(Parity.NONE);

port.setStopBits(StopBits.ONE);

port.setPortName("COM20");


//writing & reading

port.write("Hello, World");

String str = port.read();

// port open or close

port.open();

port.close();
</code>

# Please Fork
