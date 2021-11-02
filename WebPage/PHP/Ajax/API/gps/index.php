<?php

//acessar banco de dados mysql
$db_host = "host";
$db_user = "usuario";
$db_pass = "senha";
$db_name = "DB_API";

//conectar ao banco de dados
$conn = mysqli_connect($db_host, $db_user, $db_pass, $db_name);

//pegar todas colunas da ultima linha da tabela
$sql = "SELECT * FROM gps ORDER BY id DESC LIMIT 1";
$result = mysqli_query($conn, $sql);

//imprimir resultado no formato json
$row = mysqli_fetch_assoc($result);
echo json_encode($row);

?>