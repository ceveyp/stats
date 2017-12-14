/*
Authors: Philip Cevey, Danton Nguyen
This program is the echo server from assignment 2 question 1. However, this 
time instead the server is able to deal with multiple concurrent requests from
clients by processing each request in a new thread. The echo server listens on
a port for client connections, then creates a thread and lets this new thread
do the echo response, and then goes right back to listening for connections. 
*/
import java.io.*;
import java.net.*;

public class EchoServer {
    public static void main(String[] args){
        try{
            ServerSocket sock = new ServerSocket(43522); //open a socket on some port
            while(true){
                Socket client = sock.accept(); //listen for client connections
                Thread worker = new Thread(new EchoServerWorker(client)); //create a new thread to deal with client request
                worker.start(); //start new thread
            }
        }
        catch(IOException e){
            System.err.printf("EchoServer: IO exception: %s%n", e.getMessage());
        }
    }
}

class EchoServerWorker implements Runnable{
    private final Socket client;
    public EchoServerWorker(Socket client){
        this.client = client;
    }
    @Override
    public void run(){
        try{
            byte[] b = new byte[1000]; //initialize a buffer
            DataInputStream in = new DataInputStream(client.getInputStream()); //get input stream
            DataOutputStream out = new DataOutputStream(client.getOutputStream()); //get output stream
            int nread; //variable for number of bytes read
            while((nread = in.read(b)) != -1){ //loop through until the client is done sending data
                out.write(b, 0, nread); //write this data back to the client
            }
            client.close(); //close the connection
        }
        catch(IOException e){
            System.err.printf("EchoServerClient: IO exception: %s%n", e.getMessage());
        }
    }
}