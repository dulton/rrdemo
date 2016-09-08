package numgames.ptl.struts2;

import com.opensymphony.xwork2.ActionSupport;
import org.apache.struts2.convention.annotation.Action;
import org.apache.struts2.convention.annotation.Namespace;
import org.apache.struts2.convention.annotation.ParentPackage;
import org.apache.struts2.convention.annotation.Result;

/**
 * Action Annotation
 *
 * @author zhengrr
 * @version 2016-7-25
 */
@Namespace("/struts2")
@ParentPackage("struts2")
@Action(results = {
   @Result(name = "success", location = "/RESULT/struts2/action_ann.html"),
   @Result(name = "none", location = "/RESULT/struts2/action_ann.html"),
   @Result(name = "input", location = "/RESULT/struts2/action_ann.html")
})
public class ActionAnn extends ActionSupport {
}
