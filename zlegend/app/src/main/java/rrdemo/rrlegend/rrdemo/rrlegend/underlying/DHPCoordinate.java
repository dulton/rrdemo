package rrdemo.rrlegend.rrdemo.rrlegend.underlying;

/**
 * 离散平面六边形坐标.<br/>
 * Discrete Hexagonal Plane Coordinate.
 *
 * @author zhengrr
 * @since 2016-9-7
 */
public final class DHPCoordinate {
   /**
    * 构造函数.
    *
    * @param xx 分量x.
    * @param yy 分量y.
    * @param zz 分量z.
    */
   public DHPCoordinate(final int xx, final int yy, final int zz) {
      x = xx;
      y = yy;
      z = zz;
   }

   /*
    *    -z \     ^ y
    *        \   /
    *         \ /
    * -x ------X-----> x
    *         / \
    *        /   \
    *    -y /     v z
    */

   /**
    * 分量x.
    */
   private int x;

   /**
    * 分量y.
    */
   private int y;

   /**
    * 分量z.
    */
   private int z;

   /**
    * 获取分量x.
    *
    * @return 分量x.
    */
   public int getX() {
      return x;
   }

   /**
    * 获取分量y.
    *
    * @return 分量y.
    */
   public int getY() {
      return y;
   }

   /**
    * 获取分量z.
    *
    * @return 分量z.
    */
   public int getZ() {
      return z;
   }

   /**
    * 设定分量x.
    *
    * @param xx 分量x.
    */
   public void setX(final int xx) {
      x = xx;
   }

   /**
    * 设定分量y.
    *
    * @param yy 分量y.
    */
   public void setY(final int yy) {
      y = yy;
   }

   /**
    * 设定分量z.
    *
    * @param zz 分量z.
    */
   public void setZ(final int zz) {
      z = zz;
   }

   /**
    * 判断是否符合规格.
    *
    * @return 判断结果.
    */
   private boolean isNormalized() {
      return !(0 != x && 0 != y && 0 != z)
         && !(0 < x && (y < 0 || z < 0))
         && !(x < 0 && (0 < y || 0 < z))
         && !(0 == x && ((0 < y && 0 < z) || (y < 0 && z < 0)));
   }

   /**
    * 规格化.
    */
   private void normalize() {
      if (isNormalized()) {
         return;
      }

      int tmp;

      /* x = y + z */
      tmp = x;
      x -= tmp;
      y += tmp;
      z += tmp;
      if (isNormalized()) {
         return;
      }

      /* y = x - z */
      tmp = y;
      x += tmp;
      y -= tmp;
      z -= tmp;
      if (isNormalized()) {
         return;
      }

      /* z = x - y */
      tmp = z;
      x += tmp;
      y -= tmp;
      z -= tmp;
      // if (isNormalized()){
      //    return;
      // }
   }

   /**
    * 判断是否在原点上.
    *
    * @return 判断结果.
    */
   public boolean isAtOrigin() {
      normalize();
      return 0 == x && 0 == y && 0 == z;
   }

   /**
    * 判断是否在轴上.
    *
    * @return 判断结果.
    */
   public boolean isAtAxis() {
      normalize();
      return 0 == y && 0 == z
         || 0 == x && 0 == z
         || 0 == x && 0 == y;
   }

   /**
    * 判断是否在X轴上.
    *
    * @return 判断结果.
    */
   public boolean isAtXAxis() {
      normalize();
      return 0 == y && 0 == z;
   }

   /**
    * 判断是否在Y轴上.
    *
    * @return 判断结果.
    */
   public boolean isAtYAxis() {
      normalize();
      return 0 == x && 0 == z;
   }

   /**
    * 判断是否在Z轴上.
    *
    * @return 判断结果.
    */
   public boolean isAtZAxis() {
      normalize();
      return 0 == x && 0 == y;
   }

   /**
    * 求长度(坐标到原点的距离).
    *
    * @return 长度.
    */
   public int length() {
      normalize();
      return Math.abs(x) + Math.abs(y) + Math.abs(z);
   }

