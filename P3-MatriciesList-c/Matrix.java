// Matrix.java
// Kevin Duong
// keduong 
// CMPS101 - PA3
// Feb. 4th, 2017
// ADT for array of List objects

class Matrix{
   private class Entry{
      int column;
      double value;
      
      // Entry data type
      Entry(int column, double value){
         this.column = column;
         this.value = value;
      }
      
      public String toString(){
         return ("("+column+","+value +")") ;
      }
      
      public boolean equals (Object x){
         return ((Entry)x).column == column &&
         ((Entry)x).value == value;
      }
   }
      
      List[] matrix;
      int NNZ;    
// Constructor-----------------------------------------------------------------      
      Matrix(int n){
         if (n < 1){
            throw new RuntimeException(
            " Matrix Error: Matrix() cannot be called with n <= 0.");
         }
         this.NNZ = 0;
         matrix = new List[n+1];
         for(int i = 1; i< (n+1); ++i)
            matrix[i] = new List();
      }
// Access functions------------------------------------------------------------
      
      // getSize()
      // Returns n, the number of rows and columns in this Matrix
      int getSize(){
         return matrix.length -1;
      }
      
      // getNNZ()
      // Returns the number of Non-Zero Entries in this Matrix
      int getNNZ(){       
         return NNZ;
      }
      
      // equals(Object x)
      // overrides Object's equals()method
      public boolean equals (Object x){
         Matrix M;
         if(x instanceof Matrix){
            M = (Matrix)x;
            if(getSize() != M.getSize())
               return false;
            for(int i =1; i<= getSize(); ++i){
               if(!(matrix[i].equals(M.matrix[i])) )  
                  return false;
            }
         }
         return true;
      }
      
// manipulation procedures ----------------------------------------------------
 
      // makeZero()
      // sets this Matrix to the zero state
      void makeZero(){
      for(int i=1; i<this.getSize(); ++i)
         this.matrix[i].clear();
         NNZ = 0;
      }
      
      // copy()
      // Returns a new matrix having same entries as this Matrix
      Matrix copy(){
         Matrix cpy = new Matrix(getSize());
         Entry obj;
         for(int i=1; i<getSize(); ++i){
            matrix[i].moveFront();
            while(matrix[i].index() >=0){
               obj = (Entry) matrix[i].get();
               cpy.changeEntry(i, obj.column, obj.value);
               matrix[i].moveNext();
            }
         }
         cpy.NNZ = NNZ;
         return cpy;
      }
            
      // changeEntry(int i, int j, double x)
      // changes the ith row, jth column of this Matrix to x*obj
      // pre: 1<=i<=getSize(), 1<=j<=getSize()
      void changeEntry(int i, int j, double x){
         if(i<1 || i>getSize())
            throw new RuntimeException(
         "Error: changeEntry() called on Matrix with invalid i position.");
         if(j<1 || j>getSize())
            throw new RuntimeException(
         "Error: changeEntry() called on Matirx with invalid j position.");
         boolean noIndex = false;
         
         matrix[i].moveFront();              
         while(matrix[i].index() >= 0){         
            Entry obj = (Entry) matrix[i].get();                
            if(obj.column == j){
               noIndex = true;
               if(x == 0.){
                  matrix[i].delete();
                  return;
               }
               else{
               obj.value = x;
               return;
               }
            }
            matrix[i].moveNext();
         }         
         if(!noIndex && x!=0){
            matrix[i].moveFront();
                if (x != 0) 
                  this.NNZ++;
            if(matrix[i].index() == -1){
               matrix[i].append(new Entry(j,x));
               return;    
            }
            else{
               while(matrix[i].index() >= 0 && 
               ((Entry)matrix[i].get()).column<j){
                  matrix[i].moveNext();
               }
               if(matrix[i].index() >=0 ){
                  matrix[i].insertBefore(new Entry(j,x));
                  return;
               }
               else{
                  matrix[i].append(new Entry(j,x));
                  return;
               }
            }
         }

      }
   // scalarMult(double x)
   // returns a new Matrix that is the scalar product of this Matrix with x
   Matrix scalarMult(double x){
      Matrix product = new Matrix(getSize());
      if (x == 0){
         product.NNZ = 0;
         return product;
      }
      product = this.copy();
      for(int i = 1; i<=product.getSize(); ++i){
         product.matrix[i].moveFront();
         while(product.matrix[i].index()>=0){
            Entry obj = (Entry)product.matrix[i].get();
            product.changeEntry(i, obj.column, (x*obj.value));
            product.matrix[i].moveNext();
         }
      }
      product.NNZ = NNZ;
      return product;
   }
   // add(Matrix M)
   // returns a new Matrix that is the sum of this Matrix with M  
   Matrix add(Matrix M){
      if(getSize() != M.getSize())
         throw new RuntimeException(
      "add() called on matricies of differing size");
      Matrix A = new Matrix(getSize());
      
      if(M == this)
         return this.scalarMult(2);
      for(int i = 1; i<= getSize(); ++i){
         A.matrix[i] = addHelp(matrix[i], M.matrix[i]);
      }
      A.NNZ = M.NNZ;
      return A;
   }
      
