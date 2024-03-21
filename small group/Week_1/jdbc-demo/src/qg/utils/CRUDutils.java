package qg.utils;

import java.net.ConnectException;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

public class CRUDutils {


    //通用执行增删改的方法
    public static int update(String sql,Object ... params){
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;
        try {
            //获取连接
            conn = JDBCutils.getConnection();

            //执行查询
            pstmt = conn.prepareStatement(sql);

            //设置占位符
            //params底层是数组
            for (int i = 0; i < params.length; i++) {
                pstmt.setObject(i+1,params[i]);
            }

            //返回更新数据的条数
            return pstmt.executeUpdate();

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }finally {
            try {
                //释放资源
                JDBCutils.release(rs,pstmt,conn);
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
        }
    }


    //执行查询的方法
    public static ArrayList<Student> query(String sql, Object... params){
        ArrayList<Student> list = new ArrayList<>();
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;
        try {
            //获取连接
            conn = JDBCutils.getConnection();

            //执行查询
            pstmt = conn.prepareStatement(sql);
            //设置占位符
            for (int i = 0; i < params.length; i++) {
                pstmt.setObject(i+1,params[i]);
            }
            //执行sql语句 获取结果集
            rs = pstmt.executeQuery();
            //处理结果集
            while (rs.next()) {
                //获取数据
                String name = rs.getString("name");
                int age = rs.getInt("age");
                //封装对象
                Student stu = new Student(name,age);
                //装载集合
                list.add(stu);
            }
            return list;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }finally {
            try {
                JDBCutils.release(rs,pstmt,conn);
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
        }
    }
}
