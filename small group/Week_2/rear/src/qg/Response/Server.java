package qg.Response;

import qg.untils.CRUDutils;
import qg.untils.JDBCutils;
import qg.untils.User;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.ArrayList;

public class Server {
    public static void main(String[] args) throws IOException {
        int port = 8080;
        ServerSocket ss = new ServerSocket(port); //监听指定端口
        System.out.println("Response.Server is listening on port" + port);
        System.out.println("Response.Server is running...");

        while (true) {
            Socket socket = ss.accept();
            System.out.println("Client connected: " + socket);

            BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));

            //请求行
            String line = reader.readLine();
            System.out.println("Received data: " + line);

            System.out.println("Processing login request...");

            //请求头
            StringBuilder headers = new StringBuilder();
            String header;
            while ((header = reader.readLine()) != null && !header.isEmpty()) {
                System.out.println(header);
                headers.append(header).append("\r\n");
            }


            //请求体
            int contentLength = 0;
            String contentLengthHeader = "Content-Length: ";
            String[] headerLines = headers.toString().split("\r\n");
            for (String headerLine : headerLines) {
                if (headerLine.startsWith(contentLengthHeader)) {
                    contentLength = Integer.parseInt(headerLine.substring(contentLengthHeader.length()));
                    break;
                }
            }
            char[] bodyData = new char[contentLength];
            reader.read(bodyData, 0, contentLength);
            String requestBody = new String(bodyData);


            System.out.println("Request Body: " + requestBody);

            //将json字符串分割成username和password
            String[] bodyParts = requestBody.split(",");
            String username = "";
            String password = "";
            String[] part1 = bodyParts[0].split(":");
            username = part1[1].substring(1, part1[1].length() - 1);
            String[] part2 = bodyParts[1].split(":");
            password = part2[1].substring(1, part2[1].length() - 2);

            //登录
            if (line.contains("login")) {

                int flag = loginUser(username, password);

                writer.write("HTTP/1.1 200 OK\r\n");
                writer.write("Content-Type: text-html\r\n");
                writer.write("Access-Control-Allow-Origin: *\r\n"); // 允许所有源的请求
                writer.write("\r\n"); // 空行，分隔头部和消息体

                if (flag == -1) {
                    writer.write("User doesn't exist\r\n");//用户不存在
                } else if (flag == 0) {
                    writer.write("Wrong password\r\n");//密码错误
                } else if (flag == 1) {
                    writer.write("Login successful\r\n"); // 返回登录成功消息给客户端
                }
                writer.flush();
            }

            //注册
            else if (line.contains("register")) {

                int flag = registerUser(username, password);

                if (flag == 1) {
                    writer.write("HTTP/1.1 200 OK\r\n");
                    writer.write("Content-Type: text-html\r\n");
                    writer.write("Access-Control-Allow-Origin: *\r\n"); // 允许所有源的请求
                    writer.write("\r\n"); // 空行，分隔头部和消息体
                    writer.write("Register successful\r\n"); // 返回登录成功消息给客户端
                    writer.flush();
                } else if (flag == -1) {
                    writer.write("HTTP/1.1 200 OK\r\n");
                    writer.write("Content-Type: text-html\r\n");
                    writer.write("Access-Control-Allow-Origin: *\r\n"); // 允许所有源的请求
                    writer.write("\r\n"); // 空行，分隔头部和消息体
                    writer.write("User already exists\r\n"); // 返回登录成功消息给客户端
                    writer.flush();
                } else if (flag == 0) {
                    writer.write("HTTP/1.1 500 Internal Server Error\r\n");
                    writer.write("Content-Type: text-html\r\n");
                    writer.write("Access-Control-Allow-Origin: *\r\n"); // 允许所有源的请求
                    writer.write("\r\n"); // 空行，分隔头部和消息体
                    writer.write("Fail to register user\r\n"); // 返回登录成功消息给客户端
                    writer.flush();
                }

            }

            //修改密码
            else if (line.contains("reset")) {
                int flag = resetPassword(username, password);

                if (flag == 1) {
                    writer.write("HTTP/1.1 200 OK\r\n");
                    writer.write("Content-Type: text-html\r\n");
                    writer.write("Access-Control-Allow-Origin: *\r\n"); // 允许所有源的请求
                    writer.write("\r\n"); // 空行，分隔头部和消息体
                    writer.write("Reset successful\r\n"); // 返回登录成功消息给客户端
                    writer.flush();
                } else if (flag == -1) {
                    writer.write("HTTP/1.1 200 OK\r\n");
                    writer.write("Content-Type: text-html\r\n");
                    writer.write("Access-Control-Allow-Origin: *\r\n"); // 允许所有源的请求
                    writer.write("\r\n"); // 空行，分隔头部和消息体
                    writer.write("User doesn't exist\r\n");//用户不存在
                    writer.flush();
                } else {
                    writer.write("HTTP/1.1 500 Internal Server Error\r\n");
                    writer.write("Content-Type: text-html\r\n");
                    writer.write("Access-Control-Allow-Origin: *\r\n"); // 允许所有源的请求
                    writer.write("\r\n"); // 空行，分隔头部和消息体
                    writer.write("Fail to reset password\r\n"); // 返回登录成功消息给客户端
                    writer.flush();
                }
            }