   // sub(Matrix M)
   // returns a new Matrix that is the difference of this Matrix with M       
   Matrix sub(Matrix M){
      if(getSize() != M.getSize())
         throw new RuntimeException(
      "sub() called on matricies of differing size");
      Matrix A = new Matrix(getSize());
      A.NNZ = M.NNZ;
      if(M == this)
         return new Matrix(getSize());
      for(int i = 1; i<= getSize(); ++i){
         A.matrix[i] = subHelp(matrix[i], M.matrix[i]);
         A.NNZ--;
      }
      return A;
   }
      
   // transpose()
   // returns a new Matrix that is the transpose of this Matrix      
   Matrix transpose(){
      Matrix M = new Matrix(getSize());
      Entry obj;
      for(int i = 1; i<getSize();++i){
            matrix[i].moveFront();
            while(matrix[i].index() >= 0){
               obj = (Entry)matrix[i].get();
               M.changeEntry(obj.column, i, obj.value);
               matrix[i].moveNext();
            }
         
      }
      M.NNZ = NNZ;
      return M;
   }

   // mult(Matrix M)
   // returns a new Matrix that is the product of this Matrix with M   
   Matrix mult(Matrix M){
      if(getSize() != M.getSize())
         throw new RuntimeException(
      "mult() called on matricies of differing size");
      Matrix A = new Matrix(M.getSize());
      Matrix B = M.transpose();
      double product;
      
      for(int i =1; i<getSize(); ++i){
         if(matrix[i].length() == 0) continue;
            for(int j=1;j<getSize();++j){
                  if(B.matrix[j].length() == 0) continue;
                  product = dot(matrix[i],B.matrix[j]);
                  A.changeEntry(i,j, product);
            }
      }
      return A;
   }
   
// other functions ------------------------------------------------------------
   
   // toString()
   // overrides Object's toString() method  
   public String toString(){
      String out = "";
      for(int i = 1; i<=getSize(); ++i){
         if(matrix[i].length()>0)
            out = out + (i + ": " + matrix[i]+ "\n");
      }
      return out;
   }
  
// helper functions -----------------------------------------------------------

   // dot(List P, List Q)
   // returns the vector dot product of two Matrix Rows P, Q;
   private static double dot(List P, List Q){
      double sum = 0.;
      Entry obj1, obj2;
      P.moveFront();
      Q.moveFront();
      while(P.index()>=0 && Q.index() >=0){
         obj1 = (Entry)P.get();
         obj2 = (Entry)Q.get();
         if(obj1.column <obj2.column)
            P.moveNext();
         else if(obj1.column>obj2.column)
            Q.moveNext();
         else{
            sum = sum+(obj1.value*obj2.value);
            P.moveNext();
            Q.moveNext();
         }
      }
      return sum;
   } 

   // addHelp(List P, List Q)
   // helper function for add function
   private List addHelp(List P, List Q){
      List add = new List();
      P.moveFront();
      Q.moveFront();
      while(P.index() >=0 || Q.index()>=0){
         if(P.index() >=0 && Q.index()>=0){
            Entry obj1 = (Entry)P.get();
            Entry obj2 = (Entry)Q.get();
            if(obj1.column > obj2.column){
               add.append(new Entry(obj2.column, obj2.value));
               Q.moveNext();
            }
            else if(obj1.column == obj2.column){
               if(obj1.value+obj2.value!=0)
                  add.append(new Entry(obj1.column, (obj1.value+obj2.value)));
               P.moveNext();
			    	Q.moveNext();
	         }
            else if(obj1.column < obj2.column){
               add.append(new Entry(obj1.column, obj1.value));
               P.moveNext();
            }
         }
         else if(P.index()>=0){
            Entry obj1 = (Entry) P.get();
            add.append(new Entry(obj1.column, obj1.value));
            P.moveNext();
		   }
         else{
			Entry obj2 = (Entry) Q.get();
			add.append(new Entry(obj2.column,obj2.value));
         Q.moveNext();
         }
	   }
      return add;
	}
   
   // subHelp(List P, List Q)
   // helper function for sub function
   private List subHelp(List P, List Q){
      List sub = new List();
      P.moveFront();
      Q.moveFront();
      while(P.index() >=0 || Q.index()>=0){
         if(P.index() >=0 && Q.index()>=0){
            Entry obj1 = (Entry)P.get();
            Entry obj2 = (Entry)Q.get();
            if(obj1.column > obj2.column){
               sub.append(new Entry(obj2.column, obj2.value*(-1.)));
               Q.moveNext();
            }
            else if(obj1.column == obj2.column){
               if(obj1.value-obj2.value!=0)
                  sub.append(new Entry(obj1.column, (obj1.value-obj2.value)));
               P.moveNext();
               Q.moveNext();
            }
            else if(obj1.column < obj2.column){
               sub.append(new Entry(obj1.column, obj1.value));
               P.moveNext();
            }
         }
         else if(P.index()>=0){
            Entry obj1 = (Entry) P.get();
            sub.append(new Entry(obj1.column, obj1.value));
            P.moveNext();
         }
         else{
            Entry obj2 = (Entry) Q.get();
            sub.append(new Entry(obj2.column,obj2.value*(-1.)));
            Q.moveNext();
         }
      }
      return sub;   
   }
}
   
   