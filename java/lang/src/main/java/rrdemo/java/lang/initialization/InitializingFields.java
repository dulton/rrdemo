package rrdemo.java.lang.initialization;

/**
 * 初始化字段.
 *
 * @author zhengrr
 * @see <a href="http://docs.oracle.com/javase/tutorial/java/nutsandbolts/datatypes.html">
 * The Java™ Tutorials - Primitive Data Types</a>
 * @see <a href="http://docs.oracle.com/javase/tutorial/java/javaOO/initial.html">
 * The Java™ Tutorials - Initializing Fields</a>
 * @since 2016-9-6
 */
public final class InitializingFields {

   /**
    * 布尔型.
    */
   private boolean boolDefault/*= false*/;

   /**
    * 字符型.
    */
   private char charDefault/*= '\u0000'*/;

   /**
    * 字节整型.
    */
   private byte byteDefault/*= (byte) 0*/;

   /**
    * 短整型.
    */
   private short shortDefault/*= (short) 0*/;

   /**
    * 整型.
    */
   private int intDefault/*= 0*/;

   /**
    * 长整型.
    */
   private long longDefault/*= 0L*/;

   /**
    * (单精度)浮点型.
    */
   private float floatDefault/*= 0.0f*/;

   /**
    * 双精度浮点型.
    */
   private double doubleDefault/*= 0.0d*/;

   /**
    * 对象.
    */
   private Object objectDefault/*= null*/;

   /* 类/静态初始化块 */
   static {
   }

   /* 对象/实例初始化块 */ {
   }
}
