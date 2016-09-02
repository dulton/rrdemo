package rrdemo.rrlegend;

import java.util.Set;

/**
 * 世界.<br/> 单例模式.
 *
 * @author zhengrr
 * @since 2016-9-2
 */
public class World {
   /**
    * 单例实体.
    */
   private static World instance = new World();

   /**
    * 获取单例实体.
    *
    * @return 单例实体.
    */
   public static World i() {
      return instance;
   }

   /**
    * 构造方法(私有).
    */
   private World() {
   }

   /**
    * 世界包含的所有实体.
    */
   private Set<Entity> contents;
}
