package numgames.ptl.interceptor;

import com.opensymphony.xwork2.Action;
import com.opensymphony.xwork2.ActionInvocation;
import org.apache.struts2.ServletActionContext;

import javax.servlet.http.HttpServletRequest;

/**
 * Check Input
 *
 * @author zhengrr
 * @version 2016-7-27
 */
public class CheckInput implements com.opensymphony.xwork2.interceptor.Interceptor {

   /**
    * Does nothing
    */
   @Override
   public void destroy() { }

   /**
    * Does nothing
    */
   @Override
   public void init() { }

   /* from javax.servlet.http.HttpServlet */
   private static final String METHOD_DELETE = "DELETE";
   private static final String METHOD_HEAD = "HEAD";
   private static final String METHOD_GET = "GET";
   private static final String METHOD_OPTIONS = "OPTIONS";
   private static final String METHOD_POST = "POST";
   private static final String METHOD_PUT = "PUT";
   private static final String METHOD_TRACE = "TRACE";

   /**
    * intercept
    *
    * @param invocation the action invocation
    * @return
    * @throws Exception
    */
   @Override
   public String intercept(ActionInvocation invocation) throws Exception {
      final HttpServletRequest request = (HttpServletRequest)
         invocation.getInvocationContext().get(ServletActionContext.HTTP_REQUEST);
      if (request.getMethod().equals(METHOD_GET)) return Action.INPUT;

      return invocation.invoke();
   }
}
