package qg.test;

import qg.utils.JDBCutils;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class JDBCTest {
    public static void main(String[] args) throws Exception {
        Connection conn = null;
        conn = JDBCutils.getConnection();
        String sql = "update message set age = ? where name = ?";
        PreparedStatement pstmt = conn.prepareStatement(sql);
        pstmt.setInt(1,15);
        pstmt.setString(1,"zhangsan");
        int count = pstmt.executeUpdate();
        System.out.println(count>0);
        JDBCutils.release(null,pstmt,conn);
    }
}
