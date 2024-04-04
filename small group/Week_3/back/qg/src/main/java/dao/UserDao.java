package dao;

import domain.User;
import untils.CRUDutils;

import java.util.ArrayList;

public class UserDao {
    private UserDao() {};

    /**
     *登录
     * @param username
     * @param password
     * @return -1不存在该用户  1用户名密码正确  0用户名密码错误
     */
    public static int login(String username,String password){
        String sql = "select username,password from user where username = ?";
        ArrayList<User> query = CRUDutils.query(sql,username);
        if(query.isEmpty()){
            return -1;
        }else{
            User user = query.get(0);
            if(user.getPassword().equals(password)){
                return 1;
            }else{
                return 0;
            }
        }
    }

    /**
     * 注册
     * @param username
     * @param password
     * @param email
     * @return -1该用户已存在  1注册成功  0注册失败
     */
    public static int register(String username,String password,String email){
        String sql1 = "select username,password,email from user where username = ? or email = ?";
        ArrayList<User> query = CRUDutils.query(sql1,username,email);
        System.out.println(query);
        if(!(query.isEmpty())){
            return -1;
        }


        String sql2 = "insert into user (username,password,email) values (?,?,?)";

        int count = CRUDutils.update(sql2,username,password,email);
        System.out.println(count);
        if(count>0){
            return 1;
        }else {
            return 0;
        }
    }
}
