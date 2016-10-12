package rrdemo.java.lang.operators;

/**
 * 赋值(操作符).
 *
 * @author zhengrr
 * @since 2016-9-9
 */
public final class Assignment {

   /**
    * 对象的赋值.<br/>
    * 引用赋值.
    */
   public void object() {
      Object ref = new Object();
      Object alias = ref;
   }

   /**
    * 对象的传递.<br/>
    * 引用传递.
    *
    * @param obj 对象(的引用).
    * @return 对象(的引用).
    */
   public Object object(final Object obj) {
      return obj;
   }

}
