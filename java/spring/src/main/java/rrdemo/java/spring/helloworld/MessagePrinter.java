package rrdemo.java.spring.helloworld;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

/**
 * @author zhengrr
 * @since 2016-9-18
 */
@Component
public class MessagePrinter {

   final private MessageService service;

   @Autowired
   public MessagePrinter(MessageService service) {
      this.service = service;
   }

   public void printMessage() {
      System.out.println(this.service.getMessage());
   }
}
