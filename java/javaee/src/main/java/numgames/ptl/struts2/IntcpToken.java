package numgames.ptl.struts2;

import com.opensymphony.xwork2.ActionSupport;
import org.apache.struts2.convention.annotation.InterceptorRef;
import org.apache.struts2.convention.annotation.InterceptorRefs;
import org.apache.struts2.convention.annotation.ParentPackage;

/**
 * Interceptor Token
 *
 * @author zhengrr
 * @version 2016-7-27
 */
@ParentPackage("struts2")
@InterceptorRefs({
   @InterceptorRef("headStruts2Stack"),
   @InterceptorRef("tokenSession"),
   @InterceptorRef("tailStruts2Stack")
})
public class IntcpToken extends ActionSupport {}
