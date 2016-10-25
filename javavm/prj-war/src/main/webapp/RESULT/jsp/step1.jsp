<%----%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
         pageEncoding="UTF-8" %>
<%!
   private int initVar = 0;
   private int serviceVar = 0;
   private int destroyVar = 0;

   @Override
   public void jspInit() {
      ++initVar;
      System.out.println("jspInit(): " + initVar);
   }

   @Override
   public void jspDestroy() {
      ++destroyVar;
      System.out.println("jspDestroy(): " + destroyVar);
   }
%>
<%
   ++serviceVar;
   System.out.println("_jspService(): " + serviceVar);
%>
<html>
<head>
   <title>第一个JSP程序</title>
</head>
<body>
Address: <%= request.getRemoteAddr() %><br/>
Date: <%= new java.util.Date() %>
</body>
</html>