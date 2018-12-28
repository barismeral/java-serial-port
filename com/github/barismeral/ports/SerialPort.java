package com.github.barismeral.ports;

/**
 * @author Barış Meral
 * @since 2018.12.28
 * @version 1.0.0
 *
 * Serial Port ConCreate Class
 */
public class SerialPort {

    /**
     * library load lib\\JSPC.dll
     */
    static{

       System.loadLibrary("lib/JSPC");
       // System.loadLibrary("out/production/JavaSerialPort/lib/JSPC");
    }

    /**
     * Default Constructor
     */
    public SerialPort(){ }

    /**
     * Second Constructor
     * @param portName String
     * @param baudRate int
     * @param dataBits int
     * @param parity Enum
     * @param stopBits Enum
     */
    public SerialPort(String portName,int baudRate,int dataBits,Parity parity,StopBits stopBits){

        setPortName(portName);
        setBaudRate(baudRate);
        setDataBits(dataBits);
        setParity(parity);
        setStopBits(stopBits);

    }




    private int baudRate=9600;
    private int dataBits=8;
    private Parity parity = Parity.NONE;
    private StopBits stopBits = StopBits.ONE;
    private String portName;

    private long portHandle;

    public int getBaudRate() {
        return baudRate;
    }

    public void setBaudRate(int baudRate) {
        this.baudRate = baudRate;
    }

    public int getDataBits() {
        return dataBits;
    }

    public void setDataBits(int dataBits) {
        this.dataBits = dataBits;
    }

    public Parity getParity() {
        return parity;
    }

    public void setParity(Parity parity) {
        this.parity = parity;
    }

    public StopBits getStopBits() {
        return stopBits;
    }

    public void setStopBits(StopBits stopBits) {
        this.stopBits = stopBits;
    }

    public String getPortName() {
        return portName;
    }

    public void setPortName(String portName) {
        this.portName = portName;
    }


    /**
     * private access
     * <b>native function C++</b>
     * @param portName String
     * @return long win32 Handle Pointer
     */
    private native long openPort(String portName);

    /**
     * <b>native function C++</b>
     * @param portHandle long win32 Handle Pointer
     * @return boolean status
     */
    private native boolean closePort(long portHandle);

    /**
     * private access
     * <b>native function C++</b>
     * @param portHandle long win32 Handle Pointer
     * @param baudRate  int baud rate
     * @param bitSize int bit size
     * @param parity int parity
     * @param stopBits int stop bits
     * @return boolean status
     */
    private native boolean setParam(long portHandle, int baudRate,int bitSize,int parity,int stopBits);

    /**
     * private access
     * <b>native function C++</b>
     * @param portHandle long win32 Handle Pointer
     * @param buffer byte array
     * @return boolean status
     */
    private native boolean write(long portHandle,byte[] buffer);

    /**
     * private access
     * <b>native function C++</b>
     * @param portHandle long win32 Handle Pointer
     * @param byteCount int read byte size
     * @return byte array
     */
    private native byte[] read(long portHandle,int byteCount);

    /**
     * private access
     * <b>native function C++</b>
     * @param portHandle long win32 Handle Pointer
     * @return boolean status
     */
    private native boolean purgePort(long portHandle);


    /**
     *
     * @return boolean process status
     */
    public boolean open(){

         portHandle = openPort(getPortName());

        int parity = getParity().value;
        int stop = getStopBits().value;
        setParam(portHandle,getBaudRate(),getDataBits(),parity,stop);
		
		if(portHandle == 5 || portHandle== -1){
		return false;
		}
		else
			return true;
		
    }

    /**
     * closed port
     * @return boolean process status
     */
    public boolean close(){


        return closePort(portHandle);

    }

    /**
     * Write port
     * @param str write text
     * @return boolean process status
     */
    public boolean write(String str){

       byte[] bytes = str.getBytes(java.nio.charset.Charset.forName("UTF-8"));
        return write(portHandle,bytes);

    }

    /**
     * read port
     * @return String reading text
     */
    public String read(){


        byte[] bytes = read(portHandle,50);
		byte[] clean;
		int i=0;
		while(bytes[i]!='\0'){
			
			i++;
		}
		
		clean = new byte[i];
		for(int j = 0; j<i; j++){
			
			clean[j] = bytes[j];
			
		}
		
        return new String(clean);

    }

    /**
     * purge port
     * @return boolean
     */
    public boolean purge(){

        return purgePort(portHandle);

    }





}
