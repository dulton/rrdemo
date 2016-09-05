package rrdemo.rrlegend.rrdemo.rrlegend.underlying;

/**
 * 位置.
 *
 * @author zhengrr
 * @since 2016-9-5
 */
public final class Position {
   /* 多重平面六边形坐标
    * Multiple Plane Hexagonal Coordinate
    * w  -z \     ^ y
    *        \   /
    *         \ /
    * -x ------X-----> x
    *         / \
    *        /   \
    *    -y /     v z
    */
   private int w;
   private int x;
   private int y;
   private int z;

   /**
    * 判断平面六边形坐标是否符合规格.
    *
    * @return 判断结果.
    */
   private boolean isNormalized() {
      return !(0 != x && 0 != y && 0 != z) &&
         !(0 < x && (y < 0 || z < 0)) &&
         !(x < 0 && (0 < y || 0 < z)) &&
         !(0 == x && ((0 < y && 0 < z) || (y < 0 && z < 0)));
   }

   /**
    * 规格化平面六边形坐标.
    */
   private void normalize() {
      if (isNormalized())
         return;

      int tmp;

      /* x = y + z */
      tmp = x;
      x -= tmp;
      y += tmp;
      z += tmp;
      if (isNormalized())
         return;

      /* y = x - z */
      tmp = y;
      x += tmp;
      y -= tmp;
      z -= tmp;
      if (isNormalized())
         return;

      /* z = x - y */
      tmp = z;
      x += tmp;
      y -= tmp;
      z -= tmp;
      if (isNormalized())
         return;
   }

   public final int w() {
      return w;
   }

   public final int x() {
      return x;
   }

   public final int y() {
      return y;
   }

   public final int z() {
      return z;
   }

   /**
    * 将当前位置转移到目的位置.
    *
    * @param destination 目的位置.
    */
   public final void transferTo(final Position destination) {
      w = destination.w();
      x = destination.x();
      y = destination.y();
      z = destination.z();
      normalize();
   }

   /**
    * 将当前位置按指定矢量转移.
    *
    * @param x 指定矢量的平面六边形分量X.
    * @param y 指定矢量的平面六边形分量Y.
    * @param z 指定矢量的平面六边形分量Z.
    */
   public final void transferBy(final int x, final int y, final int z) {
      this.x += x;
      this.y += y;
      this.z += z;
      normalize();
   }

   /**
    * 构造函数.
    *
    * @param w 当前位置的重W.
    * @param x 当前位置的平面六边形坐标X.
    * @param y 当前位置的平面六边形坐标Y.
    * @param z 当前位置的平面六边形坐标Z.
    */
   public Position(final int w, final int x, final int y, final int z) {
      this.w = w;
      this.x = x;
      this.y = y;
      this.z = z;
      normalize();
   }

   /**
    * 构造函数. 使用保留重(0).
    *
    * @param x 当前位置的平面六边形坐标X.
    * @param y 当前位置的平面六边形坐标Y.
    * @param z 当前位置的平面六边形坐标Z.
    */
   public Position(final int x, final int y, final int z) {
      this(0, x, y, z);
   }

   /**
    * 求到原点的(最短)距离.
    *
    * @return 到原点的(最短)距离.
    */
   private int findDistanceWithOrigin() {
      return Math.abs(x) + Math.abs(y) + Math.abs(z);
   }

   /**
    * 求到另一位置的(最短)距离.
    *
    * @param other 另一位置.
    * @return 到另一位置的(最短)距离.
    * @throws Exception 俩位置不处于同一重, 且不处于保留重(0).
    */
   private int findDistanceWith(final Position other) throws Exception {
      if (w != other.w() && 0 != w && 0 != other.w())
         throw new Exception("The current w is " + w
            + ", but other w is " + other.w() + ".");
      Position dist = new Position(other.x() - x, other.y() - y, other.z() - z);
      return dist.findDistanceWithOrigin();
   }

   /**
    * 判断是否与另一位置相邻.
    *
    * @param other 另一位置.
    * @return 判断结果.
    */
   public boolean isBorderingWith(final Position other) {
      try {
         return 1 == findDistanceWith(other);
      } catch (Exception e) {
         return false;
      }
   }

   //void moveTo
   //void teleportTo(final Position destination);
}
