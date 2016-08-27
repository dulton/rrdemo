package numgames.ptl.struts2;

import com.opensymphony.xwork2.ActionSupport;
import com.opensymphony.xwork2.ModelDriven;
import org.apache.struts2.convention.annotation.ParentPackage;

/**
 * Interceptor Params
 *
 * @author zhengrr
 * @version 2016-7-26 ~ 27
 */
@ParentPackage("struts2")
public class IntcpParams extends ActionSupport implements ModelDriven {
   /* str */
   private String value;

   public String getValue() { return value; }

   public void setValue(String value) {
      this.value = value;
   }

   /* view object */
   private IntcpParamsVO vo = new IntcpParamsVO();

   @Override
   public Object getModel() {
      return vo;
   }

   /**
    * execute
    *
    * @since 2016-7-26
    */
   @Override
   public String execute() throws Exception {
      return SUCCESS;
   }
}

