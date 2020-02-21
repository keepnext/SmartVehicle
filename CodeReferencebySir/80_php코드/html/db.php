<?php
    $mysql_hostname = 'localhost';
    $mysql_username = 'root';
    $mysql_password = '1234';
    $mysql_port = '3306';
    $mysql_charset = 'utf8';
 
    $connect = new mysqli($mysql_hostname, $mysql_username, $mysql_password);
 
    var_dump($connect);
 
    if($connect->connect_errno){
        echo '[연결실패] : '.$connect->connect_error.'';
    }else{
        echo '[연결성공!]';
    }
 
?>

