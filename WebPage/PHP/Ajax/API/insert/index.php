<?php
//verificar se a key da API está correta
$api_key = $_POST['api_key'];
if ($api_key == '13052007') {
    //acessar banco de dados mysql
$db_host = "host";
$db_user = "usuario";
$db_pass = "senha";
$db_name = "DB_API";

//conectar ao banco de dados
$conn = mysqli_connect($db_host, $db_user, $db_pass, $db_name);

//data-horario atual php
date_default_timezone_set('America/Sao_Paulo');
$data = date('Y-m-d H:i:s');

//pegar dados POST
//BMP
$temperatura_bmp = $_POST['temperatura_bmp'];
$pressao = $_POST['pressao'];
$altitude_bmp = $_POST['altitude_bmp'];
$pressao_nivel_mar = $_POST['pressao_nivel_mar'];
$altitude_real = $_POST['altitude_real'];

//MPU
$acelerometro_x = $_POST['acX'];
$acelerometro_y = $_POST['acY'];
$acelerometro_z = $_POST['acZ'];
$giroscopio_x = $_POST['gyX'];
$giroscopio_y = $_POST['gyY'];
$giroscopio_z = $_POST['gyZ'];
$temperatura_mpu = $_POST['temperatura_mpu'];
$velocidade_mpu = $_POST['velocidade_mpu'];

//GPS
$qtd_satelites = $_POST['qtd_satelites'];
$latitude = $_POST['latitude'];
$longitude = $_POST['longitude'];
$altitude_gps = $_POST['altitude_gps'];
$velocidade_gps = $_POST['velocidade_gps'];
$data_gps = $_POST['data_gps'];

//sql dados para o banco de dados
$sql_bmp = "INSERT INTO bmp VALUES ($temperatura_bmp, $pressao, $altitude_bmp, $pressao_nivel_mar, $altitude_real, $data)";
$sql_mpu = "INSERT INTO mpu VALUES ($acelerometro_x, $acelerometro_y, $acelerometro_z, $giroscopio_x, $giroscopio_y, $giroscopio_z, $temperatura_mpu, $velocidade_mpu, $data)";
$sql_gps = "INSERT INTO gps VALUES ($qtd_satelites, $latitude, $longitude, $altitude_gps, $velocidade_gps, $data_gps, $data)";

//enviando todos sql
mysqli_query($conn, $sql_bmp);
mysqli_query($conn, $sql_mpu);
mysqli_query($conn, $sql_gps);
} else {
    echo 'API key incorreta';
}
?>