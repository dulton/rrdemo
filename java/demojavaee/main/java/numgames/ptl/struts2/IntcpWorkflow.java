package numgames.ptl.struts2;

import com.opensymphony.xwork2.ActionSupport;
import org.apache.struts2.convention.annotation.ParentPackage;

/**
 * Interceptor Workflow
 *
 * @author zhengrr
 * @version 2016-7-25 ~ 27
 */
@ParentPackage("struts2")
public class IntcpWorkflow extends ActionSupport {

   /* txtfld */
   private String txtfld;

   public String getTxtfld() { return txtfld; }

   public void setTxtfld(String txtfld) {
      this.txtfld = txtfld;
   }

   /**
    * @since 2016-7-26
    */
   @Override
   public String execute() throws Exception {
      return SUCCESS;
   }

   /**
    * @since 2016-7-26
    */
   @Override
   public void validate() {
      if (getTxtfld().length() <= 0) {
         addFieldError("txtfld", "Textfield is required.");
      }
   }
}
