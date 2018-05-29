// Lex.java
// Kevin Duong 
// keduong
// 1-17-17
// PA1 - Lex.java
// Sorts given in file using List ADT into out file.
// Used FileIO.java as frame

import java.io.*;
import java.util.Scanner;

class Lex {
   public static void main(String[] args) throws IOException{
      // Variables ------------------------------------------------
      Scanner in = null;
      PrintWriter out = null;
      String line = null;
      String[] token = null;
      int cursor, lineNumber = -1;
      int i, j, n = 0;
    
      // Input check (only accepts in out)
      if(args.length>2 || args.length<2) {
         System.err.println("Usage: Lex infile outfile");
         System.exit(1);
      }

      in = new Scanner(new File(args[0]));
      out = new PrintWriter(new FileWriter(args[1]));
      // Count lines of the file
      while(in.hasNextLine()) {
         in.nextLine();
         n++;
      }

      // Recreate Scanner and create String array and List
      List L = new List();
      token = new String[n];
      
      in.close();
      in = null;
      in = new Scanner(new File(args[0]));
     

      // Put all lines of the file into the String array
      while(in.hasNextLine()) {
         ++lineNumber;
         token[lineNumber] = in.nextLine();
      }
     
      // Put first line of the input file into list (already sorted)
      L.append(0);

      // Insertion Sort for (length - 1) elements
      for(i = 1; i < token.length; ++i) {
         String tmp = token[i];
         j = i - 1;
         // Reset list index to the back so we are able to 
         // movePrev() to find the right index
         L.moveBack();
         // String compare the current line and each line in the list
         cursor = L.get();
         while(j >= 0 && tmp.compareTo(token[cursor]) <= 0) {
            L.movePrev();
            --j;
         }
         // Exited loop before moving off so insertAfter() index
         if(L.index() >= 0)
            L.insertAfter(i);
         // Fell off the list so the new element must be prepend()
         else
            L.prepend(i);
      }

      // Reset index to the front of the List
      L.moveFront();
      // Loop through List to print out all lines in the correct order
      while(L.index() >= 0) {
         cursor = L.get();
         out.println(token[cursor]);
         L.moveNext();
      }
     
      // Close file writers and file openers
      in.close();
      out.close();
   }
}