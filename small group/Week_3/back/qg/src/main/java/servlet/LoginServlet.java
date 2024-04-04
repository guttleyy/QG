package servlet;

import dao.UserDao;
import domain.ResponseData;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        resp.setContentType("application/json;charset=UTF-8");

        //解决跨域问题
        resp.setHeader("Access-Control-Allow-Origin", "*");
        resp.setHeader("Access-Control-Allow-Methods", "POST");
        resp.setHeader("Access-Control-Allow-Headers", "Content-Type");

        String username = req.getParameter("username");
        String password = req.getParameter("password");

        int flag = UserDao.login(username, password);
        if(flag == 1){
            /*req.setAttribute();
            req.getRequestDispatcher("/success").forward(req,resp);*/
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

}
