import qg.utils.CRUDutils;
import qg.utils.Student;

import java.util.ArrayList;

public class CRUDTest {
    public static void main(String[] args) {
        String sql = "select * from message where name = ?";
        String name = "zhangsan";
        ArrayList<Student> query = CRUDutils.query(sql, name);
        System.out.println(query);
    }
}
