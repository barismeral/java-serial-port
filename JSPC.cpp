	#include "com_github_barismeral_ports_SerialPort.h"
	#include <windows.h>
	   
   
 /*
 * Class:     com_github_barismeral_ports_SerialPort
 * Method:    openPort
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_github_barismeral_ports_SerialPort_openPort
  (JNIEnv *env, jobject obj, jstring str){
	
	const char prefix[] = "\\\\.\\"; // port prefix \\.\\ 
	
	const char* port = env->GetStringUTFChars(str, JNI_FALSE);

	const int strSize = strlen(port);
	const int symboSize = strlen(prefix)+1;


	char portFullName[symboSize + strSize];
	strcpy(portFullName, prefix);
	strcat(portFullName, port);
	
	
	HANDLE hComm = CreateFile(
		portFullName,
		GENERIC_READ | GENERIC_WRITE,
		0,
		0,
		OPEN_EXISTING,
		NULL,
		0);
	
	   if(hComm==INVALID_HANDLE_VALUE){ // invalid port return -1
          
          return (jlong)-1;
	     }
	     
	     else if(GetLastError() == ERROR_ACCESS_DENIED){ // Return 5
	     	return (jlong)5;
		 }
		 
		else{
			
		   DCB *dcb = new DCB();
		   
		   GetCommState(hComm,dcb);
		   
		}
		
    	return (jlong)hComm; // return port handle
	}


	/*
	 * Class:     com_github_barismeral_ports_SerialPort
	 * Method:    closePort
	 * Signature: (J)Z
	 */
	JNIEXPORT jboolean JNICALL Java_com_github_barismeral_ports_SerialPort_closePort
	  (JNIEnv *env, jobject obj, jlong port){
		HANDLE hComm = (HANDLE)port;
	
	 return CloseHandle(hComm);
	
	}



	   

	/*
	 * Class:     com_github_barismeral_ports_SerialPort
	 * Method:    setParam
	 * Signature: (JIIII)Z
	 */
	JNIEXPORT jboolean JNICALL Java_com_github_barismeral_ports_SerialPort_setParam
	  (JNIEnv *env, jobject obj, jlong port, jint baud, jint bits, jint par, jint stop){
		
		HANDLE HComm = (HANDLE)port;
		DCB *dcb = new DCB();
		
		dcb->BaudRate = baud;
		dcb->ByteSize = bits;
		dcb->Parity = par;
		dcb->StopBits = stop;
		
	 SetCommState(HComm,dcb);
	COMMTIMEOUTS *commTime = new COMMTIMEOUTS();
			commTime->ReadIntervalTimeout = 10;
        	commTime->ReadTotalTimeoutConstant = 0;
        	commTime->ReadTotalTimeoutMultiplier = 0;
        	commTime->WriteTotalTimeoutConstant = 0;
        	commTime->WriteTotalTimeoutMultiplier = 0;
        
        return SetCommTimeouts(HComm,commTime);
        
	}

	/*
	 * Class:     com_github_barismeral_ports_SerialPort
	 * Method:    write
	 * Signature: (J[C)Z
	 */
	  JNIEXPORT jboolean JNICALL Java_com_github_barismeral_ports_SerialPort_write
  		(JNIEnv *env, jobject obj, jlong port, jbyteArray bytes){
		
		HANDLE hComm = (HANDLE) port;
      
		jboolean status = JNI_FALSE;
		
	
		
		jbyte *buffer = env->GetByteArrayElements(bytes,JNI_FALSE);
		
		
		if(WriteFile(hComm,buffer,(DWORD)env->GetArrayLength(bytes),NULL,NULL)){
			
			status = JNI_TRUE;	
		}
		else {
			
		      status = JNI_FALSE;
		}
		
		env->ReleaseByteArrayElements(bytes,buffer,0);
	
	
		return status;
	
	}
	
	/*
	 * Class:     com_github_barismeral_ports_SerialPort
	 * Method:    read
	 * Signature: (JI)[B
	 */
	JNIEXPORT jbyteArray JNICALL Java_com_github_barismeral_ports_SerialPort_read
  (JNIEnv *env, jobject obj, jlong port, jint size){
  
			HANDLE hComm = (HANDLE) port;
			
			PurgeComm(hComm,PURGE_TXCLEAR);
    		jbyteArray array = env->NewByteArray(size);
    
    		
    	    jbyte buffer[size];
    	 //(DWORD)size
    		
    		if(ReadFile(hComm,buffer,size,NULL,NULL))
			{	
	         	env->SetByteArrayRegion(array,0,size,buffer);
	        }
	        

			return array;
        }
    	
		 /*
		 * Class:     com_github_barismeral_ports_SerialPort
		 * Method:    purgePort
		 * Signature: (J)Z
		 */
		JNIEXPORT jboolean JNICALL Java_com_github_barismeral_ports_SerialPort_purgePort
		  (JNIEnv *env, jobject obj, jlong port){
	  	HANDLE hComm = (HANDLE) port;
	  	
	  return PurgeComm(hComm,PURGE_TXCLEAR);
	  	
	  }

	
	
	
	
	
	
	
	
	
	
	
	
	
