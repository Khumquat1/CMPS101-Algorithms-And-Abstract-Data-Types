// Lex.java
// Kevin Duong 
// keduong
// 1-17-17
// PA1 - Lex.java
// Sorts given in file using List ADT into out file in lex order.
// Used FileIO.java as framework

import java.io.*;
import java.util.Scanner;

class Lex{
   public static void main(String[] args) throws IOException{
      
      // variables --------------------------------------------
      Scanner in = null;
      PrintWriter out = null;
      String line = null;
      String[] token = null;
      int i, j, n=0;
      int lineNumber = -1;

      // input check -------------------------------------------
      if(args.length != 2){
         System.err.println("Usage: Lex infile outfile");
         System.exit(1);
      }
      
      // count number of lines n in the file and create String array
      in = new Scanner(new File(args[0]));
      out = new PrintWriter(new FileWriter(args[1]));      
      while( in.hasNextLine() ){
         in.nextLine();
         ++n;

      }
      token = new String[n];
      
      // remake scanner for new string array and list --------------------    
      in.close();
      in = null;    
      in = new Scanner(new File(args[0]));
      
      // make string array and put lines in--------------------------------
      while(in.hasNextLine()){
         ++lineNumber;
         token[lineNumber] = in.nextLine();
      }
      // new list for integers (indices)-----------------------------------      
      List L = new List();
      L.append(0); // firstline
      
      // insertion sort algorithm *for indicies, not elements*
      for (i=1;i<token.length;++i){ 
         String s = token[i];
         j = i-1; // loop control
         L.moveFront(); // find the appropriate index
         while(j>=0 && s.compareTo(token[L.get()]) <=0){ //string comparison
            L.moveNext();
            --j;
         }
         if (L.index() >=0) L.insertBefore(i); // insert in the list in there
         else L.append(i); // we fell off so need to append
      }
      
      // printing ------------------------------------------------------------
      L.moveBack(); // get the cursor under the back element
      while(L.index() >= 0){
         out.println(token[L.get()]); 
         L.movePrev(); // go all the way through the list
      }
      in.close();
      out.close();
   }
}