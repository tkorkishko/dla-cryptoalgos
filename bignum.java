package bignum;

import java.math.BigInteger;
import java.security.KeyPairGenerator;
import java.security.SecureRandom;

import javax.crypto.*;
import java.util.Scanner;

public class bignum {
	
	private static byte key[];
	private static long startTime;
	
	public static void startWatch( ) {
		startTime = System.currentTimeMillis();
	}
	
	public static double elapsedTime( ) {
		long now = System.currentTimeMillis();
		return (now - startTime);
	}
	
	private static void genRandomKey(int size) {
						
		SecureRandom random = new SecureRandom();
		key = new byte[size/8]; // 128 bits are converted to 16 bytes;
		random.nextBytes(key);
		
	}
	
	private static BigInteger getKeySpace(int keySize) {
		BigInteger keySpace, tmp;	
		
		tmp = BigInteger.valueOf(2);
		keySpace = tmp.pow(keySize);
		
		return keySpace;
	}	
	
	public static void convertByteToHex(byte[] byteArray)
    {
        String hex = "";
  
        // Iterating through each byte in the array
        for (byte i : byteArray) {
            hex += String.format("%02X", i);
        }
  
        System.out.print(hex);
    }
	
	public static void main(String[] args) {
				
		int i;
		
		//1. Print key space based on key size
		for(i = 8; i <= 4096; i = i*2) {
			System.out.println(i+ "-bit keyspace " + getKeySpace(i).toString(10));
		}
		
		System.out.println();
		
		//2. Generate random key for each given size
		for(i = 8; i <= 4096; i = i*2) {
			genRandomKey(i);
			System.out.print(i+ "-bit random key is:"); 
			convertByteToHex(key);
			System.out.println();
				
		}
		
		System.out.println();
		
		//3. Calculate time to search through key space for given key size - up until 32-bit key
		for(i = 8; i <= 32; i = i*2) {

			startWatch();

			for(BigInteger j = BigInteger.ZERO; j.compareTo(getKeySpace(i)) < 0; j = j.add(BigInteger.ONE) ) {
				//dummy loop
			}
			System.out.println(i+"-bit keyspace search took " + elapsedTime() + "ms");
		}
		
		System.out.println("64-bit key space search took forever.0 ms");
		System.out.println("128-bit key space search took forever.0 ms");
		System.out.println("256-bit key space search took forever.0 ms");
		System.out.println("512-bit key space search took forever.0 ms");
		System.out.println("1024-bit key space search took forever.0 ms");
		System.out.println("2048-bit key space search took forever.0 ms");
		System.out.println("4096-bit key space search took forever.0 ms");
		
	}

}
