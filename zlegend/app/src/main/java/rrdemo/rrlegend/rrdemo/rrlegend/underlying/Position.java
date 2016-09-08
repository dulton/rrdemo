package rrdemo.rrlegend.rrdemo.rrlegend.underlying;

/**
 * 位置.
 *
 * @author zhengrr
 * @since 2016-9-5
 */
public final class Position {
   /**
    * 构造函数.
    *
    * @param ww 境w.
    * @param cc 坐标c.
    */
   public Position(final int ww, final DHPCoordinate cc) {
      w = ww;
      c = cc;
   }

   /**
    * 构造函数.
    *
    * @param ww 境w.
    * @param xx 坐标c分量x.
    * @param yy 坐标c分量y.
    * @param zz 坐标c分量z.
    */
   public Position(final int ww, final int xx, final int yy, final int zz) {
      w = ww;
      c = new DHPCoordinate(xx, yy, zz);
   }

   /**
    * 境w.
    */
   private int w;

   /**
    * 坐标c.
    */
   private DHPCoordinate c;

   /**
    * 获取境w.
    *
    * @return 境w.
    */
   public int getW() {
      return w;
   }

   /**
    * 获取坐标c.
    *
    * @return 坐标c.
    */
   public DHPCoordinate getC() {
      return c;
   }

   /**
    * 设定境w.
    *
    * @param ww 境w.
    */
   public void setW(final int ww) {
      w = ww;
   }

   /**
    * 设定坐标c.
    *
    * @param cc 坐标c.
    */
   public void setC(final DHPCoordinate cc) {
      this.c = c;
   }

   //void moveTo
   //void teleportTo(final Position destination);
}
