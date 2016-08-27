package numgames.ptl.struts2;

import com.opensymphony.xwork2.ActionSupport;
import org.apache.struts2.convention.annotation.ParentPackage;

/**
 * Interceptor Internationalization
 *
 * @author zhengrr
 * @version 2016-7-26 ~ 27
 */
@ParentPackage("struts2")
public class IntcpI18n extends ActionSupport {
   /**
    * @since 2016-7-26
    */
   @Override
   public String execute() throws Exception {
      setValue(getText("Hello."));
      return SUCCESS;
   }

   private String value;

   public String getValue() {
      return value;
   }

   public void setValue(String value) {
      this.value = value;
   }
}