            //注销账户
            else if (line.contains("logout")) {
                int flag = logout(username, password);

                if (flag == 1) {
                    writer.write("HTTP/1.1 200 OK\r\n");
                    writer.write("Content-Type: text-html\r\n");
                    writer.write("Access-Control-Allow-Origin: *\r\n"); // 允许所有源的请求
                    writer.write("\r\n"); // 空行，分隔头部和消息体
                    writer.write("Logout account successful\r\n"); // 返回登录成功消息给客户端
                    writer.flush();
                } else if (flag == -1) {
                    writer.write("HTTP/1.1 200 OK\r\n");
                    writer.write("Content-Type: text-html\r\n");
                    writer.write("Access-Control-Allow-Origin: *\r\n"); // 允许所有源的请求
                    writer.write("\r\n"); // 空行，分隔头部和消息体
                    writer.write("User doesn't exist\r\n");//用户不存在
                    writer.flush();
                }else if (flag == -2) {
                    writer.write("HTTP/1.1 200 OK\r\n");
                    writer.write("Content-Type: text-html\r\n");
                    writer.write("Access-Control-Allow-Origin: *\r\n"); // 允许所有源的请求
                    writer.write("\r\n"); // 空行，分隔头部和消息体
                    writer.write("Wrong password\r\n");//密码错误
                    writer.flush();
                }
                else {
                    writer.write("HTTP/1.1 500 Internal Server Error\r\n");
                    writer.write("Content-Type: text-html\r\n");
                    writer.write("Access-Control-Allow-Origin: *\r\n"); // 允许所有源的请求
                    writer.write("\r\n"); // 空行，分隔头部和消息体
                    writer.write("Fail to logout account\r\n"); // 返回登录成功消息给客户端
                    writer.flush();
                }
            } else {
                writer.write("HTTP/1.1 404 Not Found\r\n");
                writer.write("Content-Type: text/html\r\n");
                writer.write("\r\n"); // 空行，分隔头部和消息体
                //writer.write("<h1>404 Not Found</h1>"); // 返回404页面给客户端
                String params = "404 Not Found";
                /*String params = "<html>" +
                        "<head><title>404 Not Found</title></head>" +
                        "<body><h1>404 Not Fount</h1><p>The requested resource was not found on this server.</p></body>" +
                        "</html>";*/
                writer.write(params);
            }

            socket.close();


        }
    }


    //注销账户
    // -1用户不存在  -2密码错误 1删除成功 0删除失败
    private static int logout(String username, String password) {
        String sql1 = "select username,password from user where username = ?";
        ArrayList<User> query = CRUDutils.query(sql1, username);
        if (query.isEmpty()) {
            return -1;
        }
        else {
            User user = query.get(0);
            if (user.getPassword().equals(password)) {
                String sql2 = "delete from user where username = ?";

                int count = CRUDutils.update(sql2, username);

                if (count > 0) {
                    return 1;
                } else {
                    return 0;
                }
            }
            //密码错误
            else {
                return -2;
            }
        }
    }

    //登录判断
    private static int loginUser(String username, String password) {
        String sql = "select username,password from user where username = ?";
        ArrayList<User> query = CRUDutils.query(sql, username);
        //System.out.println(query);
        //username不存在时,集合为[]
        //username存在时，集合为[User{username='zhangsan', password='123456'}]
        if (query.isEmpty()) {
            return -1;//用户不存在
        } else {
            User user = query.get(0);
            if (user.getPassword().equals(password)) {
                return 1;
            } else {
                return 0;
            }
        }
        //System.out.println(user);
    }

    //注册
    public static int registerUser(String username, String password) {
        String sql1 = "select username,password from user where username = ?";
        ArrayList<User> query = CRUDutils.query(sql1, username);
        if (!(query.isEmpty())) {
            return -1;
        }

        String sql2 = "insert into user (username,password) values (?,?)";

        int count = CRUDutils.update(sql2, username, password);

        if (count > 0) {
            return 1;
        } else {
            return 0;
        }

    }


    //修改密码
    public static int resetPassword(String username, String password) {
        String sql1 = "select username,password from user where username = ?";
        ArrayList<User> query = CRUDutils.query(sql1, username);
        if (query.isEmpty()) {
            return -1;//用户不存在
        }


        String sql2 = "update user set password = ? where username = ?";

        int count = CRUDutils.update(sql2, password, username);

        if (count > 0) {
            return 1;
        } else {
            return 0;
        }
    }
}
