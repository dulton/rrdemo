package rrdemo.javavm.groovy

/**
 * 动态数组.
 *
 * @author zhengrr
 * @since 2016-10-26
 */
final class TypeArrayList {
   /**
    * 构造器.
    */
   private TypeArrayList() {}
   
   /**
    * 声明与定义.
    */
   static def declaringAndDefining() {
      def abc = ['a', 'b', 'c']
      abc
   }
   
   /**
    * 加入与移除.
    */
   static void addAndRemove() {
      def bcd = declaringAndDefining()
      bcd.remove('a')
      bcd << 'd'
   }
}
