package rrdemo.java.lang.initialization;

/**
 * @author zhengrr
 * @since 2016-9-9
 */
public final class Class {
   /**
    * 构造方法.<br/>
    *
    * @param obj 参数.
    */
   public Class(final Object obj) {
      super();
   }

   /**
    * 无参构造方法.<br/>
    * 调用另一构造方法.
    */
   public Class() {
      this(new Object());
   }

   /**
    * 清理方法.<br/>
    * 当被垃圾回收时自动调用.
    *
    * @throws Throwable
    */
   @Override
   protected void finalize() throws Throwable {
      super.finalize();
   }
}