   /**
    * 自增.
    *
    * @param other 增量.
    */
   public void increase(final DHPCoordinate other) {
      x += other.getX();
      y += other.getY();
      z += other.getZ();
   }

   /**
    * 自减.
    *
    * @param other 减量.
    */
   public void decrease(final DHPCoordinate other) {
      x -= other.getX();
      y -= other.getY();
      z -= other.getZ();
   }

   /**
    * 求和.
    *
    * @param augend 被加数.
    * @param addend 加数.
    * @return 和.
    */
   public static DHPCoordinate sum(final DHPCoordinate augend,
                                   final DHPCoordinate addend) {
      return new DHPCoordinate(
         augend.getX() + addend.getX(),
         augend.getY() + addend.getY(),
         augend.getZ() + addend.getZ());
   }

   /**
    * 加.
    *
    * @param addend 加数.
    * @return 和.
    */
   public DHPCoordinate plus(final DHPCoordinate addend) {
      return DHPCoordinate.sum(this, addend);
   }

   /**
    * 求差.
    *
    * @param minuend    被减数.
    * @param subtrahend 减数.
    * @return 差.
    */
   public static DHPCoordinate remainder(final DHPCoordinate minuend,
                                         final DHPCoordinate subtrahend) {
      return new DHPCoordinate(
         minuend.getX() - subtrahend.getX(),
         minuend.getY() - subtrahend.getY(),
         minuend.getZ() - subtrahend.getZ());
   }

   /**
    * 减.
    *
    * @param subtrahend 减数.
    * @return 差.
    */
   public DHPCoordinate minus(final DHPCoordinate subtrahend) {
      return DHPCoordinate.remainder(this, subtrahend);
   }

   /**
    * 求两坐标间的距离.
    *
    * @param c1 坐标1.
    * @param c2 坐标2.
    * @return 两坐标间的距离.
    */
   public static int distance(final DHPCoordinate c1,
                              final DHPCoordinate c2) {
      return DHPCoordinate.remainder(c1, c2).length();
   }

   /**
    * 求到另一坐标的距离.
    *
    * @param other 另一坐标.
    * @return 距离.
    */
   public int distanceWith(final DHPCoordinate other) {
      return DHPCoordinate.distance(this, other);
   }

   /**
    * 判断两坐标是否重合.
    *
    * @param c1 坐标1.
    * @param c2 坐标2.
    * @return 判断结果.
    */
   public static boolean isCoincident(final DHPCoordinate c1,
                                      final DHPCoordinate c2) {
      return 0 == distance(c1, c2);
   }

   /**
    * 判断是否与另一坐标重合.
    *
    * @param other 另一坐标.
    * @return 判断结果.
    */
   public boolean isCoincidentWith(final DHPCoordinate other) {
      return DHPCoordinate.isCoincident(this, other);
   }

   /**
    * 判断两坐标是否相邻.
    *
    * @param c1 坐标1.
    * @param c2 坐标2.
    * @return 判断结果.
    */
   public static boolean isBordering(final DHPCoordinate c1,
                                     final DHPCoordinate c2) {
      return 1 == distance(c1, c2);
   }

   /**
    * 判断是否与另一坐标相邻.
    *
    * @param other 另一坐标.
    * @return 判断结果.
    */
   public boolean isBorderingWith(final DHPCoordinate other) {
      return DHPCoordinate.isBordering(this, other);
   }

   /**
    * 判断两坐标是否共线.
    *
    * @param c1 坐标1.
    * @param c2 坐标2.
    * @return 判断结果.
    */
   public static boolean isCollinear(final DHPCoordinate c1,
                                     final DHPCoordinate c2) {
      return DHPCoordinate.remainder(c1, c2).isAtAxis();
   }

   /**
    * 判断是否与另一坐标共线.
    *
    * @param other 另一坐标.
    * @return 判断结果.
    */
   public boolean isCollinearWith(final DHPCoordinate other) {
      return DHPCoordinate.isCollinear(this, other);
   }
}
