#include <iostream>

using namespace std;

int main()
{
   int myId, numLet, intResult;
   double doubleResult;

   myId = 20240237;
   numLet = 4;

   cout << "My family name is Tran" << endl;
   cout << "My student ID is " << myId << endl;
   cout << "The number of characters in my last name is " << numLet << endl;

   intResult = myId % 17;
   cout << "\nExpression #1 ------------ : " << intResult << endl;

   intResult = (numLet + 17) % 11;
   cout << "\nExpression #2 ------------ : " << intResult << endl;

   doubleResult = myId / (numLet + 800.);
   cout << "\nExpression #3 ------------ : " << doubleResult << endl;

   intResult = 1 + 2 + 3 + numLet;
   cout << "\nExpression #4 ------------ : " << intResult << endl;

   doubleResult = 15000. / (80. + ((myId - 123456.)));
   doubleResult = doubleResult / ((numLet + 20.) * (numLet + 20.));
   cout << "\nExpression #5 ------------ : " << doubleResult << endl;
   
   return 0;
}

/* -------------------- past of run ------------------

My family name is Tran
My student ID is 20240237
The number of characters in my last name is 4

Expression #1 ------------ : 3

Expression #2 ------------ : 10

Expression #3 ------------ : 25174.4

Expression #4 ------------ : 10

Expression #5 ------------ : 1.29452e-06
Program ended with exit code: 0

 ---------------------------------------------------- */