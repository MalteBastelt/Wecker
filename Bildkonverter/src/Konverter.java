import java.awt.*;
import java.io.*;
import java.awt.image.BufferedImage;
//import java.io.File;

import javax.imageio.ImageIO;

public class Konverter {
	int imgHeight;
	int imgWidth;
	BufferedImage imgBuffer;
	static int [][] imgArray;
	static int [][] bin;
	
	
	private void readImage(String fileName) {
		try {
			imgBuffer = ImageIO.read(new File(fileName));
		} catch (IOException e) {
			System.err.println("File " + fileName + " unknown!");
			System.exit(1);
		}
		// --- get width and height of image
		imgWidth = imgBuffer.getWidth();
		imgHeight = imgBuffer.getHeight();
	}
	
	private int[][] getImageArray() {
		int[][] imgArray = new int[imgHeight][imgWidth];
		for (int row = 0; row < imgHeight; row++) {
			for (int col = 0; col < imgWidth; col++) {
				imgArray[row][col] = imgBuffer.getRGB(col, row);
			}
		}
		return imgArray;
	}
	
	private int [][] getHexValues() {
		int [][] hex = new int [(imgHeight+7)/8][imgWidth]; //falls Height kein Vielfaches von 8 ist z.B. 12
		for(int x=0; x<imgWidth; x++){
			for (int y=0; y<imgHeight; y+=8){
				int hexByte = 0;
				for(int digit=0; digit<8; digit++){
					if(y+digit < imgHeight) {
					hexByte |= bin[y+digit][x]<<digit;
					}
				}
				hex[y/8][x] = hexByte;
			}
		}
		return hex;
	}
	
	private void convertToBinary(){
		bin = new int [imgHeight][imgWidth];
		imgArray = getImageArray();
		for(int x=0; x<imgWidth; x++){
			for(int y=0; y<imgHeight; y++){
				if((imgArray[y][x]&0xFF)<180){
					bin[y][x] = 1;
				}
			}
		}
		return;
	}
	
	private void printSize() {
		System.out.println("width: " + imgWidth);
		System.out.println("height: " + imgHeight);
	}
	
/*	private void printHexArray() {
		int hex[][];
		hex = getHexValues();
		
		System.out.println(" ");
		System.out.println("Hex Array:");
		System.out.println("-----------");
		System.out.print("{");
		
		
		for (int j = 0; j<hex[0].length;j++){
			if(j>0) {
				System.out.print(" ");
			}
			System.out.print("  {");
			String ende = ", ";
			for (int i = 0; i<hex.length; i++){
				if(i==hex.length-1){
					ende = "";
					//System.out.println("hallo");
				}
				System.out.print("0x" + Integer.toHexString(hex[i][j]) + ende);
			}
			if((j==hex[0].length-1)){
				ende = "},";
			} else {
				ende = "}, ";
			}
			System.out.println(ende);
		}
		
	}*/
	
	private void printHexArray() {
		int hex[][];
		hex = getHexValues();
		int cnt = 0;
		System.out.println(" ");
		System.out.println("Hex Array:");
		System.out.println("-----------");
		System.out.print("{");
		
		for (int j = 0; j<hex[0].length;j++){
			String ende = ", ";
			for (int i = 0; i<hex.length; i++){
				if(j==hex[0].length-1 && i==hex.length-1) {
					ende = "}";
				}
				System.out.print("0x" + Integer.toHexString(hex[i][j]) + ende);
				cnt++;
			}		
		}
		System.out.println();
		System.out.println("Anzahl Elemente: " + cnt);
	}
	
	private void printBinaryPic() {
		System.out.println("Vorschau Binärbild:");
		System.out.println("-------------------");
		for (int i = 0; i<bin.length; i++){
			for (int j = 0; j<bin[0].length;j++){
				if(bin[i][j]==1)
				System.out.print("x ");
				else
					System.out.print("  ");
			}
			System.out.println();
		}
	}
	
	public static void main(String [] args){
		/*Konverter pic = new Konverter();
		pic.readImage("Buchstaben\\J.png");
		pic.convertToBinary();
		pic.printBinaryPic();
		pic.printHexArray();*/
		convertPicture("herzmittel.png");
	}
	
	public static void convertPicture(String file) {
		Konverter pic = new Konverter();
		pic.readImage(/*"Buchstaben\\"+*/file);
		pic.convertToBinary();
		pic.printBinaryPic();
		pic.printHexArray();	
	}

}
