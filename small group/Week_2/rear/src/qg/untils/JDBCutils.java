package qg.untils;

import java.io.IOException;
import java.io.InputStream;
import java.sql.*;
import java.util.Properties;

public class JDBCutils {

    //私有化构造方法
    public JDBCutils() {};

    private static String driverClass;
    private static String url;
    private static String user;
    private static String password;

    //静态代码块，执行一次
    //先于静态方法执行
    //用来一次性地对成员变量进行赋值
    static{
        try {
            //获取配置文件
            InputStream is = JDBCutils.class.getResourceAsStream("/qg/resources/db.properties");

            //加载配置文件
            Properties prop = new Properties();
            prop.load(is);

            //为成员变量赋值
            driverClass = prop.getProperty("driverClass");
            url = prop.getProperty("url");
            user = prop.getProperty("user");
            password = prop.getProperty("password");

            //注册驱动
            Class.forName(driverClass);

            is.close();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    //获取连接
    public static Connection getConnection() {
        Connection conn = null;
        //获取连接
        try {
            conn = DriverManager.getConnection(url,user,password);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        //返回对象
        return conn;
    }

    //释放资源
    public static void release(ResultSet rs, PreparedStatement pstmt,Connection conn) throws SQLException {
        try {
            if(rs != null){
                rs.close();
            }
            if(pstmt != null){
                pstmt.close();
            }
            if(conn != null){
                conn.close();
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
