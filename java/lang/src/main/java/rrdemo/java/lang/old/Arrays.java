package rrdemo.java.lang;

/**
 * 数组.
 *
 * @author zhengrr
 * @see <a href="http://docs.oracle.com/javase/tutorial/java/nutsandbolts/arrays.html">
 * Arrays</a>
 * @since 2016-9-6
 */
public class Arrays {
   /**
    * Declaring a Variable to Refer to an Array
    */
   void declaring() {
      int[] styleJava;  // recommended.
      int styleCCpp[];
   }

   /**
    * Creating, Initializing, and Accessing an Array
    */
   void Creating() {
      int[] style1 = {1, 2, 3};
      int[] style2 = {1, 2, 3,};

      Integer[] init1;
      init1= new Integer[]{new Integer(1), new Integer(2), 3};
      Integer[] init2 = {new Integer(1), new Integer(2), 3};
   }

   /**
    * Copying Arrays
    */
   void Copying() {
      char[] copyFrom = {
         'd', 'e', 'c', 'a', 'f', 'f', 'e', 'i', 'n', 'a', 't', 'e', 'd'};

      char[] copyTo1 = new char[7];
      System.arraycopy(copyFrom, 2, copyTo1, 0, 7);
      /*or*/
      char[] copyTo2 = java.util.Arrays.copyOfRange(copyFrom, 2, 9);
   }
}
