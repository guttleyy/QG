package servlet;

import dao.Impl.UserDaoImpl;
import pojo.ResponseData;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/user/*")
public class UserServlet extends BaseServlet{

    public void login(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        resp.setContentType("application/json;charset=UTF-8");
        System.out.println("login1");

        String username = req.getParameter("username");
        String password = req.getParameter("password");
//        System.out.println(username + " " + password);

        int flag = new UserDaoImpl().login(username,password);
//        System.out.println(flag);
        if(flag == 1){
            ResponseData responseData = new ResponseData(200,null,"登录成功!");
            resp.getWriter().write(responseData.toString());
        }else if(flag == 0){
            ResponseData responseData = new ResponseData(404,null,"用户名或密码错误!");
            resp.getWriter().write(responseData.toString());
        }else{
            ResponseData responseData = new ResponseData(404,null,"用户不存在!");
            resp.getWriter().write(responseData.toString());
        }

    }


    public void register(HttpServletRequest req, HttpServletResponse resp) throws IOException{
        resp.setContentType("application/json;charset=UTF-8");

        String username = req.getParameter("username");
        String password = req.getParameter("password");
        String email = req.getParameter("email");


        int flag = new UserDaoImpl().register(username,password,email);
        if(flag == 1){
            ResponseData responseData = new ResponseData(200,null,"注册成功!");
            resp.getWriter().write(responseData.toString());
        }else if(flag == 0){
            ResponseData responseData = new ResponseData(500,null,"注册失败!");
            resp.getWriter().write(responseData.toString());
        }else{
            ResponseData responseData = new ResponseData(404,null,"用户名或邮箱已存在!");
            resp.getWriter().write(responseData.toString());
        }
    }
}
