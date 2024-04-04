package servlet;

import dao.UserDao;
import domain.ResponseData;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/register")
public class RegisterServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        resp.setContentType("application/json;charset=UTF-8");

        //解决跨域问题
        resp.setHeader("Access-Control-Allow-Origin", "*");
        resp.setHeader("Access-Control-Allow-Methods", "POST");
        resp.setHeader("Access-Control-Allow-Headers", "Content-Type");

        String username = req.getParameter("username");
        String password = req.getParameter("password");
        String email = req.getParameter("email");

//        System.out.println(username + " " + password + " " + email);

        int flag = UserDao.register(username, password,email);
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
