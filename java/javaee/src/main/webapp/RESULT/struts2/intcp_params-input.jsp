<%@ page contentType="text/html; charset=UTF-8" %>
<%@ taglib prefix="s" uri="/struts-tags" %>
<!DOCTYPE html>
<html>
<head>
    <title>Interceptor Params</title>
</head>
<body>
<h1>Interceptor Params</h1>
<s:form action="intcp_params">
    <s:textfield name="value" label="Value"/>
    <s:textfield name="member" label="Member Value"/>
    <s:submit/>
</s:form>
</body>
</html>
