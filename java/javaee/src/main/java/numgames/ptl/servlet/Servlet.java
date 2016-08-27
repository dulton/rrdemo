package numgames.ptl.servlet;

import javax.servlet.*;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

/**
 * Servlet
 *
 * @author zhengrr
 * @version 2016-7-28
 */
public class Servlet extends HttpServlet {

   /**
    * Called by the servlet container to indicate to a servlet that the servlet
    * is being placed into service.
    *
    * <p>The servlet container calls the <code>init</code> method exactly once
    * after instantiating the servlet. The <code>init</code> method must
    * complete successfully before the servlet can receive any requests.
    *
    * <p>The servlet container cannot place the servlet into service if the
    * <code>init</code> method <ol> <li>Throws a <code>ServletException</code>
    * <li>Does not return within a time period defined by the Web server </ol>
    *
    * @param config a <code>ServletConfig</code> object containing the servlet's
    *               configuration and initialization parameters
    * @throws ServletException if an exception has occurred that interferes with
    *                          the servlet's normal operation
    * @see UnavailableException
    * @see #getServletConfig
    */
   @Override
   public void init(ServletConfig config) throws ServletException {
      super.init(config);
   }

   /**
    * Called by the servlet container to allow the servlet to respond to a
    * request.
    *
    * <p>This method is only called after the servlet's <code>init()</code>
    * method has completed successfully.
    *
    * <p>  The status code of the response always should be set for a servlet
    * that throws or sends an error.
    *
    * <p>Servlets typically run inside multithreaded servlet containers that can
    * handle multiple requests concurrently. Developers must be aware to
    * synchronize access to any shared resources such as files, network
    * connections, and as well as the servlet's class and instance variables.
    * More information on multithreaded programming in Java is available in <a
    * href="http://java.sun.com/Series/Tutorial/java/threads/multithreaded.html">
    * the Java tutorial on multi-threaded programming</a>.
    *
    * @param req the <code>ServletRequest</code> object that contains the
    *            client's request
    * @param res the <code>ServletResponse</code> object that contains the
    *            servlet's response
    * @throws ServletException if an exception occurs that interferes with the
    *                          servlet's normal operation
    * @throws IOException      if an input or output exception occurs
    */
   @Override
   public void service(ServletRequest req, ServletResponse res) throws ServletException, IOException {
      super.service(req, res);
   }

   @Override
   protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
      super.doGet(req, resp);
   }

   @Override
   protected void doHead(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
      super.doHead(req, resp);
   }

   @Override
   protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
      super.doPost(req, resp);
   }

   @Override
   protected void doPut(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
      super.doPut(req, resp);
   }

   @Override
   protected void doDelete(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
      super.doDelete(req, resp);
   }

   @Override
   protected void doOptions(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
      super.doOptions(req, resp);
   }

   @Override
   protected void doTrace(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
      super.doTrace(req, resp);
   }

   /**
    * Called by the servlet container to indicate to a servlet that the servlet
    * is being taken out of service.  This method is only called once all
    * threads within the servlet's <code>service</code> method have exited or
    * after a timeout period has passed. After the servlet container calls this
    * method, it will not call the <code>service</code> method again on this
    * servlet.
    *
    * <p>This method gives the servlet an opportunity to clean up any resources
    * that are being held (for example, memory, file handles, threads) and make
    * sure that any persistent state is synchronized with the servlet's current
    * state in memory.
    */
   @Override
   public void destroy() {
      super.destroy();
   }
}
