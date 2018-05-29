// Sparse.java
// Kevin Duong
// keduong 
// CMPS101 - PA3
// Feb. 4th, 2017
// Handles input and output files of Matrix
// Used FileIO.java as framework

import java.io.*;
import java.util.Scanner;

class Sparse{
   
   public static void main(String[] args) throws IOException{
      Scanner in = null;
      PrintWriter out = null;
      String line = null;
      String[] token = null;
      int i, j, a, b, n;
      int lineNumber = 0;
      int row, column;
      double value;
      Matrix A,B,C;

      if(args.length != 2){
         System.err.println("Usage: Sparse infile outfile");
         System.exit(1);
      }
      
      in = new Scanner(new File(args[0]));
      out = new PrintWriter(new FileWriter(args[1]));
      
      // Parse ints and create Matricies
      n = Integer.parseInt(in.next());
      a = Integer.parseInt(in.next());
      b = Integer.parseInt(in.next());
      A = new Matrix(n);
      B = new Matrix(n);

      
      // insert values for Matrix A
      for (i=0; i<a;i++){
         row = Integer.parseInt(in.next());
         column = Integer.parseInt(in.next());
         value = Double.parseDouble(in.next());
         A.changeEntry(row,column,value);         
      }
      
      // spacing between A and B
      line = in.nextLine();
      
      // insert values for matrix B
      for (i=0; i<b;i++){
         row = Integer.parseInt(in.next());
         column = Integer.parseInt(in.next());
         value = Double.parseDouble(in.next());
         B.changeEntry(row,column,value);         
      }
     
      // Print based on assignment specification
      out.format("A has %s non-zero entries\n", A.getNNZ());
      out.println(A);
      
      out.format("B has %s non-zero entries\n",B.getNNZ());
     	out.println(B);
     
      C = A.scalarMult(1.5);
		out.println("(1.5)*A = ");
     	out.println(C);

      C = A.add(B);
		out.println("A+B = ");
      out.println(C);

      C = A.add(A);
		out.println("A+A = ");
      out.println(C);

      C = B.sub(A);
		out.println("B-A = ");
      out.println(C);

      C = A.sub(A);
		out.println("A-A = ");
      out.println(C);

      C = A.transpose();
		out.println("Transpose(A) = ");
      out.println(C);

      C = A.mult(B);
     	out.println("A*B = ");
      out.println(C);

      C = B.mult(B);
      out.println("B*B = ");
      out.println(C);

      in.close();
      out.close();
   }
}