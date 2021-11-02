<!DOCTYPE html>
<html>
    <head>
        <title>Rocket</title>
    </head>

    <body>
        <div>
            <h1>BMP180</h1>
        </div>

        <div>
            <h1>MPU6050</h1>
        </div>

        <div>
            <h1>GPS</h1>
        </div>

        <h4>
            <?php
                date_default_timezone_set('America/Sao_Paulo');
                $data = date('Y-m-d H:i:s');
                echo $data;
            ?>
        </h4>
        
    </body>
</html>