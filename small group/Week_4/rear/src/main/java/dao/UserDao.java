package dao;

import pojo.User;

public interface UserDao {
    //登录方法
    public int login(String username, String password);

    //注册方法
    public int register(String username, String password, String email);
}
