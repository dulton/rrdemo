package rrdemo.rrlegend;

import rrdemo.rrlegend.rrdemo.rrlegend.underlying.Position;

/**
 * 实体.
 *
 * @author zhengrr
 * @since 2016-9-2
 */
public class Entity {

   /**
    * 位置.
    */
   private Position pos;

   /**
    * 获取位置.
    *
    * @return 位置.
    */
   public final Position getPos() {
      return pos;
   }

   /**
    * 设定位置.
    *
    * @param position 位置.
    */
   public final void setPos(final Position position) {
      this.pos = position;
   }

}
