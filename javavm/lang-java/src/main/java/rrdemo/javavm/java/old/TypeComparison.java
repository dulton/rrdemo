package rrdemo.java.lang.operators;

/**
 * 比较(操作符).
 *
 * @author zhengrr
 * @since 2016-9-9
 */
public final class Comparison {

   /**
    * 对象的比较.<br/>
    * 比较引用.
    */
   public void objectEquivalence() {
      Object a = new Object();
      Object aa = a;
      Object b = new Object();
      assert a == aa;
      assert a != b;

      // 另外, equals()方法默认也是比较引用:
      assert a.equals(aa);
      assert !a.equals(b);
   }
}
