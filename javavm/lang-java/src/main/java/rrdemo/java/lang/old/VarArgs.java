package rrdemo.java.lang.initialization;

/**
 * 可变参数.
 *
 * @author zhengrr
 * @since 2016-9-9
 */
public final class VarArgs {
   /**
    * 接受可变参数(对象数组)的构造方法.
    *
    * @param args 可变参数(对象数组).
    */
   public VarArgs(final Object[] args) { }

   /**
    * 上述方法的语法糖.
    *
    * @param args 可变参数.
    * @since JDK 5+.
    */
   public VarArgs(final boolean... args) { }
}
