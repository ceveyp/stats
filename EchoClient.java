/*
Authors: Philip Cevey, Danton Nguyen
This program is a client that makes echo requests of a server.
It opens a TCP connection on the port the server is listening on,
sends some data and the server echoes it back to the client. For 
demonstration, the server's response is printed as a string, even 
though the server is supposed to accept binary data. The client
listens for user input in a loop and closes the connection when
it receives a '.' from the user. 
*/
import java.io.*;
import java.net.*;
import java.util.*;

public class EchoClient {
	public static void main(String[] args){
		try{
            Socket sock = new Socket("127.0.0.1", 43522); //open a TCP connection with the server
      		OutputStream os = sock.getOutputStream(); //get output stream
      		InputStream is = sock.getInputStream(); //get input stream
            DataOutputStream out = new DataOutputStream(os);
            DataInputStream in = new DataInputStream(is);
			Scanner input = new Scanner(System.in); //create scanner for user input
   			byte[] echoString = input.nextLine().getBytes(); //get user input as an array of bytes
			while('.' != (char) echoString[0]){ //while the user has not typed '.'
				byte[] echoReply = new byte[echoString.length]; //declare an array to hold the response from the server
				out.write(echoString); //send server the data to echo
            	in.read(echoReply); //read server's response into array of bytes
           		System.out.print("Server: ");
				for(int i = 0; i < echoReply.length; ++i) //for demonstration purposes, print the server's response as a string
                	System.out.printf("%c", echoReply[i]);
            	System.out.println();
				echoString = input.nextLine().getBytes();
			}
            sock.close(); //close the connection
		}
		catch(IOException e){
        	System.err.println("IO exception");
        }
	}
}

