//Roots.java
//Kevin Duong
//keduong
//pa4
//Computes the roots/zeroes of a polynomial with the degree and domain(endpoints) entered by the user. It employs the Bisection method.
//--------------------------------------------------------------------------------------------------------------------------------------
import java.util.Scanner;
class Roots{
   public static void main(String[] args){
  
      Scanner sc = new Scanner(System.in);

      double roots=1.0, resolution, tolerance, threshold, a, b, L, R;
         resolution = Math.pow(10.0,-2.0);
         tolerance = Math.pow(10.0,-7.0);
         threshold = Math.pow(10.0,-3.0);
     //resolution is to establish the width of sections, tolerance to pinpoint zeroes, threshold to account for round off errors.
      System.out.print("Enter the degree: ");
         int degree = sc.nextInt();
      System.out.print("Enter "+(degree+1)+" coefficients: ");
         double[] C= new double[degree+1];
         for(int i=0;i<C.length;i++){
            C[i]=sc.nextDouble();
         }
      System.out.print("Enter the left and right endpoints: ");
         L = sc.nextDouble();
         R = sc.nextDouble();
         System.out.println();
         a = L;
         b = a + resolution;
         double[] D= diff(C);
         boolean found = false;
         while (b<= R){
            if (poly(C,a)*poly(C,b)<0){ 
               roots = findRoot(C,a,b,tolerance); //find actual root
               double check = Math.abs(poly(C,roots));// used to ensure the root is within 10^-7 distance from 0. 
               if (check <=threshold){ // if that root is good
                  System.out.print("Root found at "); // misc printing...
                  System.out.printf("%.5f%n", roots); // rounded to the nearest 5th
                  found= true; // we got one

//               System.out.println(poly(C,roots));    for debugging
               }
            }
            if (poly(D,a)*poly(D,b) <0){
               roots = findRoot(D,a,b,tolerance); // this computes the even roots of the function, while checking the roots of the derivate.
               double check = Math.abs(poly(C,roots)); // Checks the zero found from the derivative with the original function.
               if (check<=threshold){
                  System.out.print("Root found at ");
                  System.out.printf("%.5f%n",roots);
                  found= true;
//               System.out.println(poly(C,roots));
               }
            }      
               a=b; // for incrementing while loop
               b = a+resolution;
         }
               if (!found) // our boolean variable from earlier
                  System.out.println("No roots found.");     
   }
   
   static double poly(double[] C, double x){ //calling function to calculate value of the polynomial
      int y=C.length;
      double sum=0.0;
      for(int i=0;i<y;i++){
         sum+=C[i]*(Math.pow((x),i));
      }
      return sum;
   }   
   static double[] diff(double[] C){   // derivative of the function input by user used to check even roots.
      int n=C.length-1;
      double[]D = new double[n];
      for(int i=0; i<n;i++){
         D[i]=C[i+1]*(i+1);
      }
      return D;
   }
   static double findRoot(double[] C, double a, double b, double tolerance){ // used to calculate roots of function input 
      double mid = a, width;
      width = b-a;
      while(width>tolerance){
         mid = (a+b)/2;
         if (poly(C,a)*poly(C,mid)<=0)
            b=mid;
            else
               a=mid;
         width = b-a;
      }
      return mid;   
   }
}

