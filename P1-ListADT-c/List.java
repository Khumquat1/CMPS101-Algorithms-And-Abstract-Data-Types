// List.java
// Kevin Duong 
// keduong
// 1-17-17
// PA1 - List.java
// List ADT for PA1
// Used Queue.java and Stack.java as framework

class List{

   private class Node{
      // Fields
      int data;
      Node next;
      Node prev;
      
      // Constructor
      Node(int data) { 
         this.data = data; 
         next = null; 
         prev = null; 
      }
      
      Node(int data, Node prev, Node next){
         this.data = data; 
         this.next = next; 
         this.prev = prev; 
      }
      
      // toString():  overrides Object's toString() method
      public String toString() { 
         return String.valueOf(data); 
      }
      
      // equals(): overrides Object's equals() method
      public boolean equals(Object x){
         boolean eq = false;
         Node that;
         if(x instanceof Node){
            that = (Node) x;
            eq = (this.data==that.data);
         }
         return eq;
      }
   }

   // Fields
   private Node front;
   private Node back;
   private Node cursor;
   private int index;
   private int length;

   // Constructor
   List() { 
      front = back = cursor = null; 
      length = 0; 
      index = -1;
   }


   // Access Functions --------------------------------------------------------

   // length()
   // Returns number of elements in this List
   int length() { 
      return length; 
   }
   
   // index()
   //  If cursor is defined, returns the index of the cursor element,
   //   otherwise returns -1.
   int index() { 
      return index; 
   }

   // front() 
   // Returns front element. 
   // Pre: length()>0
   int front(){
      if( length < 1 ){
         throw new RuntimeException(
            "List Error: front() called on empty List");
      }
      return front.data;
   }
   
   // back() 
   // Returns back element. 
   // Pre: length()>0
   int back(){
      if( length < 1 ){
         throw new RuntimeException(
            "List Error: back() called on empty List");
      }
      return back.data;
   }
   
   // get() 
   // Returns front element. 
   // Pre: length()>0, index()>= 0 
   int get(){
      if( length < 1 || index<0){
         throw new RuntimeException(
            "List Error: front() called on emptyList or undef. index");
      }
      return cursor.data;
   }
   
   // equals(List L)
   // Returns true if this List and L are the same integer
   // sequence. The cursor is ignored in both lists.
   boolean equals(List L){
      boolean eq = false;
      Node N, M;
      
      N = front;
      M = L.front;
      eq = (length == L.length);
      if (!eq) return eq;
      while(N != null && M != null){
         eq = N.equals(M);
         if (!eq) return eq;
         N = N.next;
         M = M.next;
      }
      return eq;
   }


   // Manipulation Procedures -------------------------------------------------

   // clear()
   // Resets this List to original empty State
   void clear(){
      if (front == null) return; //already empty
      front = front.next = null;
      length = 0;
   }

   // moveFront()
   // If List is non-empty, places the cursor under the front element,
   // otherwise does nothing.
   void moveFront(){
      if (length > 0){
         cursor = front;
         index = 0;
      }
   }
  
   // moveBack()
   // If List is non-empty, places the cursor under the back element,
   // otherwise does nothing.
   void moveBack(){
      if (length > 0){
         cursor = back;
         index = length-1;
      }
   }
   
   // movePrev()
   // If cursor is defined and not at front, moves cursor one step toward
   // front of this List, if cursor is defined and at front, cursor becomes
   // undefined, if cursor is undefined does nothing.
   void movePrev(){
      if (cursor != null && index != 0){
         cursor = cursor.prev;
         --index;
      }
      else if(cursor != null && index == 0){
         cursor = null;
         index = -1;
      }
   }

   // moveNext()
   // If cursor is defined and not at back, moves cursor one step toward
   // back of this List, if cursor is defined and at back, cursor becomes
   // undefined, if cursor is undefined does nothing.
   void moveNext(){
      if (cursor != null && index != length-1){
         cursor = cursor.next;
         ++index;
      }
      else if(cursor != null && index == length-1){
         cursor = null;
         index = -1;
      }
   }
   
   // prepend(int data)
   // Insert new element into this List. If List is non-empty,
   // insertion takes place before front element.
   void prepend(int data){
      Node N = new Node(data, null, front);
      ++length;
      if(front == null)
         back = front = N;
      else{
         front = front.prev = N;
      }
   }
   
   // append(int data)
   // Insert new element into this List. If List is non-empty,
   // insertion takes place before back element.
   void append(int data){
      Node N = new Node(data, back, null);
      ++length;
      if(front == null)
         front = back = N;
      else{
         back = back.next = N;
      }
   }
   
   //insertBefore(int Data)
   // Insert new element before cursor.
   // Pre: length()>0, index()>=0
   void insertBefore(int data){
      if (index <0 || length <1)
         throw new RuntimeException(
         "List Error: insertBefore() called on undefined index or empty List");
      Node N = new Node(data, cursor.prev, cursor);
      ++length;
      if (cursor.prev == null)
         front = cursor.prev = N;
      else{
         cursor.prev.next = N;
         cursor.prev = N;
      }
   }
   
   //insertAfter(int Data)
   // Insert new element after cursor.
   // Pre: length()>0, index()>=0
   void insertAfter(int data){
      if (index <0 || length <1)
         throw new RuntimeException(
         "List Error: insertBefore() called on undefined index or empty List");
      Node N = new Node(data, cursor, cursor.next);
      ++length;
      if (cursor.next == null)
         back = cursor.next = N;
      else{
         cursor.next.prev = N;
         cursor.next = N;
      }
   }
   
   // deleteFront()
   // Deletes the front element. 
   // Pre: length()>0   
   void deleteFront(){
      if (length<1)
         throw new RuntimeException(
      "List Error: deleteFront() called on empty list");
      if (cursor == front){
         front = back = null;
      }
      else{
         front = front.next;
         front.prev = null;
      }
      --length;
  
   }

   // deleteBack()
   // Deletes the front element. 
   // Pre: length()>0
   void deleteBack(){
      if (length<1)
         throw new RuntimeException(
      "List Error: deleteFront() called on empty list");
      back = back.prev;
      back.next = null;
   }
   
   // delete()
   // Deletes the cursor element, making the cursor undef.
   // Pre: length() >0, index() >=0
   void delete(){
      if (index <0 || length <1)
         throw new RuntimeException(
         "List Error: delete() called on undefined index or empty List");
      --length;
      cursor.prev.next = cursor.next;
      cursor.next.prev = cursor.prev;
      cursor = null;
   }
   
   
   // Other Functions ---------------------------------------------------------

   // toString()
   // Overrides Object's toString method. Returns a String
   // representation of this List consisting of a space
   // separated sequence of integers, with front on left.
   public String toString(){
      String out = new String();
      Node N = front;
      
      for(N = front; N != null; N=N.next){
         out = out + String.valueOf(N.data) + " ";
      }
      return out;
   }

   // copy()
   // Returns a new List representing the same integer sequence as this
   // List. The cursor in the new list is undefined, regardless of the
   // state of the cursor in this List. This List is unchanged.
   List copy(){
      List L = new List();
      Node N = this.front;

      while( N!=null ){
         L.append(N.data);
         N = N.next;
      }
      return L;
   }
}